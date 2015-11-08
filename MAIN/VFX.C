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
 * $Source: f:/miner/source/main/rcs/vfx.c $
 * $Revision: 2.4 $
 * $Author: john $
 * $Date: 1995/05/11 13:28:59 $
 * 
 * Routines to access VR helmet.
 * 
 * $Log: vfx.c $
 * Revision 2.4  1995/05/11  13:28:59  john
 * Made so no -vfx doesnt' check for VIPPORT.
 * 
 * Revision 2.3  1995/05/11  13:08:28  john
 * Made code print bomb out with error if it can't find VIPPORT.
 * 
 * 
 * Revision 2.2  1995/05/08  13:53:32  john
 * Added code to read the vipport environment variable.
 * 
 * Revision 2.1  1995/03/10  13:05:50  john
 * Added code so that palette is correct for VFX1 helmets.
 * 
 * Revision 2.0  1995/02/27  11:30:29  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.5  1994/12/28  10:26:42  john
 * Fixed some VFX problems.
 * 
 * Revision 1.4  1994/11/19  15:20:34  mike
 * rip out unused code and data
 * 
 * Revision 1.3  1994/09/20  19:36:11  matt
 * Added seperate function to set palette
 * 
 * Revision 1.2  1994/06/24  17:03:50  john
 * Added VFX support. Also took all game sequencing stuff like
 * EndGame out and put it into gameseq.c
 * 
 * Revision 1.1  1994/06/23  09:14:06  john
 * Initial revision
 * 
 * 
 */

static char rcsid[] = "$Id: vfx.c 2.4 1995/05/11 13:28:59 john Exp $";
#pragma unused(rcsid)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gr.h"
#include "error.h"
#include "mono.h"

#define INDEX_SCR 	0
#define INDEX_SRR 	1
#define INDEX_ICR 	2
#define INDEX_ISR 	3
#define INDEX_PSR		4
#define INDEX_VRR		5
#define INDEX_PCR		6
#define INDEX_PPRR	7
#define INDEX_PRAR	8
#define INDEX_PWAR	9
#define INDEX_PCRR	10

#define PORT_AIR		(vfx_base_port)
#define PORT_CSR		(vfx_base_port+1)
#define PORT_DFIN		(vfx_base_port+2)
#define PORT_DFOUT	(vfx_base_port+4)

typedef struct DATA_SCR	{
	union {
		struct {
			ubyte cmd 	: 6;	//Command Code 
			ubyte cchk 	: 1;	//Command Check Condition
			ubyte cpnd 	: 1;	//Command Pending
		};
		ubyte value;
	};
} DATA_SCR;

typedef struct DATA_SSR	{
	ubyte ssc	: 6;	// Software Status Code
	ubyte rsvd	: 2;	// Reserved
} DATA_SSR;

typedef struct DATA_ICR	{
	ubyte ien	: 1;	// Interrupt Enable
	ubyte cor	: 1;	// Clear On Read
	ubyte sfmd	: 2;	// Sync/Flip Mode
	ubyte rsvd	: 4;	// Reserved
} DATA_ICR;

typedef struct DATA_ISR	{
	ubyte sfip	: 1;	// Sync/Flip Interrupt Pending
	ubyte rsvd	: 6;	// Reserved
	ubyte flpp	: 1;	// Flip Pending
} DATA_ISR;

typedef struct DATA_PSR	{
	union {
		struct {
			ubyte reps	: 4;	// Right Eye Page Select
			ubyte leps	: 4;	// Left Eye Page Select
		};
		ubyte value;
	};
} DATA_PSR;

typedef struct DATA_VRR	{
	union {
		struct {
			ubyte vipr	: 1;	// VIPP Ready
			ubyte rsvd	: 7;	// Reserved
		};
		ubyte value;
	};
} DATA_VRR;

typedef struct DATA_PCR	{
	ubyte dps	: 1;	// Disable Palette Snoop
	ubyte lrps	: 1;	// Left/Right Palette Select
	ubyte wrbp	: 1;	// WRite Both Palettes
	ubyte rsvd	: 5;	// Reserved
} DATA_PCR;


extern int Game_vfx_flag;
static int vfx_base_port = 0x260;

static int vfx_initialized = 0;

extern void gr_palette_apply(ubyte *palette);

void vfx_init()
{
	char * vipport;

	if (vfx_initialized) return;
	vfx_initialized = 1;
	
	vipport = getenv( "VIPPORT" );
	if ( vipport )	{
		sscanf( vipport, "%x", &vfx_base_port );
	} else {
		Error( "Couldn't find VIPPORT environment variable.\n" );
	}
}

//download palette into VFX
void vfx_set_palette_sub(ubyte * palette)
{
#ifdef OGLES
	gr_palette_apply(palette);
#endif
}

void vfx_set_palette()
{
	if (!vfx_initialized) return;
	vfx_set_palette_sub(gr_palette);
}

void vfx_init_graphics()
{
}


void vfx_close_graphics()
{
}



void vfx_set_page(ubyte page)
{
}
