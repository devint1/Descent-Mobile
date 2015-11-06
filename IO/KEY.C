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
 * $Source: f:/miner/source/bios/rcs/key.c $
 * $Revision: 1.35 $
 * $Author: john $
 * $Date: 1995/01/25 20:13:30 $
 * 
 * Functions for keyboard handler.
 * 
 * $Log: key.c $
 * Revision 1.35  1995/01/25  20:13:30  john
 * Took out not passing keys to debugger if w10.
 * 
 * Revision 1.34  1995/01/14  19:19:31  john
 * Made so when you press Shift+Baskspace, it release keys autmatically.
 * 
 * Revision 1.33  1994/12/13  09:21:48  john
 * Took out keyd_editor_mode, and KEY_DEBUGGED stuff for NDEBUG versions.
 * 
 * Revision 1.32  1994/11/12  13:52:01  john
 * Fixed bug with code that cleared bios buffer.
 * 
 * Revision 1.31  1994/10/24  15:16:16  john
 * Added code to detect KEY_PAUSE.
 * 
 * Revision 1.30  1994/10/24  13:57:53  john
 * Hacked in support for pause key onto code 0x61.
 * 
 * Revision 1.29  1994/10/21  15:18:13  john
 * *** empty log message ***
 * 
 * Revision 1.28  1994/10/21  15:17:24  john
 * Made LSHIFT+BACKSPACE do what PrtScr used to.
 * 
 * Revision 1.27  1994/09/22  16:09:18  john
 * Fixed some virtual memory lockdown problems with timer and
 * joystick.
 * 
 * Revision 1.26  1994/09/15  21:32:47  john
 * Added bounds checking for down_count scancode
 * parameter.
 * 
 * Revision 1.25  1994/08/31  12:22:20  john
 * Added KEY_DEBUGGED
 * 
 * Revision 1.24  1994/08/24  18:53:48  john
 * Made Cyberman read like normal mouse; added dpmi module; moved
 * mouse from assembly to c. Made mouse buttons return time_down.
 * 
 * Revision 1.23  1994/08/18  15:17:51  john
 * *** empty log message ***
 * 
 * Revision 1.22  1994/08/18  15:16:38  john
 * fixed some bugs with clear_key_times and then
 * removed it because i fixed key_flush to do the
 * same.
 * 
 * Revision 1.21  1994/08/17  19:01:25  john
 * Attempted to fix a bug with a key being held down
 * key_flush called, then the key released having too 
 * long of a time.
 * 
 * Revision 1.20  1994/08/08  10:43:48  john
 * Recorded when a key was pressed for key_inkey_time.
 * 
 * Revision 1.19  1994/06/22  15:00:03  john
 * Made keyboard close automatically on exit.
 * 
 * Revision 1.18  1994/06/21  09:16:29  john
 * *** empty log message ***
 * 
 * Revision 1.17  1994/06/21  09:08:23  john
 * *** empty log message ***
 * 
 * Revision 1.16  1994/06/21  09:05:01  john
 * *** empty log message ***
 * 
 * Revision 1.15  1994/06/21  09:04:24  john
 * Made PrtScreen do an int5
 * 
 * Revision 1.14  1994/06/17  17:17:06  john
 * Added keyd_time_last_key_was_pressed or something like that.
 * 
 * Revision 1.13  1994/05/14  13:55:16  matt
 * Added #define to control key passing to bios
 * 
 * Revision 1.12  1994/05/05  18:09:39  john
 * Took out BIOS to prevent stuck keys.
 * 
 * Revision 1.11  1994/05/03  17:39:12  john
 * *** empty log message ***
 * 
 * Revision 1.10  1994/04/29  12:14:20  john
 * Locked all memory used during interrupts so that program
 * won't hang when using virtual memory.
 * 
 * Revision 1.9  1994/04/28  23:49:41  john
 * Made key_flush flush more keys and also did something else but i forget what.
 * 
 * Revision 1.8  1994/04/22  12:52:12  john
 * *** empty log message ***
 * 
 * Revision 1.7  1994/04/01  10:44:59  mike
 * Change key_getch() to call getch() if our interrupt hasn't been installed.
 * 
 * Revision 1.6  1994/03/09  10:45:48  john
 * Neatend code a bit.
 * 
 * Revision 1.5  1994/02/17  17:24:16  john
 * Neatened up a bit.
 * 
 * Revision 1.4  1994/02/17  16:30:29  john
 * Put in code to pass keys when in debugger.
 * 
 * Revision 1.3  1994/02/17  15:57:59  john
 * Made handler not chain to BIOS handler.
 * 
 * Revision 1.2  1994/02/17  15:56:06  john
 * Initial version.
 * 
 * Revision 1.1  1994/02/17  15:54:07  john
 * Initial revision
 * 
 * 
 */

