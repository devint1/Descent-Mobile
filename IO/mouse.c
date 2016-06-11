/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 * $Source: f:/miner/source/bios/rcs/mouse.c $
 * $Revision: 1.11 $
 * $Author: john $
 * $Date: 1995/02/10 18:52:17 $
 * 
 * Functions to access Mouse and Cyberman...
 * 
 * $Log: mouse.c $
 * Revision 1.11  1995/02/10  18:52:17  john
 * Fixed bug with mouse not getting closed.
 * 
 * Revision 1.10  1995/02/02  11:10:33  john
 * Changed a bunch of mouse stuff around to maybe get
 * around PS/2 mouse hang.
 * 
 * Revision 1.9  1995/01/14  19:19:52  john
 * Fixed signed short error cmp with -1 that caused mouse
 * to break under Watcom 10.0
 * 
 * Revision 1.8  1994/12/27  12:38:23  john
 * Made mouse use temporary dos buffer instead of
 * 
 * allocating its own.
 * 
 * 
 * Revision 1.7  1994/12/05  23:54:53  john
 * Fixed bug with mouse_get_delta only returning positive numbers..
 * 
 * Revision 1.6  1994/11/18  23:18:18  john
 * Changed some shorts to ints.
 * 
 * Revision 1.5  1994/09/13  12:34:02  john
 * Added functions to get down count and state.
 * 
 * Revision 1.4  1994/08/29  20:52:19  john
 * Added better cyberman support; also, joystick calibration
 * value return funcctiionn,
 * 
 * Revision 1.3  1994/08/24  18:54:32  john
 * *** empty log message ***
 * 
 * Revision 1.2  1994/08/24  18:53:46  john
 * Made Cyberman read like normal mouse; added dpmi module; moved
 * mouse from assembly to c. Made mouse buttons return time_down.
 * 
 * Revision 1.1  1994/08/24  13:56:37  john
 * Initial revision
 * 
 * 
 */


#pragma unused(rcsid)
static char rcsid[] = "$Id: mouse.c 1.11 1995/02/10 18:52:17 john Exp $";

#define near
#define far

#include "fix.h"
#include "dpmi.h"
#include "mouse.h"
#include "timer.h"
#include "motion.h"

#include <stdlib.h>
#include <stdio.h>
#include <kconfig.h>

#define MOUSE_MAX_BUTTONS	11

typedef struct event_info {
	short x;
	short y;
	short z;
	short pitch;
	short bank;
} event_info;

typedef struct mouse_info {
	fix		ctime;
	ubyte		cyberman;
	int		num_buttons;
	ubyte		pressed[MOUSE_MAX_BUTTONS];
	fix		time_went_down[MOUSE_MAX_BUTTONS];
	fix		time_held_down[MOUSE_MAX_BUTTONS];
	uint		num_downs[MOUSE_MAX_BUTTONS];
	uint		num_ups[MOUSE_MAX_BUTTONS];
	event_info x_info;
} mouse_info;

static mouse_info Mouse;

static int Mouse_installed = 0;

int touch_dx = 0, touch_dy = 0;

#pragma off (check_stack)
void mouse_handler (short x, short y, bool down) {
	Mouse.ctime = timer_get_fixed_secondsX();
	
	if (down) {	// left button pressed
		if (!Mouse.pressed[MB_LEFT]) {
			Mouse.pressed[MB_LEFT] = 1;
			Mouse.time_went_down[MB_LEFT] = Mouse.ctime;
			Mouse.x_info.x = x;
			Mouse.x_info.y = y;
		}
		Mouse.num_downs[MB_LEFT]++;
	}
	else {  // left button released
		if (Mouse.pressed[MB_LEFT]) {
			Mouse.pressed[MB_LEFT] = 0;
			Mouse.time_held_down[MB_LEFT] += Mouse.ctime - Mouse.time_went_down[MB_LEFT];
			Mouse.x_info.x = x;
			Mouse.x_info.y = y;
		}
		Mouse.num_ups[MB_LEFT]++;
	}
}

void mouse_handler_end (void)  // dummy functions
{
}
#pragma on (check_stack)

//--------------------------------------------------------
// returns 0 if no mouse
//           else number of buttons
int mouse_init()
{
	if (Mouse_installed)
		return Mouse.num_buttons;

	Mouse.num_buttons = 1;
	Mouse.cyberman = 0;

	if (!dpmi_lock_region(&Mouse,sizeof(mouse_info)))	{
		printf( "Unable to lock mouse data region" );
		exit(1);
	}
	if (!dpmi_lock_region((void near *)mouse_handler,(char *)mouse_handler_end - (char near *)mouse_handler))	{
		printf( "Unable to lock mouse handler" );
		exit(1);
	}

	Mouse_installed = 1;
	atexit( mouse_close );
	mouse_flush();

	if (Config_use_gyroscope) {
		startMotion();
	}

	return Mouse.num_buttons;
}



