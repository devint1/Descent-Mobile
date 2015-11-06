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
* $Source: Smoke:miner:source:3d::RCS:setup.c $
* $Revision: 1.4 $
* $Author: allender $
* $Date: 1995/10/11 00:27:04 $
*
* Setup for 3d library
*
* $Log: setup.c $
* Revision 1.4  1995/10/11  00:27:04  allender
* bash free_num_points to 0
*
* Revision 1.3  1995/09/13  11:31:58  allender
* calc for fCanv_w2 and fCanv_h2
*
* Revision 1.2  1995/06/25  21:57:57  allender
* *** empty log message ***
*
* Revision 1.1  1995/05/05  08:52:54  allender
* Initial revision
*
* Revision 1.1  1995/04/17  03:59:01  matt
* Initial revision
*
*
*/

static char rcsid[] = "$Id: setup.c 1.4 1995/10/11 00:27:04 allender Exp $";
#pragma unused(rcsid)

#include <stdlib.h>

#include "error.h"

#include "3d.h"
#include "globvars.h"
#include "clipper.h"
#ifdef OGLES
#include "setupogles.h"
#endif

//initialize the 3d system
void g3_init(void) {
	//	div0_init(DM_ERROR);
	atexit(g3_close);
}

//close down the 3d system
void g3_close(void) {}

extern void init_interface_vars_to_assembler(void);

//start the frame
void g3_start_frame(void) {
	fix s;

	//set int w,h & fixed-point w,h/2
	Canv_w2 = (Canvas_width = grd_curcanv->cv_bitmap.bm_w) << 15;
	Canv_h2 = (Canvas_height = grd_curcanv->cv_bitmap.bm_h) << 15;
#ifdef __powerc
	fCanv_w2 = f2fl((Canvas_width = grd_curcanv->cv_bitmap.bm_w) << 15);
	fCanv_h2 = f2fl((Canvas_height = grd_curcanv->cv_bitmap.bm_h) << 15);
#endif

	//compute aspect ratio for this canvas

	s = fixmuldiv(grd_curscreen->sc_aspect, Canvas_height, Canvas_width);

	if (s <= f1_0) {		//scale x
		Window_scale.x = s;
		Window_scale.y = f1_0;
	}
	else {
		Window_scale.y = fixdiv(f1_0, s);
		Window_scale.x = f1_0;
	}

	Window_scale.z = f1_0;		//always 1

	init_free_points();

	init_interface_vars_to_assembler();		//for the texture-mapper
#ifdef OGLES
	g3_ogles_start_frame();
#endif

}

//this doesn't do anything, but is here for completeness
void g3_end_frame(void) {
	//	Assert(free_point_num==0);
	free_point_num = 0;
#ifdef OGLES
	g3_ogles_end_frame();
#endif
}