//#define PASS_KEYS_TO_BIOS	1			//if set, bios gets keys

static char rcsid[] = "$Id: key.c 1.35 1995/01/25 20:13:30 john Exp $";
#pragma unused(rcsid)

#include <stdlib.h>
#include <stdio.h>

//#define WATCOM_10

#include "error.h"
#include "key.h"
#include "timer.h"
#include "dpmi.h"
#include "i86.h"

#define KEY_BUFFER_SIZE 16

#define __interrupt
#define near
#define __far

//-------- Variable accessed by outside functions ---------
unsigned char 				keyd_buffer_type;		// 0=No buffer, 1=buffer ASCII, 2=buffer scans
unsigned char 				keyd_repeat;
unsigned char 				keyd_editor_mode;
volatile unsigned char 	keyd_last_pressed;
volatile unsigned char 	keyd_last_released;
volatile unsigned char	keyd_pressed[256];
volatile int				keyd_time_when_last_pressed;

typedef struct keyboard	{
	unsigned short		keybuffer[KEY_BUFFER_SIZE];
	fix					time_pressed[KEY_BUFFER_SIZE];
	fix					TimeKeyWentDown[256];
	fix					TimeKeyHeldDown[256];
	unsigned int		NumDowns[256];
	unsigned int		NumUps[256];
	unsigned int 		keyhead, keytail;
	unsigned char 		E0Flag;
	unsigned char 		E1Flag;
	int 					in_key_handler;
	void (__interrupt __far *prev_int_9)();
} keyboard;

static volatile keyboard key_data;

static unsigned char Installed=0;

unsigned char ascii_table[256] = {
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 10
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 20
	255, 255, ' ', 255, 255, 255, 255, 255, 255, 255,	// 30
	255, 255, 255, 255, 255, 255, 255, 255, '0', '1',	// 40
	'2', '3', '4', '5', '6', '7', '8', '9', 255, 255,	// 50
	255, 255, 255, 255, 255, 'a', 'b', 'c', 'd', 'e',	// 60
	'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',	// 70
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',	// 80
	'z', 255, 255, 255, 255, '0', '1', '2', '3', '4',	// 90
	'5', '6', '7', '8', '9', 255, '*', '+', 255, '-',	// 100
	'.', '/', 255, 255, 255, 255, 255, 255, 255, 255,	// 110
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 120
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 130
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 140
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 150
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 160
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 170
	255, 255, 255, 255, 255, 255, 255, '=', ',', '-',	// 180
	'.', '/', '`', 255, 255, 255, ';', 255, 255, 255,	// 190
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 200
	255, 255, 255, 255, 255, 255, 255, 255, 255, '[',	// 210
	'\\',']', '\'',255, 255, 255, 255, 255, 255, 255,	// 220
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 230
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 240
	255, 255, 255, 255, 255, 255 };						// 250

unsigned char shifted_ascii_table[256] = {
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 10
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 20
	255, 255, ' ', 255, 255, 255, 255, 255, 255, 255,	// 30
	255, 255, 255, 255, 255, 255, 255, 255, 255, '!',	// 40
	'@', '#', '$', '%', '^', '&', '*', '(', ')', 255,	// 50
	255, 255, 255, 255, 255, 'A', 'B', 'C', 'D', 'E',	// 60
	'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',	// 70
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',	// 80
	'Z', 255, 255, 255, 255, '0', '1', '2', '3', '4',	// 90
	'5', '6', '7', '8', '9', 255, '*', '+', 255, '-',	// 100
	'.', '/', 255, 255, 255, 255, 255, 255, 255, 255,	// 110
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 120
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 130
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 140
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 150
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 160
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 170
	255, 255, 255, 255, 255, 255, 255, '+', '<', '_',	// 180
	'>', '?', '~', 255, 255, 255, ':', 255, 255, 255,	// 190
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 200
	255, 255, 255, 255, 255, 255, 255, 255, 255, '{',	// 210
	'|', '}', '"', 255, 255, 255, 255, 255, 255, 255,	// 220
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 230
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 240
	255, 255, 255, 255, 255, 255 };						// 250