void mouse_close()
{
	if (Mouse_installed)	{
		Mouse_installed = 0;
	}
}

// Uses the device's accelerometer + gyroscope and touch drags
// dz was added for banking, and gives the game a nice stabilization effect
void mouse_get_delta( int *dx, int *dy, int *dz)
{
	double x, y, z;

	if (!Mouse_installed) {
		*dx = *dy = 0;
		return;
	}
	*dx = touch_dx * 3;
	*dy = touch_dy * 4;

	// The multipliers here are arbitrary; they just adjust the sensitivity
	if (Config_use_gyroscope) {
		getAcceleration(&x, &y, &z);
		if (*dx == 0 && *dy == 0) {
			*dx = (int)(x * 10.0);
			*dy = (int)(y * 10.0);
		}
		*dz = (int)(z * 10.0);
	} else {
		*dz = 0;
	}
}

int mouse_get_btns()
{
	int i;
	uint flag=1;
	int status = 0;

	if (!Mouse_installed) 
		return 0;

	for (i=0; i<MOUSE_MAX_BUTTONS; i++ )	{
		if (Mouse.pressed[i])
			status |= flag;
		flag <<= 1;
	}
	return status;
}

void mouse_set_pos(short x, short y)
{
	Mouse.x_info.x = x;
	Mouse.x_info.y = y;
}

void mouse_flush()
{
	int i;
	fix CurTime;

	if (!Mouse_installed) 
		return;

	//Clear the mouse data
	CurTime =timer_get_fixed_secondsX();
	for (i=0; i<MOUSE_MAX_BUTTONS; i++ )	{
		Mouse.pressed[i] = 0;
		Mouse.time_went_down[i] = CurTime;
		Mouse.time_held_down[i] = 0;
		Mouse.num_downs[i]=0;
		Mouse.num_ups[i]=0;
	}
}

// Returns how many times this button has went down since last call.
int mouse_button_down_count(int button, int *x, int *y)
{
	int count;

	if (!Mouse_installed) 
		return 0;
	
	if(x) {
		*x = Mouse.x_info.x;
	}
	if(y) {
		*y = Mouse.x_info.y;
	}

	count = Mouse.num_downs[button];
	Mouse.num_downs[button]=0;

	return count;
}

// Returns how many times this button has went up since last call.
int mouse_button_up_count(int button, int *x, int *y)
{
	int count;

	if (!Mouse_installed)
		return 0;

	if(x) {
		*x = Mouse.x_info.x;
	}
	if(y) {
		*y = Mouse.x_info.y;
	}

	count = Mouse.num_ups[button];
	Mouse.num_ups[button]=0;

	return count;
}

// Returns 1 if this button is currently down
int mouse_button_state(int button)	
{
	int state;

	if (!Mouse_installed) 
		return 0;

	state = Mouse.pressed[button];

	return state;
}

// Returns how long this button has been down since last call.
fix mouse_button_down_time(int button, int *x, int *y)
{
	fix time_down, time;

	if (!Mouse_installed) 
		return 0;
	
	if(x) {
		*x = Mouse.x_info.x;
	}
	if(y) {
		*y = Mouse.x_info.y;
	}

	if ( !Mouse.pressed[button] )	{
		time_down = Mouse.time_held_down[button];
		Mouse.time_held_down[button] = 0;
	} else	{
		time = timer_get_fixed_secondsX();
		time_down =  time - Mouse.time_went_down[button];
		Mouse.time_went_down[button] = time;
	}

	return time_down;
}

void mouse_get_cyberman_pos( int *x, int *y )
{
	dpmi_real_regs rr;
	event_info * ei;
	ubyte *Mouse_dos_mem;

	if ( (!Mouse_installed) || (!Mouse.cyberman) ) {
		*x = *y = 0;
		return;
	}

	Mouse_dos_mem = dpmi_get_temp_low_buffer( 64 );

	if ( !Mouse_dos_mem )	{
		*x = *y = 0;
		return;
	}


	memset( &rr, 0, sizeof(dpmi_real_regs) );
	rr.es = DPMI_real_segment(Mouse_dos_mem);
	rr.edx = DPMI_real_offset(Mouse_dos_mem);
	rr.eax = 0x5301;
	dpmi_real_int386x( 0x33, &rr );

	ei = (event_info *)Mouse_dos_mem;

	*x = (((ei->x+8128)*256)/(8064+8128+1)) - 127;
	*y = (((ei->y+8128)*256)/(8064+8128+1)) - 127;

}