extern char key_to_ascii(int keycode )
{
	return keycode;
}

void key_clear_bios_buffer_all() {
	// Does nothing since there is nothing to clear!
}

void key_clear_bios_buffer() {
	// Same here, no more memory-mapped I/O
}

void key_flush()
{
	int i;
	fix CurTime;

	// Clear the BIOS buffer
	key_clear_bios_buffer();

	key_data.keyhead = key_data.keytail = 0;

	//Clear the keyboard buffer
	for (i=0; i<KEY_BUFFER_SIZE; i++ )	{
		key_data.keybuffer[i] = 0;
		key_data.time_pressed[i] = 0;
	}
	
	//Clear the keyboard array

	CurTime =timer_get_fixed_secondsX();

	for (i=0; i<256; i++ )	{
		keyd_pressed[i] = 0;
		key_data.TimeKeyWentDown[i] = CurTime;
		key_data.TimeKeyHeldDown[i] = 0;
		key_data.NumDowns[i]=0;
		key_data.NumUps[i]=0;
	}
}

int add_one( int n )
{
	n++;
	if ( n >= KEY_BUFFER_SIZE ) n=0;
	return n;
}

// Returns 1 if character waiting... 0 otherwise
int key_checkch()
{
	int is_one_waiting = 0;

	//_disable();

	key_clear_bios_buffer();

	if (key_data.keytail!=key_data.keyhead)
		is_one_waiting = 1;
	//_enable();
	return is_one_waiting;
}

int key_inkey()
{
	int key = -1;

	//_disable();

	key_clear_bios_buffer();

	if (key_data.keytail!=key_data.keyhead)	{
		key = key_data.keybuffer[key_data.keyhead];
		key_data.keyhead = add_one(key_data.keyhead);
	}
	//_enable();
	return key;
}

int key_inkey_time(fix * time)
{
	int key = 0;

	//_disable();

	key_clear_bios_buffer();

	if (key_data.keytail!=key_data.keyhead)	{
		key = key_data.keybuffer[key_data.keyhead];
		*time = key_data.time_pressed[key_data.keyhead];
		key_data.keyhead = add_one(key_data.keyhead);
	}
	//_enable();
	return key;
}


int key_peekkey()
{
	int key = 0;

	key_clear_bios_buffer();

	if (key_data.keytail!=key_data.keyhead)	{
		key = key_data.keybuffer[key_data.keyhead];
	}

	return key;
}

// If not installed, uses BIOS and returns getch();
//	Else returns pending key (or waits for one if none waiting).
int key_getch()
{
	int dummy=0;
	
	/*if (!Installed)
		return getch();*/

	while (!key_checkch())
		dummy++;
	return key_inkey();
}

unsigned int key_get_shift_status()
{
	unsigned int shift_status = 0;

	key_clear_bios_buffer();

	if ( keyd_pressed[KEY_LSHIFT] || keyd_pressed[KEY_RSHIFT] )
		shift_status |= KEY_SHIFTED;

	if ( keyd_pressed[KEY_LALT] || keyd_pressed[KEY_RALT] )
		shift_status |= KEY_ALTED;

	if ( keyd_pressed[KEY_LCTRL] || keyd_pressed[KEY_RCTRL] )
		shift_status |= KEY_CTRLED;

#ifndef NDEBUG
	if (keyd_pressed[KEY_DELETE])
		shift_status |=KEY_DEBUGGED;
#endif

	return shift_status;
}

// Returns the number of seconds this key has been down since last call.
fix key_down_time(int scancode)	{
	fix time_down, time;

	if ((scancode<0)|| (scancode>255)) return 0;

#ifndef NDEBUG
	if (keyd_editor_mode && key_get_shift_status() )
		return 0;  
#endif

	if ( !keyd_pressed[scancode] )	{
		time_down = key_data.TimeKeyHeldDown[scancode];
		key_data.TimeKeyHeldDown[scancode] = 0;
	} else	{
		time = timer_get_fixed_secondsX();
		time_down =  time - key_data.TimeKeyWentDown[scancode];
		key_data.TimeKeyWentDown[scancode] = time;
	}

	return time_down;
}

// Returns number of times key has went from up to down since last call.
unsigned int key_down_count(int scancode)	{
	int n;

	if ((scancode<0)|| (scancode>255)) return 0;

	n = key_data.NumDowns[scancode];
	key_data.NumDowns[scancode] = 0;

	return n;
}


// Returns number of times key has went from down to up since last call.
unsigned int key_up_count(int scancode)	{
	int n;

	if ((scancode<0)|| (scancode>255)) return 0;

	n = key_data.NumUps[scancode];
	key_data.NumUps[scancode] = 0;

	return n;
}

// Use intrinsic forms so that we stay in the locked interrup code.

void Int5() {
//#pragma aux Int5 = "int 5";
	//__asm { int 5 }
}

#pragma off (check_stack)
void key_handler(unsigned char scancode, bool down) {
	unsigned char temp;
	unsigned short keycode;

	if (!down) {
		// Key going up
		keyd_last_released = scancode;
		keyd_pressed[scancode] = 0;
		key_data.NumUps[scancode]++;
		temp = 0;
		temp |= keyd_pressed[KEY_LSHIFT] || keyd_pressed[KEY_RSHIFT];
		temp |= keyd_pressed[KEY_LALT] || keyd_pressed[KEY_RALT];
		temp |= keyd_pressed[KEY_LCTRL] || keyd_pressed[KEY_RCTRL];
#ifndef NDEBUG
		temp |= keyd_pressed[KEY_DELETE];
		if (!(keyd_editor_mode && temp))
#endif		// NOTICE LINK TO ABOVE IF!!!!
			key_data.TimeKeyHeldDown[scancode] += timer_get_fixed_secondsX() - key_data.TimeKeyWentDown[scancode];
	}
	else {
		// Key going down
		keyd_last_pressed = scancode;
		keyd_time_when_last_pressed = timer_get_fixed_secondsX();
		if (!keyd_pressed[scancode]) {
			// First time down
			key_data.TimeKeyWentDown[scancode] = timer_get_fixed_secondsX();
			keyd_pressed[scancode] = 1;
			key_data.NumDowns[scancode]++;
#ifndef NDEBUG
			if ((keyd_pressed[KEY_LSHIFT]) && (scancode == KEY_BACKSP)) {
				keyd_pressed[KEY_LSHIFT] = 0;
				Int5();
			}
#endif
		}
		else if (!keyd_repeat) {
			// Don't buffer repeating key if repeat mode is off
			scancode = 0xAA;
		}

		if (scancode != 0xAA) {
			keycode = scancode;

			if (keyd_pressed[KEY_LSHIFT] || keyd_pressed[KEY_RSHIFT])
				keycode |= KEY_SHIFTED;

			if (keyd_pressed[KEY_LALT] || keyd_pressed[KEY_RALT])
				keycode |= KEY_ALTED;

			if (keyd_pressed[KEY_LCTRL] || keyd_pressed[KEY_RCTRL])
				keycode |= KEY_CTRLED;

#ifndef NDEBUG
			if (keyd_pressed[KEY_DELETE])
				keycode |= KEY_DEBUGGED;
#endif

			temp = key_data.keytail + 1;
			if (temp >= KEY_BUFFER_SIZE) temp = 0;

			if (temp != key_data.keyhead) {
				key_data.keybuffer[key_data.keytail] = keycode;
				key_data.time_pressed[key_data.keytail] = keyd_time_when_last_pressed;
				key_data.keytail = temp;
			}
		}
	}
}

#pragma on (check_stack)

void key_handler_end()	{		// Dummy function to help calculate size of keyboard handler function
}

void key_init()
{
	// Initialize queue

	keyd_time_when_last_pressed = timer_get_fixed_seconds();
	keyd_buffer_type = 1;
	keyd_repeat = 1;
	key_data.in_key_handler = 0;
	key_data.E0Flag = 0;
	key_data.E1Flag = 0;

	// Clear the keyboard array
	key_flush();

	if (Installed) return;
	Installed = 1;

	//--------------- lock everything for the virtal memory ----------------------------------
	if (!dpmi_lock_region ((void near *)key_handler, (char *)key_handler_end - (char near *)key_handler))	{
		printf( "Error locking keyboard handler!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&key_data, sizeof(keyboard)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_buffer_type, sizeof(char)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_repeat, sizeof(char)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_editor_mode, sizeof(char)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_last_pressed, sizeof(char)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_last_released, sizeof(char)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_pressed, sizeof(char)*256))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}
	if (!dpmi_lock_region (&keyd_time_when_last_pressed, sizeof(int)))	{
		printf( "Error locking keyboard handler's data!\n" );
		exit(1);
	}

	atexit( key_close );
}

void key_close()
{
	if (!Installed) return;
	Installed = 0;

	key_clear_bios_buffer_all();
}
