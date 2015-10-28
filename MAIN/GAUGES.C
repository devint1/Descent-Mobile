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
 * $Source: f:/miner/source/main/rcs/gauges.c $
 * $Revision: 2.7 $
 * $Author: john $
 * $Date: 1995/12/19 16:18:33 $
 *
 * Inferno gauge drivers
 *
 * $Log: gauges.c $
 * Revision 2.7  1995/12/19  16:18:33  john
 * Made weapon info align with canvas width, not 315.
 * 
 * Revision 2.6  1995/03/21  14:39:25  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.5  1995/03/14  12:31:25  john
 * Prevent negative shields from printing.
 * 
 * Revision 2.4  1995/03/10  12:57:58  allender
 * move rear view text up four pixels up when playing back demo
 * 
 * Revision 2.3  1995/03/09  11:47:51  john
 * Added HUD for VR helmets.
 * 
 * Revision 2.2  1995/03/06  15:23:26  john
 * New screen techniques.
 * 
 * Revision 2.1  1995/02/27  13:13:45  john
 * Removed floating point.
 * 
 * Revision 2.0  1995/02/27  11:29:06  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.203  1995/02/11  01:56:45  mike
 * move up weapons text on fullscreen hud, missiles was offscreen.
 * 
 * Revision 1.202  1995/02/09  13:23:34  rob
 * Added reticle names in demo playback.
 * 
 * Revision 1.201  1995/02/08  19:20:46  rob
 * Show cloaked teammates on H
 * UD.  Get rid of show ID's in anarchy option.
 * 
 * Revision 1.200  1995/02/07  21:09:00  mike
 * add flashing to invulnerability and cloak on fullscreen.
 * 
 * Revision 1.199  1995/02/02  21:55:57  matt
 * Added new colored key icons for fullscreen
 * 
 * Revision 1.198  1995/01/30  17:17:07  rob
 * Fixed teammate names on hud.
 * 
 * Revision 1.197  1995/01/28  17:40:49  mike
 * fix gauge fontcolor.
 * 
 * Revision 1.196  1995/01/27  17:03:14  mike
 * fix placement of weapon info in multiplayer fullscreen, as per AP request.
 * 
 * Revision 1.195  1995/01/27  11:51:23  rob
 * Put deaths tally into cooperative mode
 * 
 * Revision 1.194  1995/01/27  11:43:24  adam
 * fiddled with key display
 * 
 * Revision 1.193  1995/01/25  23:38:35  mike
 * fix keys on fullscreen.
 * 
 * Revision 1.192  1995/01/24  22:03:28  mike
 * Lotsa hud stuff, put a lot of messages up.
 * 
 * Revision 1.191  1995/01/23  16:47:21  rob
 * Fixed problem with playing extra life noise in coop.
 * 
 * Revision 1.190  1995/01/22  16:00:46  mike
 * remove unneeded string.
 * 
 * Revision 1.189  1995/01/22  15:58:22  mike
 * localization
 * 
 * Revision 1.188  1995/01/20  17:19:45  rob
 * Fixing colors of hud kill list players.
 * 
 * Revision 1.187  1995/01/20  09:19:18  allender
 * record player flags when in CM_FULL_SCREEN
 * 
 * Revision 1.186  1995/01/19  16:29:09  allender
 * made demo recording of weapon change be in this file for shareware only
 * 
 * Revision 1.185  1995/01/19  15:00:33  allender
 * code to record shield, energy, and ammo in fullscreen
 * 
 * Revision 1.184  1995/01/19  13:43:13  matt
 * Fixed "cheater" message on HUD
 * 
 * Revision 1.183  1995/01/18  16:11:58  mike
 * Don't show added scores of 0.
 * 
 * Revision 1.182  1995/01/17  17:42:39  allender
 * do ammo counts in demo recording
 * 
 * Revision 1.181  1995/01/16  17:26:25  rob
 * Fixed problem with coloration of team kill list.
 * 
 * Revision 1.180  1995/01/16  17:22:39  john
 * Made so that KB and framerate don't collide.
 * 
 * Revision 1.179  1995/01/16  14:58:31  matt
 * Changed score_added display to print "Cheater!" when cheats enabled
 * 
 * Revision 1.178  1995/01/15  19:42:07  matt
 * Ripped out hostage faces for registered version
 * 
 * Revision 1.177  1995/01/15  19:25:07  mike
 * show vulcan ammo and secondary ammo in fullscreen view.
 * 
 * Revision 1.176  1995/01/15  13:16:12  john
 * Made so that paging always happens, lowmem just loads less.
 * Also, make KB load print to hud.
 * 
 * Revision 1.175  1995/01/14  19:17:32  john
 * First version of piggy paging.
 * 
 * Revision 1.174  1995/01/05  21:25:23  rob
 * Re-did some changes lost due to RCS weirdness.
 * 
 * Revision 1.173  1995/01/05  12:22:34  rob
 * Don't show player names for cloaked players.
 * 
 * Revision 1.172  1995/01/04  17:14:50  allender
 * make init_gauges work properly on demo playback
 * 
 * Revision 1.171  1995/01/04  15:04:42  allender
 * new demo calls for registered version
 * 
 * Revision 1.167  1995/01/03  13:03:57  allender
 * pass score points instead of total points.   Added ifdef for
 * multi_send_score
 * 
 * Revision 1.166  1995/01/03  11:45:02  allender
 * add hook to record player score
 * 
 * Revision 1.165  1995/01/03  11:25:19  allender
 * remove newdemo stuff around score display
 * 
 * Revision 1.163  1995/01/02  21:03:53  rob
 * Fixing up the hud-score-list for coop games.
 * 
 * Revision 1.162  1994/12/31  20:54:40  rob
 * Added coop mode HUD score list.
 * Added more generic system for player names on HUD.
 * 
 * Revision 1.161  1994/12/30  20:13:01  rob
 * Ifdef reticle names on shareware.
 * Added robot reticle naming.
 * 
 * Revision 1.160  1994/12/29  17:53:51  mike
 * move up energy/shield in fullscreen to get out of way of kill list.
 * 
 * Revision 1.159  1994/12/29  16:44:05  mike
 * add energy and shield showing.
 * 
 * Revision 1.158  1994/12/28  16:34:29  mike
 * make warning beep go away on Player_is_dead.
 * 
 * Revision 1.157  1994/12/28  10:00:43  allender
 * change in init_gauges to for multiplayer demo playbacks
 * 
 * Revision 1.156  1994/12/27  11:06:46  allender
 * removed some previous code to for demo playback stuff
 * 
 * Revision 1.155  1994/12/23  14:23:06  john
 * Added floating reticle for VR helments.  
 * 
 * Revision 1.154  1994/12/21  12:56:41  allender
 * on multiplayer demo playback, show kills and deaths
 * 
 * Revision 1.153  1994/12/19  20:28:42  rob
 * Get rid of kill list in coop games.
 * 
 * Revision 1.152  1994/12/14  18:06:44  matt
 * Removed compile warnings
 * 
 * Revision 1.151  1994/12/14  15:21:28  rob
 * Made gauges align in status_bar net game.
 * 
 * Revision 1.150  1994/12/12  17:20:33  matt
 * Don't get bonus points when cheating
 * 
 * Revision 1.149  1994/12/12  16:47:00  matt
 * When cheating, get no score.  Change level cheat to prompt for and 
 * jump to new level.
 * 
 * Revision 1.148  1994/12/12  12:05:45  rob
 * Grey out players who are disconnected.
 * 
 * Revision 1.147  1994/12/09  16:19:48  yuan
 * kill matrix stuff.
 * 
 * Revision 1.146  1994/12/09  16:12:34  rob
 * Fixed up the status bar kills gauges for net play.
 * 
 * Revision 1.145  1994/12/09  01:55:34  rob
 * Added kills list to HUD/status bar.
 * Added something for Mark.
 * 
 * Revision 1.144  1994/12/08  21:03:30  allender
 * pass old player flags to record_player_flags
 * 
 * Revision 1.143  1994/12/07  22:49:33  mike
 * no homing missile warning during endlevel sequence.
 * 
 * Revision 1.142  1994/12/06  13:55:31  matt
 * Use new rounding func, f2ir()
 * 
 * Revision 1.141  1994/12/03  19:03:37  matt
 * Fixed vulcan ammo HUD message
 * 
 * Revision 1.140  1994/12/03  18:43:18  matt
 * Fixed (hopefully) claok gauge
 * 
 * Revision 1.139  1994/12/03  14:26:21  yuan
 * Fixed dumb bug
 * 
 * Revision 1.138  1994/12/03  14:17:30  yuan
 * Localization 320
 * 
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: gauges.c 2.7 1995/12/19 16:18:33 john Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "inferno.h"
#include "game.h"
#include "screens.h"
#include "gauges.h"
#include "physics.h"
#include "error.h"

#include "menu.h"			// For the font.
#include "mono.h"
#include "collide.h"
#include "newdemo.h"
#include "player.h"
#include "gamefont.h"
#include "hostage.h"
#include "bm.h"
#include "text.h"
#include "powerup.h"
#include "sounds.h"
#include "multi.h"
#include "network.h"
#include "endlevel.h"

#include "wall.h"
#include "text.h"
#include "render.h"
#include "piggy.h"

bitmap_index Gauges[MAX_GAUGE_BMS];   // Array of all gauge bitmaps.

grs_canvas *Canv_LeftEnergyGauge;
grs_canvas *Canv_SBEnergyGauge;
grs_canvas *Canv_RightEnergyGauge;
grs_canvas *Canv_NumericalGauge;

//bitmap numbers for gauges

#define GAUGE_SHIELDS			0		//0..9, in decreasing order (100%,90%...0%)

#define GAUGE_INVULNERABLE		10		//10..19
#define N_INVULNERABLE_FRAMES	10

#define GAUGE_SPEED		   	20		//unused
#define GAUGE_ENERGY_LEFT		21
#define GAUGE_ENERGY_RIGHT		22
#define GAUGE_NUMERICAL			23

#define GAUGE_BLUE_KEY			24
#define GAUGE_GOLD_KEY			25
#define GAUGE_RED_KEY			26
#define GAUGE_BLUE_KEY_OFF		27
#define GAUGE_GOLD_KEY_OFF		28
#define GAUGE_RED_KEY_OFF		29

#define SB_GAUGE_BLUE_KEY		30
#define SB_GAUGE_GOLD_KEY		31
#define SB_GAUGE_RED_KEY		32
#define SB_GAUGE_BLUE_KEY_OFF	33
#define SB_GAUGE_GOLD_KEY_OFF	34
#define SB_GAUGE_RED_KEY_OFF	35

#define SB_GAUGE_ENERGY			36

#define GAUGE_LIVES				37	

#define GAUGE_SHIPS				38
#define GAUGE_SHIPS_LAST		45

#define RETICLE_CROSS			46
#define RETICLE_PRIMARY			48
#define RETICLE_SECONDARY		51
#define RETICLE_LAST				55

#define GAUGE_HOMING_WARNING_ON	56
#define GAUGE_HOMING_WARNING_OFF	57

#define SML_RETICLE_CROSS		58
#define SML_RETICLE_PRIMARY	60
#define SML_RETICLE_SECONDARY	63
#define SML_RETICLE_LAST		67

#define KEY_ICON_BLUE			68
#define KEY_ICON_YELLOW			69
#define KEY_ICON_RED				70

//change MAX_GAUGE_BMS when adding gauges

//Coordinats for gauges

#define GAUGE_BLUE_KEY_X		(grd_curscreen->sc_w * 0.140625)
#define GAUGE_BLUE_KEY_Y		(grd_curscreen->sc_h * 0.76)
#define GAUGE_GOLD_KEY_X		(grd_curscreen->sc_w * 0.1375)
#define GAUGE_GOLD_KEY_Y		(grd_curscreen->sc_h * 0.81)
#define GAUGE_RED_KEY_X			(grd_curscreen->sc_w * 0.134375)
#define GAUGE_RED_KEY_Y			(grd_curscreen->sc_h * 0.86)

#define SB_GAUGE_KEYS_X			(grd_curscreen->sc_w * 0.034375)

#define SB_GAUGE_BLUE_KEY_Y		(grd_curscreen->sc_h * 0.765)
#define SB_GAUGE_GOLD_KEY_Y		(grd_curscreen->sc_h * 0.845)
#define SB_GAUGE_RED_KEY_Y		(grd_curscreen->sc_h * 0.925)

#define HOMING_WARNING_X	(grd_curscreen->sc_w * 0.021875)
#define HOMING_WARNING_Y	(grd_curscreen->sc_h * 0.855)

#define LEFT_ENERGY_GAUGE_X 	(grd_curscreen->sc_w * 0.21875)
#define LEFT_ENERGY_GAUGE_Y 	(grd_curscreen->sc_h * 0.655)
#define LEFT_ENERGY_GAUGE_W 	(grd_curscreen->sc_w * 0.2)
#define LEFT_ENERGY_GAUGE_H 	(grd_curscreen->sc_h * 0.045)

#define RIGHT_ENERGY_GAUGE_X 	(grd_curscreen->sc_w * 0.59375)
#define RIGHT_ENERGY_GAUGE_Y 	(grd_curscreen->sc_h * 0.655)
#define RIGHT_ENERGY_GAUGE_W 	(grd_curscreen->sc_w * 0.2)
#define RIGHT_ENERGY_GAUGE_H 	(grd_curscreen->sc_h * 0.045)

#define SB_ENERGY_GAUGE_X 		(grd_curscreen->sc_w * 0.30625)
#define SB_ENERGY_GAUGE_Y 		(grd_curscreen->sc_h * 0.775)
#define SB_ENERGY_GAUGE_W 		(grd_curscreen->sc_w * 0.05)
#define SB_ENERGY_GAUGE_H 		(grd_curscreen->sc_h * 0.205)

#define SB_ENERGY_NUM_X 		(SB_ENERGY_GAUGE_X+2)
#define SB_ENERGY_NUM_Y 		(grd_curscreen->sc_h * 0.95)

#define SHIELD_GAUGE_X 			(grd_curscreen->sc_w * 0.45625)
#define SHIELD_GAUGE_Y			(grd_curscreen->sc_h * 0.775)
#define SHIELD_GAUGE_W 			(grd_curscreen->sc_w * 0.109375)
#define SHIELD_GAUGE_H			(grd_curscreen->sc_h * 0.16)

#define SHIP_GAUGE_X 			(SHIELD_GAUGE_X+(grd_curscreen->sc_w*0.015625))
#define SHIP_GAUGE_Y			(SHIELD_GAUGE_Y+(grd_curscreen->sc_h*0.025))

#define SB_SHIELD_GAUGE_X 		(grd_curscreen->sc_w * 0.384375)		//139
#define SB_SHIELD_GAUGE_Y 		(grd_curscreen->sc_h * 0.815)

#define SB_SHIP_GAUGE_X 		(SB_SHIELD_GAUGE_X+(grd_curscreen->sc_h*0.025))
#define SB_SHIP_GAUGE_Y 		(SB_SHIELD_GAUGE_Y+(grd_curscreen->sc_h*0.025))

#define SB_SHIELD_NUM_X 		(SB_SHIELD_GAUGE_X+(grd_curscreen->sc_w*0.0375))	//151
#define SB_SHIELD_NUM_Y 		(grd_curscreen->sc_h * 0.78)

#define NUMERICAL_GAUGE_X		(grd_curscreen->sc_w * 0.48125)
#define NUMERICAL_GAUGE_Y		(grd_curscreen->sc_h * 0.65)
#define NUMERICAL_GAUGE_W		(grd_curscreen->sc_w * 0.059375)
#define NUMERICAL_GAUGE_H		(grd_curscreen->sc_h * 0.11)

#define PRIMARY_W_PIC_X			(grd_curscreen->sc_w * 0.2)
#define PRIMARY_W_PIC_Y			(grd_curscreen->sc_h * 0.77)
#define PRIMARY_W_TEXT_X		(grd_curscreen->sc_w * 0.271875)
#define PRIMARY_W_TEXT_Y		(grd_curscreen->sc_h * 0.785)
#define PRIMARY_AMMO_X			(grd_curscreen->sc_w * 0.290625)
#define PRIMARY_AMMO_Y			(grd_curscreen->sc_h * 0.855)

#define SECONDARY_W_PIC_X		(grd_curscreen->sc_w * 	0.73125)
#define SECONDARY_W_PIC_Y		(grd_curscreen->sc_h * 0.77)
#define SECONDARY_W_TEXT_X		(grd_curscreen->sc_w * 	0.646875)
#define SECONDARY_W_TEXT_Y		(grd_curscreen->sc_h * 0.785)
#define SECONDARY_AMMO_X		(grd_curscreen->sc_w * 	0.665625)
#define SECONDARY_AMMO_Y		(grd_curscreen->sc_h * 0.855)

#define SB_LIVES_X				(grd_curscreen->sc_w * 	0.83125)
#define SB_LIVES_Y				(grd_curscreen->sc_h * 0.925)
#define SB_LIVES_LABEL_X		(grd_curscreen->sc_w * 	0.740625)
#define SB_LIVES_LABEL_Y		(SB_LIVES_Y+1)

#define SB_SCORE_RIGHT			(grd_curscreen->sc_w * 	0.940625)
#define SB_SCORE_Y				(grd_curscreen->sc_h * 0.79)
#define SB_SCORE_LABEL_X		(grd_curscreen->sc_w * 	0.740625)

#define SB_SCORE_ADDED_RIGHT	(grd_curscreen->sc_w * 	0.940625)
#define SB_SCORE_ADDED_Y		(grd_curscreen->sc_h * 0.825)

static int score_display;
static fix score_time;

static int old_score[2]				= { -1, -1 };
static int old_energy[2]			= { -1, -1 };
static int old_shields[2]			= { -1, -1 };
static int old_flags[2]				= { -1, -1 };
static int old_weapon[2][2]		= {{ -1, -1 },{-1,-1}};
static int old_ammo_count[2][2]	= {{ -1, -1 },{-1,-1}};
static int old_cloak[2]				= { 0, 0 };
static int old_lives[2]				= { -1, -1 };

static int invulnerable_frame = 0;

static int cloak_fade_state;		//0=steady, -1 fading out, 1 fading in 

#define WS_SET				0		//in correct state
#define WS_FADING_OUT	1
#define WS_FADING_IN		2

int weapon_box_states[2];
fix weapon_box_fade_values[2];

#define FADE_SCALE	(2*i2f(GR_FADE_LEVELS)/REARM_TIME)		// fade out and back in REARM_TIME, in fade levels per seconds (int)

typedef struct span {
	int l,r;
} span;
											
#define N_LEFT_WINDOW_SPANS  39
#define N_RIGHT_WINDOW_SPANS 43

#define PRIMARY_W_BOX_LEFT		(grd_curscreen->sc_w * 0.196875)
#define PRIMARY_W_BOX_TOP		(grd_curscreen->sc_h * 0.77)
#define PRIMARY_W_BOX_RIGHT		(PRIMARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.18125))
#define PRIMARY_W_BOX_BOT		(PRIMARY_W_BOX_TOP+N_LEFT_WINDOW_SPANS * ((float)grd_curscreen->sc_h / 200.0f)-1)
											
#define SECONDARY_W_BOX_LEFT	(grd_curscreen->sc_w * 0.63125)	//207
#define SECONDARY_W_BOX_TOP		(grd_curscreen->sc_h * 0.755)
#define SECONDARY_W_BOX_RIGHT	(grd_curscreen->sc_w * 0.821875)	//(SECONDARY_W_BOX_LEFT+54)
#define SECONDARY_W_BOX_BOT		(SECONDARY_W_BOX_TOP+N_RIGHT_WINDOW_SPANS*((float)grd_curscreen->sc_h / 200.0f)-1)

#define SB_PRIMARY_W_BOX_LEFT		(grd_curscreen->sc_w * 0.10625)		//50
#define SB_PRIMARY_W_BOX_TOP		(grd_curscreen->sc_h * 0.765)
#define SB_PRIMARY_W_BOX_RIGHT		(SB_PRIMARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.165625))
#define SB_PRIMARY_W_BOX_BOT		(grd_curscreen->sc_h * 0.975)
											
#define SB_SECONDARY_W_BOX_LEFT		(grd_curscreen->sc_w * 0.528125)	//210
#define SB_SECONDARY_W_BOX_TOP		(grd_curscreen->sc_h * 0.765)
#define SB_SECONDARY_W_BOX_RIGHT	(SB_SECONDARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.16875))
#define SB_SECONDARY_W_BOX_BOT		(grd_curscreen->sc_h * 0.98)

#define SB_PRIMARY_W_PIC_X		(SB_PRIMARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.003125))	//51
#define SB_PRIMARY_W_PIC_Y		(grd_curscreen->sc_h * 0.77)
#define SB_PRIMARY_W_TEXT_X		(SB_PRIMARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.075))	//(51+23)
#define SB_PRIMARY_W_TEXT_Y		(grd_curscreen->sc_h * 0.785)
#define SB_PRIMARY_AMMO_X		(SB_PRIMARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.09375))	//(51+32)
#define SB_PRIMARY_AMMO_Y		(grd_curscreen->sc_h * 0.855)

#define SB_SECONDARY_W_PIC_X		(SB_SECONDARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.090625))	//(212+27)
#define SB_SECONDARY_W_PIC_Y		(grd_curscreen->sc_h * 0.77)
#define SB_SECONDARY_W_TEXT_X		(SB_SECONDARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.00625))	//212
#define SB_SECONDARY_W_TEXT_Y		(grd_curscreen->sc_h * 0.785)
#define SB_SECONDARY_AMMO_X			(SB_SECONDARY_W_BOX_LEFT+(grd_curscreen->sc_w * 0.034375))	//(212+9)
#define SB_SECONDARY_AMMO_Y			(grd_curscreen->sc_h * 0.855)

typedef struct gauge_box {
	int left,top;
	int right,bot;		//maximal box
	int num_spans;
	span spanlist[43];	//list of left,right spans for copy
} gauge_box;

int	Color_0_31_0 = -1;

gauge_box get_gauge_box(int index) {
	int left_l[6] = {
		0,
		grd_curscreen->sc_w * 0.003125,
		grd_curscreen->sc_w * 0.00625,
		grd_curscreen->sc_w * 0.009375,
		grd_curscreen->sc_w * 0.0125,
		grd_curscreen->sc_w * 0.015625
	};
	int left_r[4] = {
		grd_curscreen->sc_w * 0.165625,
		grd_curscreen->sc_w * 0.1625,
		grd_curscreen->sc_w * 0.159375,
		grd_curscreen->sc_w * 0.15625
	};

	//store delta x values from left of box
	span weapon_window_left[] = {		//first span 67,154
		{ left_l[4],left_r[0] },
		{ left_l[4],left_r[0] },
		{ left_l[4],left_r[0] },
		{ left_l[4],left_r[0] },
		{ left_l[4],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[3],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[2],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[1],left_r[0] },
		{ left_l[0],left_r[0] },
		{ left_l[0],left_r[0] },
		{ left_l[0],left_r[0] },
		{ left_l[0],left_r[0] },
		{ left_l[0],left_r[1] },
		{ left_l[1],left_r[1] },
		{ left_l[2],left_r[2] },
		{ left_l[3],left_r[2] },
		{ left_l[4],left_r[3] },
		{ left_l[5],left_r[3] }
	};
	int right_l[10] = {
		0,
		grd_curscreen->sc_w * 0.003125,
		grd_curscreen->sc_w * 0.00625,
		grd_curscreen->sc_w * 0.009375,
		grd_curscreen->sc_w * 0.0125,
		grd_curscreen->sc_w * 0.015625,
		grd_curscreen->sc_w * 0.01875,
		grd_curscreen->sc_w * 0.021875,
		grd_curscreen->sc_w * 0.025,
		grd_curscreen->sc_w * 0.028125
	};
	int right_r[9] = {
		grd_curscreen->sc_w * 0.165625,
		grd_curscreen->sc_w * 0.16875,
		grd_curscreen->sc_w * 0.171875,
		grd_curscreen->sc_w * 0.175,
		grd_curscreen->sc_w * 0.178125,
		grd_curscreen->sc_w * 0.18125,
		grd_curscreen->sc_w * 0.184375,
		grd_curscreen->sc_w * 0.1875,
		grd_curscreen->sc_w * 0.190625
	};

	//store delta x values from left of box
	span weapon_window_right[] = {		//first span 207,154
		{ right_l[208 - 202],right_r[(255 - 202) - 53] },
		{ right_l[206 - 202],right_r[(257 - 202) - 53] },
		{ right_l[205 - 202],right_r[(258 - 202) - 53] },
		{ right_l[204 - 202],right_r[(259 - 202) - 53] },
		{ right_l[203 - 202],right_r[(260 - 202) - 53] },
		{ right_l[203 - 202],right_r[(260 - 202) - 53] },
		{ right_l[203 - 202],right_r[(260 - 202) - 53] },
		{ right_l[203 - 202],right_r[(260 - 202) - 53] },
		{ right_l[203 - 202],right_r[(260 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(261 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[203 - 202],right_r[(262 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[204 - 202],right_r[(263 - 202) - 53] },
		{ right_l[205 - 202],right_r[(263 - 202) - 53] },
		{ right_l[206 - 202],right_r[(262 - 202) - 53] },
		{ right_l[207 - 202],right_r[(261 - 202) - 53] },
		{ right_l[208 - 202],right_r[(260 - 202) - 53] },
		{ right_l[211 - 202],right_r[(255 - 202) - 53] }
	};

	//first two are primary & secondary
	//seconds two are the same for the status bar
	gauge_box gauge_boxes[] = {
		{ PRIMARY_W_BOX_LEFT,PRIMARY_W_BOX_TOP,PRIMARY_W_BOX_RIGHT,PRIMARY_W_BOX_BOT,N_LEFT_WINDOW_SPANS },
		{ SECONDARY_W_BOX_LEFT,SECONDARY_W_BOX_TOP,SECONDARY_W_BOX_RIGHT,SECONDARY_W_BOX_BOT,N_RIGHT_WINDOW_SPANS },

		{ SB_PRIMARY_W_BOX_LEFT,SB_PRIMARY_W_BOX_TOP,SB_PRIMARY_W_BOX_RIGHT,SB_PRIMARY_W_BOX_BOT,0,NULL },
		{ SB_SECONDARY_W_BOX_LEFT,SB_SECONDARY_W_BOX_TOP,SB_SECONDARY_W_BOX_RIGHT,SB_SECONDARY_W_BOX_BOT,0,NULL }
	};

	if (index == 0) {
		memcpy(gauge_boxes[0].spanlist, weapon_window_left, sizeof(span) * N_LEFT_WINDOW_SPANS);
	}
	else if (index == 1) {
		memcpy(gauge_boxes[1].spanlist, weapon_window_right, sizeof(span) * N_RIGHT_WINDOW_SPANS);
	}

	return gauge_boxes[index];
}

//copy a box from the off-screen buffer to the visible page
void copy_gauge_box(gauge_box *box,grs_bitmap *bm)
{

	if (box->spanlist) {
		int gauge_h = box->bot-box->top+1;
		int cnt,y,span_idx;

//gr_setcolor(BM_XRGB(31,0,0));

		for (cnt = 0, y = box->top; cnt < gauge_h; cnt++, y++) {
			span_idx = ((float)cnt / (float)gauge_h) * box->num_spans;
			gr_bm_ubitblt(box->spanlist[span_idx].r - box->spanlist[span_idx].l + 1, 1,
				box->left + box->spanlist[span_idx].l, y, box->left + box->spanlist[span_idx].l, y, bm, &grd_curcanv->cv_bitmap);
			//gr_scanline(box->left+box->spanlist[cnt].l,box->left+box->spanlist[cnt].r,y);
		}
	}
	else
		gr_bm_ubitblt(box->right-box->left+1,box->bot-box->top+1,
						box->left,box->top,box->left,box->top,
						bm,&grd_curcanv->cv_bitmap);
}

//fills in the coords of the hostage video window
void get_hostage_window_coords(int *x,int *y,int *w,int *h)
{
	if (Cockpit_mode == CM_STATUS_BAR) {
		*x = SB_SECONDARY_W_BOX_LEFT;
		*y = SB_SECONDARY_W_BOX_TOP;
		*w = SB_SECONDARY_W_BOX_RIGHT - SB_SECONDARY_W_BOX_LEFT + 1;
		*h = SB_SECONDARY_W_BOX_BOT - SB_SECONDARY_W_BOX_TOP + 1;
	}
	else {
		*x = SECONDARY_W_BOX_LEFT;
		*y = SECONDARY_W_BOX_TOP;
		*w = SECONDARY_W_BOX_RIGHT - SECONDARY_W_BOX_LEFT + 1;
		*h = SECONDARY_W_BOX_BOT - SECONDARY_W_BOX_TOP + 1;
	}

}

//these should be in gr.h 
#define cv_w  cv_bitmap.bm_w
#define cv_h  cv_bitmap.bm_h

#define HUD_MESSAGE_LENGTH 150
#define HUD_MAX_NUM 4
extern int HUD_nmessages, hud_first; // From hud.c
extern char HUD_messages[HUD_MAX_NUM][HUD_MESSAGE_LENGTH+5]; 

void hud_show_score()
{
	char	score_str[20];
	int	w, h, aw;

	if ((HUD_nmessages > 0) && (strlen(HUD_messages[hud_first]) > 38))
		return;

	gr_set_curfont( GAME_FONT );

	if ( ((Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP)) ) {
		sprintf(score_str, "%s: %5d", TXT_KILLS, Players[Player_num].net_kills_total);
	} else {
		sprintf(score_str, "%s: %5d", TXT_SCORE, Players[Player_num].score);
	}
	gr_get_string_size(score_str, &w, &h, &aw );

	if (Color_0_31_0 == -1)
		Color_0_31_0 = gr_getcolor(0,31,0);
	gr_set_fontcolor(Color_0_31_0, -1);

	gr_scale_printf(grd_curcanv->cv_w-f2i(fixmul(Scale_factor, i2f(w)))-2, 3, Scale_factor, Scale_factor, score_str);
}

void hud_show_score_added()
{
	int	color;
	int	w, h, aw;
	char	score_str[20];

	if ( (Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP) ) 
		return;

	if (score_display == 0)
		return;

	gr_set_curfont( GAME_FONT );

	score_time -= FrameTime;
	if (score_time > 0) {
		color = f2i(score_time * 20) + 10;

		if (color < 10) color = 10;
		if (color > 31) color = 31;

		if (Cheats_enabled)
			sprintf(score_str, "%s", TXT_CHEATER);
		else
			sprintf(score_str, "%5d", score_display);

		gr_get_string_size(score_str, &w, &h, &aw );
		gr_set_fontcolor(gr_getcolor(0, color, 0),-1 );
		gr_scale_printf(grd_curcanv->cv_w-f2i(fixmul(Scale_factor, i2f(w)))-2-10, f2i(fixmul(Scale_factor, i2f(GAME_FONT->ft_h)))+5, Scale_factor, Scale_factor,score_str);
	} else {
		score_time = 0;
		score_display = 0;
	}
	
}

void sb_show_score()
{	                                                                                                                                                                                                                                                             
	char	score_str[20];
	int x,y;
	int	w, h, aw;
	static int last_x[2]={-1,-1};
	int redraw_score;

	if (last_x[0] < 0) {
		last_x[0] = SB_SCORE_RIGHT;
	}
	if (last_x[1] < 0) {
		last_x[1] = SB_SCORE_RIGHT;
	}

	if ( (Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP) ) 
		redraw_score = -99;
	else
		redraw_score = -1;

	if (old_score[VR_current_page]==redraw_score) {
		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor(gr_getcolor(0,20,0),-1 );

		if ( (Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP) ) 
			gr_scale_printf(SB_SCORE_LABEL_X,SB_SCORE_Y, Scale_factor, Scale_factor, "%s:", TXT_KILLS);
		else
			gr_scale_printf(SB_SCORE_LABEL_X,SB_SCORE_Y, Scale_factor, Scale_factor, "%s:", TXT_SCORE);
	}

	gr_set_curfont( GAME_FONT );
	if ( (Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP) ) 
		sprintf(score_str, "%5d", Players[Player_num].net_kills_total);
	else
		sprintf(score_str, "%5d", Players[Player_num].score);
	gr_get_string_size(score_str, &w, &h, &aw );
	w *= f2fl(Scale_factor);

	x = SB_SCORE_RIGHT-w-(grd_curscreen->sc_w * 0.00625);
	y = SB_SCORE_Y;

	//erase old score
	gr_setcolor(BM_XRGB(0,0,0));
	gr_rect(last_x[VR_current_page],y,SB_SCORE_RIGHT,y+f2fl(Scale_factor)*GAME_FONT->ft_h);

	if ( (Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP) ) 
		gr_set_fontcolor(gr_getcolor(0,20,0),-1 );
	else
		gr_set_fontcolor(gr_getcolor(0,31,0),-1 );	

	gr_scale_printf(x,y, Scale_factor, Scale_factor,score_str);

	last_x[VR_current_page] = x;
}

void sb_show_score_added()
{
	int	color;
	int w, h, aw;
	char	score_str[32];
	int x;
	static int last_x[2] = { -1,-1 };
	static	int last_score_display[2] = { -1, -1};

	if (last_x[0] < 0) {
		last_x[0] = SB_SCORE_RIGHT;
	}
	if (last_x[1] < 0) {
		last_x[1] = SB_SCORE_RIGHT;
	}

	if ( (Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP) ) 
		return;

	if (score_display == 0)
		return;

	gr_set_curfont( GAME_FONT );

	score_time -= FrameTime;
	if (score_time > 0) {
		if (score_display != last_score_display[VR_current_page]) {
			gr_setcolor(BM_XRGB(0,0,0));
			gr_rect(last_x[VR_current_page],SB_SCORE_ADDED_Y,SB_SCORE_ADDED_RIGHT,SB_SCORE_ADDED_Y+f2fl(Scale_factor)*GAME_FONT->ft_h);
			last_score_display[VR_current_page] = score_display;
		}

		color = f2i(score_time * 20) + 10;

		if (color < 10) color = 10;
		if (color > 31) color = 31;

		if (Cheats_enabled)
			sprintf(score_str, "%s", TXT_CHEATER);
		else
			sprintf(score_str, "%5d", score_display);

		gr_get_string_size(score_str, &w, &h, &aw );
		w *= f2fl(Scale_factor);

		x = SB_SCORE_ADDED_RIGHT-w-(grd_curscreen->sc_w * 0.00625);

		gr_set_fontcolor(gr_getcolor(0, color, 0),-1 );
		gr_scale_printf(x, SB_SCORE_ADDED_Y, Scale_factor, Scale_factor, score_str);

		last_x[VR_current_page] = x;

	} else {
		//erase old score
		gr_setcolor(BM_XRGB(0,0,0));
		gr_rect(last_x[VR_current_page],SB_SCORE_ADDED_Y,SB_SCORE_ADDED_RIGHT,SB_SCORE_ADDED_Y+f2fl(Scale_factor)*GAME_FONT->ft_h);

		score_time = 0;
		score_display = 0;

	}
	
}

fix	Last_warning_beep_time[2] = {0,0};		//	Time we last played homing missile warning beep.

//	-----------------------------------------------------------------------------
void play_homing_warning(void)
{
	fix	beep_delay;

	if (Endlevel_sequence || Player_is_dead)
		return;

	if (Players[Player_num].homing_object_dist >= 0) {
		beep_delay = Players[Player_num].homing_object_dist/128;
		if (beep_delay > F1_0)
			beep_delay = F1_0;
		else if (beep_delay < F1_0/8)
			beep_delay = F1_0/8;

		if (GameTime - Last_warning_beep_time[VR_current_page] > beep_delay/2) {
			digi_play_sample( SOUND_HOMING_WARNING, F1_0 );
			Last_warning_beep_time[VR_current_page] = GameTime;
		}
	}
}

int	Last_homing_warning_shown[2]={-1,-1};

//	-----------------------------------------------------------------------------
void show_homing_warning(void)
{
	grs_point scale_pts[] = {
		{ HOMING_WARNING_X * 65536, HOMING_WARNING_Y * 65536 },
		{ HOMING_WARNING_X * 65536 + i2f(21), HOMING_WARNING_Y * 65536 + i2f(20) },
		{ HOMING_WARNING_X * 65536 + 21 * Scale_x, HOMING_WARNING_Y * 65536 + 20 * Scale_y }
	};

	if ((Cockpit_mode == CM_STATUS_BAR) || (Endlevel_sequence)) {
		if (Last_homing_warning_shown[VR_current_page] == 1) {
			PIGGY_PAGE_IN( Gauges[GAUGE_HOMING_WARNING_OFF] );
			scale_bitmap(&GameBitmaps[Gauges[GAUGE_HOMING_WARNING_OFF].index], scale_pts);
			Last_homing_warning_shown[VR_current_page] = 0;
		}
		return;
	}

	gr_set_current_canvas( get_current_game_screen() );

	if (Players[Player_num].homing_object_dist >= 0) {

		if (GameTime & 0x4000) {
			if (Last_homing_warning_shown[VR_current_page] != 1) {
				PIGGY_PAGE_IN(Gauges[GAUGE_HOMING_WARNING_ON]);
				scale_bitmap(&GameBitmaps[Gauges[GAUGE_HOMING_WARNING_ON].index], scale_pts);
				Last_homing_warning_shown[VR_current_page] = 1;
			}
		} else {
			if (Last_homing_warning_shown[VR_current_page] != 0) {
				PIGGY_PAGE_IN(Gauges[GAUGE_HOMING_WARNING_OFF]);
				scale_bitmap(&GameBitmaps[Gauges[GAUGE_HOMING_WARNING_OFF].index], scale_pts);
				Last_homing_warning_shown[VR_current_page] = 0;
			}
		}
	} else if (Last_homing_warning_shown[VR_current_page] != 0) {
		PIGGY_PAGE_IN(Gauges[GAUGE_HOMING_WARNING_OFF]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_HOMING_WARNING_OFF].index], scale_pts);
		Last_homing_warning_shown[VR_current_page] = 0;
	}

}

#define MAX_SHOWN_LIVES 4

void hud_show_homing_warning(void)
{
	if (Players[Player_num].homing_object_dist >= 0) {

		if (GameTime & 0x4000) {
			//gr_set_current_canvas(&VR_render_sub_buffer[0]);	//render off-screen
			gr_set_curfont( GAME_FONT );
			gr_set_fontcolor(gr_getcolor(0,31,0),-1 );
			gr_scale_printf(0x8000, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.04),Scale_factor, Scale_factor,TXT_LOCK);
		}
	}
}

void hud_show_keys(void)
{
	grs_point blue_scale_pts[] = {
		{ 2 * Scale_x, 24 * Scale_y },
		{ 2 * Scale_x + i2f(5), 24 * Scale_y + i2f(7) },
		{ 2 * Scale_x + 5 * Scale_factor, 24 * Scale_y + 7 * Scale_factor }
	};
	grs_point gold_scale_pts[] = {
		{ 10 * Scale_x, 24 * Scale_y },
		{ 10 * Scale_x + i2f(5), 24 * Scale_y + i2f(7) },
		{ 10 * Scale_x + 5 * Scale_factor, 24 * Scale_y + 7 * Scale_factor }
	};
	grs_point red_scale_pts[] = {
		{ 18 * Scale_x, 24 * Scale_y },
		{ 18 * Scale_x + i2f(5), 24 * Scale_y + i2f(7) },
		{ 18 * Scale_x + 5 * Scale_factor, 24 * Scale_y + 7 * Scale_factor }
	};

	if (Players[Player_num].flags & PLAYER_FLAGS_BLUE_KEY) {
		PIGGY_PAGE_IN(Gauges[KEY_ICON_BLUE]);
		scale_bitmap(&GameBitmaps[Gauges[KEY_ICON_BLUE].index], blue_scale_pts);

	}

	if (Players[Player_num].flags & PLAYER_FLAGS_GOLD_KEY) {
		PIGGY_PAGE_IN(Gauges[KEY_ICON_YELLOW]);
		scale_bitmap(&GameBitmaps[Gauges[KEY_ICON_YELLOW].index], gold_scale_pts);
	}

	if (Players[Player_num].flags & PLAYER_FLAGS_RED_KEY) {
		PIGGY_PAGE_IN(Gauges[KEY_ICON_RED]);
		scale_bitmap(&GameBitmaps[Gauges[KEY_ICON_RED].index], red_scale_pts);
	}

}

void hud_show_energy(void)
{
	//gr_set_current_canvas(&VR_render_sub_buffer[0]);	//render off-screen
	gr_set_curfont( GAME_FONT );
	gr_set_fontcolor(gr_getcolor(0,31,0),-1 );
	if (Game_mode & GM_MULTI)
		gr_scale_printf(grd_curscreen->sc_w*0.00625, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.2),
			Scale_factor, Scale_factor, "%s: %i", TXT_ENERGY, f2ir(Players[Player_num].energy));
	else
		gr_scale_printf(grd_curscreen->sc_w*0.00625, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.04),
			Scale_factor, Scale_factor, "%s: %i", TXT_ENERGY, f2ir(Players[Player_num].energy));

	if (Newdemo_state==ND_STATE_RECORDING ) {
		int energy = f2ir(Players[Player_num].energy);

		if (energy != old_energy[VR_current_page]) {
#ifdef SHAREWARE
			newdemo_record_player_energy(energy);
#else
			newdemo_record_player_energy(old_energy[VR_current_page], energy);
#endif
			old_energy[VR_current_page] = energy;
	 	}
	}
}

void hud_show_weapons(void)
{
	int	w, h, aw;
	int	y;
	char	weapon_str[32], temp_str[10];

//	gr_set_current_canvas(&VR_render_sub_buffer[0]);	//render off-screen
	gr_set_curfont( GAME_FONT );
	gr_set_fontcolor(gr_getcolor(0,31,0),-1 );

	if (Game_mode & GM_MULTI)
		y = grd_curcanv->cv_h-(grd_curscreen->sc_h*0.16);
	else
		y = grd_curcanv->cv_h;

//	#ifndef RELEASE
	y -= (grd_curscreen->sc_h*0.04);
//	#endif

	switch (Primary_weapon) {
		case 0:
			if (Players[Player_num].flags & PLAYER_FLAGS_QUAD_LASERS)
				sprintf(weapon_str, "%s %s %i", TXT_QUAD, TXT_LASER, Players[Player_num].laser_level+1);
			else
				sprintf(weapon_str, "%s %i", TXT_LASER, Players[Player_num].laser_level+1);
			break;
		case 1:
			sprintf(weapon_str, "%s: %i", TXT_W_VULCAN_S, f2i(Players[Player_num].primary_ammo[Primary_weapon] * VULCAN_AMMO_SCALE));
			break;
		case 2:
			strcpy(weapon_str, TXT_W_SPREADFIRE_S);
			break;
		#ifndef SHAREWARE
		case 3:
			strcpy(weapon_str, TXT_W_PLASMA_S);
			break;
		case 4:
			strcpy(weapon_str, TXT_W_FUSION_S);
			break;
		#endif
	}

	gr_get_string_size(weapon_str, &w, &h, &aw );
	w *= f2fl(Scale_factor);
	gr_scale_printf(grd_curcanv->cv_w-5-w, y-(grd_curscreen->sc_h*0.04), Scale_factor, Scale_factor, weapon_str);

	if (Primary_weapon == VULCAN_INDEX) {

#ifndef SHAREWARE
		if (Players[Player_num].primary_ammo[Primary_weapon] != old_ammo_count[0][VR_current_page]) {
			if (Newdemo_state == ND_STATE_RECORDING)
				newdemo_record_primary_ammo(old_ammo_count[0][VR_current_page], Players[Player_num].primary_ammo[Primary_weapon]);
			old_ammo_count[0][VR_current_page] = Players[Player_num].primary_ammo[Primary_weapon];
		}
#endif
	}

	switch (Secondary_weapon) {
		case 0:	strcpy(weapon_str, TXT_CONCUSSION);	break;
		case 1:	strcpy(weapon_str, TXT_HOMING);	break;
		case 2:	strcpy(weapon_str, TXT_PROXBOMB   );	break;
		#ifndef SHAREWARE
		case 3:	strcpy(weapon_str, TXT_SMART);	break;
		case 4:	strcpy(weapon_str, TXT_MEGA);	break;
		#endif
		default:	Int3();	weapon_str[0] = 0;	break;
	}

#ifndef SHAREWARE
	if (Players[Player_num].secondary_ammo[Secondary_weapon] != old_ammo_count[1][VR_current_page]) {
		if (Newdemo_state == ND_STATE_RECORDING)
			newdemo_record_secondary_ammo(old_ammo_count[1][VR_current_page], Players[Player_num].secondary_ammo[Secondary_weapon]);
		old_ammo_count[1][VR_current_page] = Players[Player_num].secondary_ammo[Secondary_weapon];
	}
#endif

	strcat(weapon_str, " ");
	sprintf(weapon_str, "%s%d", weapon_str, Players[Player_num].secondary_ammo[Secondary_weapon]);
	gr_get_string_size(weapon_str, &w, &h, &aw );
	w *= f2fl(Scale_factor);
	gr_scale_printf(grd_curcanv->cv_w-5-w, y, Scale_factor, Scale_factor, weapon_str);
}

void hud_show_cloak_invuln(void)
{
	if (Players[Player_num].flags & PLAYER_FLAGS_CLOAKED) {
		int	y = grd_curcanv->cv_h;

		if (Game_mode & GM_MULTI)
			y -= (grd_curscreen->sc_h*0.36);
		else
			y -= (grd_curscreen->sc_h*0.16);

		if ((Players[Player_num].cloak_time+CLOAK_TIME_MAX - GameTime > F1_0*3 ) || (GameTime & 0x8000))
			gr_scale_printf(grd_curscreen->sc_w*0.00625, y, Scale_factor, Scale_factor, "%s", TXT_CLOAKED);
	}

	if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE) {
		int	y = grd_curcanv->cv_h;

		if (Game_mode & GM_MULTI)
			y -= (grd_curscreen->sc_h*0.4);
		else
			y -= (grd_curscreen->sc_h*0.2);

		if (((Players[Player_num].invulnerable_time + INVULNERABLE_TIME_MAX - GameTime) > F1_0*4) || (GameTime & 0x8000))
			gr_scale_printf(grd_curscreen->sc_w*0.00625, y, Scale_factor, Scale_factor, "%s", TXT_INVULNERABLE);
	}

}

void hud_show_shield(void)
{
//	gr_set_current_canvas(&VR_render_sub_buffer[0]);	//render off-screen
	gr_set_curfont( GAME_FONT );
	gr_set_fontcolor(gr_getcolor(0,31,0),-1 );
	if ( Players[Player_num].shields >= 0 )	{
		if (Game_mode & GM_MULTI)
			gr_scale_printf(grd_curscreen->sc_w*0.00625, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.24),
				Scale_factor, Scale_factor, "%s: %i", TXT_SHIELD, f2ir(Players[Player_num].shields));
		else
			gr_scale_printf(grd_curscreen->sc_w*0.00625, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.08),
				Scale_factor, Scale_factor, "%s: %i", TXT_SHIELD, f2ir(Players[Player_num].shields));
	} else {
		if (Game_mode & GM_MULTI)
			gr_scale_printf(grd_curscreen->sc_w*0.00625, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.24),
				Scale_factor, Scale_factor, "%s: 0", TXT_SHIELD );
		else
			gr_scale_printf(grd_curscreen->sc_w*0.00625, grd_curcanv->cv_h-(grd_curscreen->sc_h*0.08),
				Scale_factor, Scale_factor, "%s: 0", TXT_SHIELD );
	}

	if (Newdemo_state==ND_STATE_RECORDING ) {
		int shields = f2ir(Players[Player_num].shields);

		if (shields != old_shields[VR_current_page]) {		// Draw the shield gauge
#ifdef SHAREWARE
			newdemo_record_player_shields(shields);
#else
			newdemo_record_player_shields(old_shields[VR_current_page], shields);
#endif
			old_shields[VR_current_page] = shields;
		}
	}
}

//draw the icons for number of lives
void hud_show_lives()
{
	grs_point scale_pts[] = {
		{ 10 * Scale_factor, 2 * Scale_factor },
		{ 10 * Scale_factor + i2f(8), 2 * Scale_factor + i2f(7) },
		{ 18 * Scale_factor, 9 * Scale_factor }
	};
	if ((HUD_nmessages > 0) && (strlen(HUD_messages[hud_first]) > 38))
		return;

	if (Game_mode & GM_MULTI) {
		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor(gr_getcolor(0,31,0),-1 );
		gr_printf(10 * f2fl(Scale_factor), 3 * f2fl(Scale_factor), Scale_factor, Scale_factor, "%s: %d", TXT_DEATHS, Players[Player_num].net_killed_total);
	} 
	else if (Players[Player_num].lives > 1)  {
		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor(gr_getcolor(0,20,0),-1 );
		PIGGY_PAGE_IN(Gauges[GAUGE_LIVES]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_LIVES].index],scale_pts);
		gr_scale_printf(22 * f2fl(Scale_factor), 3 * f2fl(Scale_factor), Scale_factor, Scale_factor, "x %d", Players[Player_num].lives-1);
	}

}

void sb_show_lives()
{
	int x,y;
	grs_bitmap * bm = &GameBitmaps[Gauges[GAUGE_LIVES].index];
	x = SB_LIVES_X;
	y = SB_LIVES_Y;
	grs_point scale_pts[] = {
		{ i2f(x), i2f(y) },
		{ i2f(x) + i2f(8), i2f(y) + i2f(7) },
		{ i2f(x) + 8 * Scale_factor, i2f(y) + 7 * Scale_factor }
	};

	if (old_lives[VR_current_page]==-1) {
		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor(gr_getcolor(0,20,0),-1 );
		if (Game_mode & GM_MULTI)
			gr_scale_printf(SB_LIVES_LABEL_X,SB_LIVES_LABEL_Y, Scale_factor, Scale_factor,"%s:", TXT_DEATHS);
		else
			gr_scale_printf(SB_LIVES_LABEL_X,SB_LIVES_LABEL_Y, Scale_factor, Scale_factor, "%s:", TXT_LIVES);
	}

	if (Game_mode & GM_MULTI)
	{
		char killed_str[20];
		int w, h, aw;
		static int last_x[2] = {-1,-1};
		int x;

		if (last_x[0] < 0) {
			last_x[0] = SB_SCORE_RIGHT;
		}
		if (last_x[1] < 0) {
			last_x[1] = SB_SCORE_RIGHT;
		}

		sprintf(killed_str, "%5d", Players[Player_num].net_killed_total);
		gr_get_string_size(killed_str, &w, &h, &aw);
		w *-f2fl(Scale_factor);
		gr_setcolor(BM_XRGB(0,0,0));
		gr_rect(last_x[VR_current_page], y+1, SB_SCORE_RIGHT, y+f2fl(Scale_factor)*GAME_FONT->ft_h);
		gr_set_fontcolor(gr_getcolor(0,20,0),-1);
		x = SB_SCORE_RIGHT-w-2;		
		gr_scale_printf(x, y+1, Scale_factor, Scale_factor, killed_str);
		last_x[VR_current_page] = x;
		return;
	}

	if (old_lives[VR_current_page]==-1 || Players[Player_num].lives != old_lives[VR_current_page]) {

		//erase old icons

		gr_setcolor(BM_XRGB(0,0,0));
		gr_rect(x, y, x+(grd_curscreen->sc_w*0.1), y+bm->bm_h);

		if (Players[Player_num].lives-1 > 0) {
			gr_set_curfont( GAME_FONT );
			gr_set_fontcolor(gr_getcolor(0,20,0),-1 );
			PIGGY_PAGE_IN(Gauges[GAUGE_LIVES]);
			scale_bitmap(bm,scale_pts);
			gr_scale_printf(x+(grd_curscreen->sc_w * 0.0375), y, Scale_factor, Scale_factor, "x %d", Players[Player_num].lives-1);
		}
	}

//	for (i=0;i<draw_count;i++,x+=bm->bm_w+2)
//		gr_ubitmapm(x,y,bm);

}

#ifndef RELEASE

#ifdef PIGGY_USE_PAGING
extern int Piggy_bitmap_cache_next;
#endif

void show_time()
{
	int secs = f2i(Players[Player_num].time_level) % 60;
	int mins = f2i(Players[Player_num].time_level) / 60;

	gr_set_curfont( GAME_FONT );

	if (Color_0_31_0 == -1)
		Color_0_31_0 = gr_getcolor(0,31,0);
	gr_set_fontcolor(Color_0_31_0, -1 );

	gr_printf(grd_curcanv->cv_w-25,grd_curcanv->cv_h-28,"%d:%02d", mins, secs);

#ifdef PIGGY_USE_PAGING
	{
		char text[25];
		int w,h,aw;
		sprintf( text, "%d KB", Piggy_bitmap_cache_next/1024 );
		gr_get_string_size( text, &w, &h, &aw );	
		gr_printf(grd_curcanv->cv_w-10-w,grd_curcanv->cv_h/2, text );
	}
#endif

}
#endif

#define EXTRA_SHIP_SCORE	50000		//get new ship every this many points

void add_points_to_score(int points) 
{
	int prev_score;

	score_time += f1_0*2;
	score_display += points;
	if (score_time > f1_0*4) score_time = f1_0*4;

	if (points == 0 || Cheats_enabled)
		return;

	if ((Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP))
		return;

	prev_score=Players[Player_num].score;

	Players[Player_num].score += points;

#ifndef SHAREWARE
	if (Newdemo_state == ND_STATE_RECORDING)
		newdemo_record_player_score(points);
#endif

#ifndef SHAREWARE
#ifdef NETWORK
	if (Game_mode & GM_MULTI_COOP)
		multi_send_score();
#endif
#endif

	if (Game_mode & GM_MULTI)
		return;

	if (Players[Player_num].score/EXTRA_SHIP_SCORE != prev_score/EXTRA_SHIP_SCORE) {
		int snd;
		Players[Player_num].lives += Players[Player_num].score/EXTRA_SHIP_SCORE - prev_score/EXTRA_SHIP_SCORE;
		powerup_basic(20, 20, 20, 0, TXT_EXTRA_LIFE);
		if ((snd=Powerup_info[POW_EXTRA_LIFE].hit_sound) > -1 )
			digi_play_sample( snd, F1_0 );
	}
}

void add_bonus_points_to_score(int points) 
{
	int prev_score;

	if (points == 0 || Cheats_enabled)
		return;

	prev_score=Players[Player_num].score;

	Players[Player_num].score += points;


#ifndef SHAREWARE
	if (Newdemo_state == ND_STATE_RECORDING)
		newdemo_record_player_score(points);
#endif

	if (Game_mode & GM_MULTI)
		return;

	if (Players[Player_num].score/EXTRA_SHIP_SCORE != prev_score/EXTRA_SHIP_SCORE) {
		int snd;
		Players[Player_num].lives += Players[Player_num].score/EXTRA_SHIP_SCORE - prev_score/EXTRA_SHIP_SCORE;
		if ((snd=Powerup_info[POW_EXTRA_LIFE].hit_sound) > -1 )
			digi_play_sample( snd, F1_0 );
	}
}

void init_gauge_canvases()
{
	Canv_LeftEnergyGauge = gr_create_canvas( LEFT_ENERGY_GAUGE_W, LEFT_ENERGY_GAUGE_H );
	Canv_SBEnergyGauge = gr_create_canvas( SB_ENERGY_GAUGE_W, SB_ENERGY_GAUGE_H );
	Canv_RightEnergyGauge = gr_create_canvas( RIGHT_ENERGY_GAUGE_W, RIGHT_ENERGY_GAUGE_H );
	Canv_NumericalGauge = gr_create_canvas( NUMERICAL_GAUGE_W, NUMERICAL_GAUGE_H );
}

void close_gauge_canvases()
{
	gr_free_canvas( Canv_LeftEnergyGauge );
	gr_free_canvas( Canv_SBEnergyGauge );
	gr_free_canvas( Canv_RightEnergyGauge );
	gr_free_canvas( Canv_NumericalGauge );
}

void init_gauges()
{
	int i;

	//draw_gauges_on 	= 1;

	for (i=0; i<2; i++ )	{
		if ( ((Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP)) || ((Newdemo_state == ND_STATE_PLAYBACK) && (Newdemo_game_mode & GM_MULTI) && !(Newdemo_game_mode & GM_MULTI_COOP)) ) 
			old_score[i] = -99;
		else
			old_score[i]			= -1;
		old_energy[i]			= -1;
		old_shields[i]			= -1;
		old_flags[i]			= -1;
		old_cloak[i]			= -1;
		old_lives[i]			= -1;
	
		old_weapon[0][i] = old_weapon[1][i] = -1;
		old_ammo_count[0][i] = old_ammo_count[1][i] = -1;
	}

	cloak_fade_state = 0;
}

void draw_energy_bar(int energy)
{
	int not_energy;
	int x1, x2, y;
	grs_point left_energy_scale_pts[] = {
		{ 0, 0 },
		{ i2f(64), i2f(8) },
		{ LEFT_ENERGY_GAUGE_W * 65536, LEFT_ENERGY_GAUGE_H * 65536 }
	};
	grs_point right_energy_scale_pts[] = {
		{ 0, 0 },
		{ i2f(64), i2f(8) },
		{ RIGHT_ENERGY_GAUGE_W * 65536, RIGHT_ENERGY_GAUGE_H * 65536 }
	};

	// Draw left energy bar
	gr_set_current_canvas( Canv_LeftEnergyGauge );
	gr_clear_canvas(255);
	PIGGY_PAGE_IN(Gauges[GAUGE_ENERGY_LEFT]);
	scale_bitmap(&GameBitmaps[Gauges[GAUGE_ENERGY_LEFT].index], left_energy_scale_pts);
	gr_setcolor( 0 );

	not_energy = (grd_curscreen->sc_w * 0.190625) - (energy*(grd_curscreen->sc_w * 0.190625))/100;

	if (energy < 100)
		for (y=0; y<LEFT_ENERGY_GAUGE_H; y++) {
			x1 = (grd_curscreen->sc_w * 0.021875) - y;
			x2 = (grd_curscreen->sc_w * 0.021875) - y + not_energy;
	
			if ( y>=0 && y<2 ) if (x2 > LEFT_ENERGY_GAUGE_W - 1) x2 = LEFT_ENERGY_GAUGE_W - 1;
			if ( y>=2 && y<(grd_curscreen->sc_h * 0.03)) if (x2 > LEFT_ENERGY_GAUGE_W - 2) x2 = LEFT_ENERGY_GAUGE_W - 2;
			if ( y>= (grd_curscreen->sc_h * 0.03) ) if (x2 > LEFT_ENERGY_GAUGE_W - 3) x2 = LEFT_ENERGY_GAUGE_W - 3;
			
			if (x2 > x1) gr_uscanline( x1, x2, y ); 
		}

	gr_set_current_canvas( get_current_game_screen() );
	gr_ubitmapm( LEFT_ENERGY_GAUGE_X, LEFT_ENERGY_GAUGE_Y, &Canv_LeftEnergyGauge->cv_bitmap );

	// Draw right energy bar
	gr_set_current_canvas( Canv_RightEnergyGauge );
	gr_clear_canvas(255);
	PIGGY_PAGE_IN(Gauges[GAUGE_ENERGY_RIGHT]);
	scale_bitmap(&GameBitmaps[Gauges[GAUGE_ENERGY_RIGHT].index], right_energy_scale_pts);
	gr_setcolor(0);

	if (energy < 100)
		for (y=0; y<LEFT_ENERGY_GAUGE_H; y++) {
			x1 = RIGHT_ENERGY_GAUGE_W - (grd_curscreen->sc_w * 0.01875) + y - not_energy;
			x2 = RIGHT_ENERGY_GAUGE_W - (grd_curscreen->sc_w * 0.01875) + y;
	
			if ( y>=0 && y<2 ) if (x1 < 0) x1 = 0;
			if ( y>=2 && y<(grd_curscreen->sc_h * 0.03)) if (x1 < 1) x1 = 1;
			if ( y>= (grd_curscreen->sc_h * 0.03)) if (x1 < 2) x1 = 2;
			
			if (x2 > x1) gr_uscanline( x1, x2, y ); 
		}

	gr_set_current_canvas( get_current_game_screen() );
	gr_ubitmapm( RIGHT_ENERGY_GAUGE_X, RIGHT_ENERGY_GAUGE_Y, &Canv_RightEnergyGauge->cv_bitmap );

}

void draw_shield_bar(int shield)
{
	int bm_num = shield>=100?9:(shield / 10);
	fix scale_x = fixdiv(i2f(grd_curscreen->sc_w), i2f(320));
	fix scale_y = fixdiv(i2f(grd_curscreen->sc_h), i2f(200));
	PIGGY_PAGE_IN(Gauges[GAUGE_SHIELDS + 9 - bm_num]);
	grs_bitmap *bm = &GameBitmaps[Gauges[GAUGE_SHIELDS + 9 - bm_num].index];
	grs_point scale_pts[] = {
		{ SHIELD_GAUGE_X * 65536, SHIELD_GAUGE_Y * 65536 },
		{ SHIELD_GAUGE_X * 65536 + i2f(bm->bm_w), SHIELD_GAUGE_Y * 65536 + i2f(bm->bm_h) },
		{ SHIELD_GAUGE_X * 65536 + fixmul(i2f(bm->bm_w), scale_x), SHIELD_GAUGE_Y * 65536 + fixmul(i2f(bm->bm_h), scale_y) }
	};
	scale_bitmap( bm, scale_pts );

}

#define CLOAK_FADE_WAIT_TIME  0x400

void draw_player_ship(int cloak_state,int old_cloak_state,int x, int y)
{
	static fix cloak_fade_timer=0;
	static int cloak_fade_value=GR_FADE_LEVELS-1;
	grs_bitmap *bm;
	fix scale_x, scale_y;
	int scale_w, scale_h;

	if (Game_mode & GM_TEAM)	{
		#ifdef NETWORK
		PIGGY_PAGE_IN(Gauges[GAUGE_SHIPS+get_team(Player_num)]);
		bm = &GameBitmaps[Gauges[GAUGE_SHIPS+get_team(Player_num)].index];
		#endif
	} else {
		PIGGY_PAGE_IN(Gauges[GAUGE_SHIPS+Player_num]);
		bm = &GameBitmaps[Gauges[GAUGE_SHIPS+Player_num].index];
	}
	
	scale_x = fixdiv(i2f(grd_curscreen->sc_w), i2f(320));
	scale_y = fixdiv(i2f(grd_curscreen->sc_h), i2f(200));
	scale_w = bm->bm_w * f2fl(scale_x);
	scale_h = bm->bm_h * f2fl(scale_y);
	grs_point scale_pts[] = {
		{ i2f(x), i2f(y) },
		{ i2f(x) + i2f(bm->bm_w), i2f(y) + i2f(bm->bm_h) },
		{ i2f(x) + fixmul(i2f(bm->bm_w), scale_x), i2f(y) + fixmul(i2f(bm->bm_h), scale_y) }
	};

	if (old_cloak_state==-1 && cloak_state)
			cloak_fade_value=0;

	if (!cloak_state) {
		cloak_fade_value=GR_FADE_LEVELS-1;
		cloak_fade_state = 0;
	}

	if (cloak_state==1 && old_cloak_state==0)
		cloak_fade_state = -1;
	//else if (cloak_state==0 && old_cloak_state==1)
	//	cloak_fade_state = 1;

	if (cloak_state==old_cloak_state)		//doing "about-to-uncloak" effect
		if (cloak_fade_state==0)
			cloak_fade_state = 2;
	

	if (cloak_fade_state)
		cloak_fade_timer -= FrameTime;

	while (cloak_fade_state && cloak_fade_timer < 0) {

		cloak_fade_timer += CLOAK_FADE_WAIT_TIME;

		cloak_fade_value += cloak_fade_state;

		if (cloak_fade_value >= GR_FADE_LEVELS-1) {
			cloak_fade_value = GR_FADE_LEVELS-1;
			if (cloak_fade_state == 2 && cloak_state)
				cloak_fade_state = -2;
			else
				cloak_fade_state = 0;
		}
		else if (cloak_fade_value <= 0) {
			cloak_fade_value = 0;
			if (cloak_fade_state == -2)
				cloak_fade_state = 2;
			else
				cloak_fade_state = 0;
		}
	}

	gr_set_current_canvas(&VR_render_buffer[0]);
	gr_clear_canvas(255); // DANGER! Potentially expensive op!
	scale_bitmap(bm, scale_pts);

	Gr_scanline_darkening_level = cloak_fade_value;
	gr_rect(x, y, x+scale_w-1, y+scale_h-1);
	Gr_scanline_darkening_level = GR_FADE_LEVELS;

	gr_set_current_canvas(get_current_game_screen());
	gr_bm_ubitbltm(scale_w, scale_h, x, y, x, y, &VR_render_buffer[0].cv_bitmap, &grd_curcanv->cv_bitmap);

}

#define INV_FRAME_TIME	(f1_0/10)		//how long for each frame

void draw_numerical_display(int shield, int energy)
{
	// Get scaling for font
	grs_point scale_pts[] = {
		{ 0, 0 },
		{ i2f(19), i2f(22) },
		{ NUMERICAL_GAUGE_W * 65536, NUMERICAL_GAUGE_H * 65536 }
	};

	gr_set_current_canvas( Canv_NumericalGauge );
	gr_clear_canvas(255);
	gr_set_curfont( GAME_FONT );
	PIGGY_PAGE_IN(Gauges[GAUGE_NUMERICAL]);
	scale_bitmap(&GameBitmaps[Gauges[GAUGE_NUMERICAL].index], scale_pts);

	gr_set_fontcolor(gr_getcolor(14,14,23),-1 );

	gr_scale_printf((shield>99)?grd_curscreen->sc_w*0.0125:((shield>9)?grd_curscreen->sc_w*0.01875:grd_curscreen->sc_w*0.025),
		grd_curscreen->sc_h*0.075, Scale_factor, Scale_factor,"%d",shield);

	gr_set_fontcolor(gr_getcolor(25,18,6),-1 );
	gr_scale_printf((energy>99)?grd_curscreen->sc_w*0.0125:((energy>9)?grd_curscreen->sc_w*0.01875:grd_curscreen->sc_w*0.025),
		grd_curscreen->sc_h*0.01, Scale_factor, Scale_factor,"%d",energy);
					  
	gr_set_current_canvas( get_current_game_screen() );
	gr_ubitmapm( NUMERICAL_GAUGE_X, NUMERICAL_GAUGE_Y, &Canv_NumericalGauge->cv_bitmap );
}


void draw_keys()
{
	fix scale_x = fixdiv(i2f(grd_curscreen->sc_w), i2f(320));
	fix scale_y = fixdiv(i2f(grd_curscreen->sc_h), i2f(200));
	grs_point blue_scale_pts[3] = {
		{ GAUGE_BLUE_KEY_X * 65536, GAUGE_BLUE_KEY_Y * 65536 },
		{ (GAUGE_BLUE_KEY_X * 65536) + i2f(11), (GAUGE_BLUE_KEY_Y * 65536) + i2f(8) },
		{ (GAUGE_BLUE_KEY_X * 65536) + 11 * scale_x, (GAUGE_BLUE_KEY_Y * 65536) + 8 * scale_y }
	};
	grs_point gold_scale_pts[3] = {
		{ GAUGE_GOLD_KEY_X * 65536, GAUGE_GOLD_KEY_Y * 65536 },
		{ (GAUGE_GOLD_KEY_X * 65536) + i2f(11), (GAUGE_GOLD_KEY_Y * 65536) + i2f(7) },
		{ (GAUGE_GOLD_KEY_X * 65536) + 11 * scale_x, (GAUGE_GOLD_KEY_Y * 65536) + 8 * scale_y }
	};
	grs_point red_scale_pts[3] = {
		{ GAUGE_RED_KEY_X * 65536, GAUGE_RED_KEY_Y * 65536 },
		{ (GAUGE_RED_KEY_X * 65536) + i2f(11), (GAUGE_RED_KEY_Y * 65536) + f2i(7) },
		{ (GAUGE_RED_KEY_X * 65536) + 11 * scale_x, (GAUGE_RED_KEY_Y * 65536) + 8 * scale_y }
	};

	gr_set_current_canvas( get_current_game_screen() );

	if (Players[Player_num].flags & PLAYER_FLAGS_BLUE_KEY )	{
		PIGGY_PAGE_IN(Gauges[GAUGE_BLUE_KEY]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_BLUE_KEY].index], blue_scale_pts);
	} else {
		PIGGY_PAGE_IN(Gauges[GAUGE_BLUE_KEY_OFF]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_BLUE_KEY_OFF].index], blue_scale_pts);
	}

	if (Players[Player_num].flags & PLAYER_FLAGS_GOLD_KEY)	{
		PIGGY_PAGE_IN(Gauges[GAUGE_GOLD_KEY]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_GOLD_KEY].index], gold_scale_pts);
	} else {
		PIGGY_PAGE_IN(Gauges[GAUGE_GOLD_KEY_OFF]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_GOLD_KEY_OFF].index], gold_scale_pts);
	}

	if (Players[Player_num].flags & PLAYER_FLAGS_RED_KEY)	{
		PIGGY_PAGE_IN( Gauges[GAUGE_RED_KEY] );
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_RED_KEY].index], red_scale_pts);
	} else {
		PIGGY_PAGE_IN(Gauges[GAUGE_RED_KEY_OFF]);
		scale_bitmap(&GameBitmaps[Gauges[GAUGE_RED_KEY_OFF].index], red_scale_pts);
	}
}


void draw_weapon_info_sub(int info_index,gauge_box *box,int pic_x,int pic_y,char *name,int text_x,int text_y)
{
	grs_bitmap *bm;
	char *p;

	//clear the window
	gr_setcolor(BM_XRGB(0,0,0));
	gr_rect(box->left,box->top,box->right,box->bot);

	bm=&GameBitmaps[Weapon_info[info_index].picture.index];
	Assert(bm != NULL);

	PIGGY_PAGE_IN( Weapon_info[info_index].picture );
	grs_point pic_scale_pts[] = {
		{ i2f(pic_x), i2f(pic_y) },
		{ i2f(pic_x) + i2f(bm->bm_w), i2f(pic_y) + i2f(bm->bm_h) },
		{ i2f(pic_x) + fixmul(i2f(bm->bm_w), Scale_x), i2f(pic_y) + fixmul(i2f(bm->bm_h), Scale_y) }
	};
	scale_bitmap(bm, pic_scale_pts);

	gr_set_fontcolor(gr_getcolor(0,20,0),-1 );

	if ((p=strchr(name,'\n'))!=NULL) {
		*p=0;
		gr_scale_printf(text_x,text_y, Scale_factor, Scale_factor,name);
		gr_scale_printf(text_x,text_y+(grd_curcanv->cv_font->ft_h+1)*f2i(Scale_factor), Scale_factor, Scale_factor,p+1);
		*p='\n';
	} else
		gr_scale_printf(text_x,text_y, Scale_factor, Scale_factor,name);

	//	For laser, show level and quadness
	if (info_index == 0) {
		char	temp_str[7];

		sprintf(temp_str, "%s: 0", TXT_LVL);

		temp_str[5] = Players[Player_num].laser_level+1 + '0';

		gr_scale_printf(text_x,text_y+(8*f2i(Scale_factor)), Scale_factor, Scale_factor,temp_str);

		if (Players[Player_num].flags & PLAYER_FLAGS_QUAD_LASERS) {
			strcpy(temp_str, TXT_QUAD);
			gr_scale_printf(text_x,text_y+(16*f2i(Scale_factor)), Scale_factor, Scale_factor,temp_str);
		}

	}
}


void draw_weapon_info(int weapon_type,int weapon_num)
{
	gauge_box gb;

#ifdef SHAREWARE
	if (Newdemo_state==ND_STATE_RECORDING )
		newdemo_record_player_weapon(weapon_type, weapon_num);
#endif
	if (weapon_type == 0)
		if (Cockpit_mode == CM_STATUS_BAR) {
			gr_set_current_canvas(&VR_screen_pages[0]);
			gb = get_gauge_box(2);
			draw_weapon_info_sub(Primary_weapon_to_weapon_info[weapon_num],
				&gb,
				SB_PRIMARY_W_PIC_X, SB_PRIMARY_W_PIC_Y,
				PRIMARY_WEAPON_NAMES_SHORT(weapon_num),
				SB_PRIMARY_W_TEXT_X, SB_PRIMARY_W_TEXT_Y);
			gr_set_current_canvas(get_current_game_screen());
		}
		else {
			gb = get_gauge_box(0);
			draw_weapon_info_sub(Primary_weapon_to_weapon_info[weapon_num],
				&gb,
				PRIMARY_W_PIC_X, PRIMARY_W_PIC_Y,
				PRIMARY_WEAPON_NAMES_SHORT(weapon_num),
				PRIMARY_W_TEXT_X, PRIMARY_W_TEXT_Y);
		}
	else
		if (Cockpit_mode == CM_STATUS_BAR) {
			gr_set_current_canvas(&VR_screen_pages[0]);
			gb = get_gauge_box(3);
			draw_weapon_info_sub(Secondary_weapon_to_weapon_info[weapon_num],
				&gb,
				SB_SECONDARY_W_PIC_X, SB_SECONDARY_W_PIC_Y,
				SECONDARY_WEAPON_NAMES_SHORT(weapon_num),
				SB_SECONDARY_W_TEXT_X, SB_SECONDARY_W_TEXT_Y);
			gr_set_current_canvas(get_current_game_screen());
		}
		else {
			gb = get_gauge_box(1);
			draw_weapon_info_sub(Secondary_weapon_to_weapon_info[weapon_num],
				&gb,
				SECONDARY_W_PIC_X, SECONDARY_W_PIC_Y,
				SECONDARY_WEAPON_NAMES_SHORT(weapon_num),
				SECONDARY_W_TEXT_X, SECONDARY_W_TEXT_Y);
		}
}

void draw_ammo_info(int x,int y,int ammo_count,int primary)
{
	int w;

	if (primary)
		w = ((grd_curcanv->cv_font->ft_w)*f2i(Scale_factor)*6)/2;
	else
		w = ((grd_curcanv->cv_font->ft_w)*f2i(Scale_factor)*5)/2;

	gr_setcolor(BM_XRGB(0,0,0));
	gr_rect(x,y,x+w,y+(grd_curcanv->cv_font->ft_h+2)*f2i(Scale_factor));

	gr_set_fontcolor(gr_getcolor(20,0,0),-1 );
	gr_scale_printf(x,y, Scale_factor, Scale_factor,"%03d",ammo_count);
}

void draw_primary_ammo_info(int ammo_count)
{
	if (Cockpit_mode == CM_STATUS_BAR)
		draw_ammo_info(SB_PRIMARY_AMMO_X,SB_PRIMARY_AMMO_Y,ammo_count,1);
	else
		draw_ammo_info(PRIMARY_AMMO_X,PRIMARY_AMMO_Y,ammo_count,1);
}

void draw_secondary_ammo_info(int ammo_count)
{
	if (Cockpit_mode == CM_STATUS_BAR)
		draw_ammo_info(SB_SECONDARY_AMMO_X,SB_SECONDARY_AMMO_Y,ammo_count,0);
	else
		draw_ammo_info(SECONDARY_AMMO_X,SECONDARY_AMMO_Y,ammo_count,0);
}

//returns true if drew picture
int draw_weapon_box(int weapon_type,int weapon_num)
{
	int drew_flag=0;

	gr_set_current_canvas(&VR_render_buffer[0]);
	gr_set_curfont( GAME_FONT );

	if (weapon_num != old_weapon[weapon_type][VR_current_page] && weapon_box_states[weapon_type] == WS_SET) {
		weapon_box_states[weapon_type] = WS_FADING_OUT;
		weapon_box_fade_values[weapon_type]=i2f(GR_FADE_LEVELS-1);
	}
		
	if (old_weapon[weapon_type][VR_current_page] == -1) {
		draw_weapon_info(weapon_type,weapon_num);
		old_weapon[weapon_type][VR_current_page] = weapon_num;
		old_ammo_count[weapon_type][VR_current_page]=-1;
		drew_flag=1;
		weapon_box_states[weapon_type] = WS_SET;
	}

	if (weapon_box_states[weapon_type] == WS_FADING_OUT) {
		draw_weapon_info(weapon_type,old_weapon[weapon_type][VR_current_page]);
		old_ammo_count[weapon_type][VR_current_page]=-1;
		drew_flag=1;
		weapon_box_fade_values[weapon_type] -= FrameTime * FADE_SCALE;
		if (weapon_box_fade_values[weapon_type] <= 0) {
			weapon_box_states[weapon_type] = WS_FADING_IN;
			old_weapon[weapon_type][VR_current_page] = weapon_num;
			weapon_box_fade_values[weapon_type] = 0;
		}
	}
	else if (weapon_box_states[weapon_type] == WS_FADING_IN) {
		if (weapon_num != old_weapon[weapon_type][VR_current_page]) {
			weapon_box_states[weapon_type] = WS_FADING_OUT;
		}
		else {
			draw_weapon_info(weapon_type,weapon_num);
			old_ammo_count[weapon_type][VR_current_page]=-1;
			drew_flag=1;
			weapon_box_fade_values[weapon_type] += FrameTime * FADE_SCALE;
			if (weapon_box_fade_values[weapon_type] >= i2f(GR_FADE_LEVELS-1))
				weapon_box_states[weapon_type] = WS_SET;
		}
	}

	if (weapon_box_states[weapon_type] != WS_SET) {		//fade gauge
		int fade_value = f2i(weapon_box_fade_values[weapon_type]);
		int boxofs = (Cockpit_mode==CM_STATUS_BAR)?2:0;
		gauge_box gb = get_gauge_box(boxofs + weapon_type);

		Gr_scanline_darkening_level = fade_value;
		gr_rect(gb.left, gb.top, gb.right, gb.bot);
		Gr_scanline_darkening_level = GR_FADE_LEVELS;
	}

	gr_set_current_canvas(get_current_game_screen());

	return drew_flag;


}

void draw_weapon_boxes()
{
	int boxofs = (Cockpit_mode==CM_STATUS_BAR)?2:0;
	int drew;
	gauge_box gb;

	drew = draw_weapon_box(0,Primary_weapon);
	if (drew) {
		gb = get_gauge_box(boxofs + 0);
		copy_gauge_box(&gb, &VR_render_buffer[0].cv_bitmap);
	}

	if (weapon_box_states[0] == WS_SET)
		if (Players[Player_num].primary_ammo[Primary_weapon] != old_ammo_count[0][VR_current_page]) {
			if (Primary_weapon == VULCAN_INDEX) {
#ifndef SHAREWARE
				if (Newdemo_state == ND_STATE_RECORDING)
					newdemo_record_primary_ammo(old_ammo_count[0][VR_current_page], Players[Player_num].primary_ammo[Primary_weapon]);
#endif
				draw_primary_ammo_info(f2i(VULCAN_AMMO_SCALE * Players[Player_num].primary_ammo[Primary_weapon]));
				old_ammo_count[0][VR_current_page] = Players[Player_num].primary_ammo[Primary_weapon];
			}
		}

	if (!hostage_is_vclip_playing()) {
		drew = draw_weapon_box(1,Secondary_weapon);
		if (drew) {
			gb = get_gauge_box(boxofs + 1);
			copy_gauge_box(&gb, &VR_render_buffer[0].cv_bitmap);
		}

		if (weapon_box_states[1] == WS_SET)
			if (Players[Player_num].secondary_ammo[Secondary_weapon] != old_ammo_count[1][VR_current_page]) {
#ifndef SHAREWARE
				if (Newdemo_state == ND_STATE_RECORDING)
					newdemo_record_secondary_ammo(old_ammo_count[1][VR_current_page], Players[Player_num].secondary_ammo[Secondary_weapon]);
#endif
				draw_secondary_ammo_info(Players[Player_num].secondary_ammo[Secondary_weapon]);
				old_ammo_count[1][VR_current_page] = Players[Player_num].secondary_ammo[Secondary_weapon];
			}
	}
}


void sb_draw_energy_bar(energy)
{
	int erase_height;
	grs_point scale_pts[] = {
		{ 0, 0 },
		{ i2f(64), i2f(8) },
		{ SB_ENERGY_GAUGE_W * 65536, SB_ENERGY_GAUGE_H * 65536 },
	};

	gr_set_current_canvas( Canv_SBEnergyGauge );
	gr_clear_canvas(255);
	PIGGY_PAGE_IN(Gauges[SB_GAUGE_ENERGY]);
	scale_bitmap(&GameBitmaps[Gauges[SB_GAUGE_ENERGY].index],scale_pts);

	erase_height = (100 - energy) * SB_ENERGY_GAUGE_H / 100;

	if (erase_height > 0) {
		gr_setcolor( 0 );
		gr_rect(0,0,SB_ENERGY_GAUGE_W-1,erase_height-1);
	}

	gr_set_current_canvas( get_current_game_screen() );
	gr_ubitmapm( SB_ENERGY_GAUGE_X, SB_ENERGY_GAUGE_Y, &Canv_SBEnergyGauge->cv_bitmap );

	//draw numbers
	gr_set_fontcolor(gr_getcolor(25,18,6),-1 );
	gr_scale_printf((energy>99)?SB_ENERGY_NUM_X:((energy>9)?SB_ENERGY_NUM_X+grd_curscreen->sc_w*0.00625:SB_ENERGY_NUM_X+grd_curscreen->sc_w*0.0125),SB_ENERGY_NUM_Y, Scale_factor, Scale_factor,"%d",energy);
					  
}

void sb_draw_shield_num(int shield)
{
	grs_bitmap *bm = &GameBitmaps[cockpit_bitmap[Cockpit_mode].index];

	//draw numbers

	gr_set_curfont( GAME_FONT );
	gr_set_fontcolor(gr_getcolor(14,14,23),-1 );

	//erase old one
	PIGGY_PAGE_IN( cockpit_bitmap[Cockpit_mode] );
	gr_setcolor(gr_gpixel(&VR_screen_pages[0].cv_bitmap, SB_SHIELD_NUM_X, SB_SHIELD_NUM_Y));// -(VR_render_height - bm->bm_h)));
	gr_rect(SB_SHIELD_NUM_X,SB_SHIELD_NUM_Y,SB_SHIELD_NUM_X+grd_curscreen->sc_w*0.040625,SB_SHIELD_NUM_Y+f2i(Scale_factor)*(GAME_FONT->ft_h + 2));

	gr_scale_printf((shield>99)?SB_SHIELD_NUM_X:((shield>9)?SB_SHIELD_NUM_X+grd_curscreen->sc_w*0.00625:SB_SHIELD_NUM_X+grd_curscreen->sc_w*0.0125),SB_SHIELD_NUM_Y, Scale_factor, Scale_factor,"%d",shield);
}

void sb_draw_shield_bar(int shield)
{
	int bm_num = shield>=100?9:(shield / 10);
	grs_point scale_pts[] = {
		{ SB_SHIELD_GAUGE_X * 65536, SB_SHIELD_GAUGE_Y * 65536 },
		{ SB_SHIELD_GAUGE_X * 65536 + i2f(35),  SB_SHIELD_GAUGE_Y * 65536 + i2f(32) },
		{ SB_SHIELD_GAUGE_X * 65536 + SHIELD_GAUGE_W * 65536,  SB_SHIELD_GAUGE_Y * 65536 + SHIELD_GAUGE_H * 65536 },
	};

	gr_set_current_canvas( get_current_game_screen() );

	PIGGY_PAGE_IN( Gauges[GAUGE_SHIELDS+9-bm_num] );
	scale_bitmap(&GameBitmaps[Gauges[GAUGE_SHIELDS+9-bm_num].index],scale_pts);

}

void sb_draw_keys()
{
	grs_bitmap * bm;
	int flags = Players[Player_num].flags;
	fix scale_x = fixdiv(i2f(grd_curscreen->sc_w), i2f(320));
	fix scale_y = fixdiv(i2f(grd_curscreen->sc_h), i2f(200));
	grs_point scale_pts_blue[] = {
		{ SB_GAUGE_KEYS_X * 65536, SB_GAUGE_BLUE_KEY_Y * 65536 },
		{ SB_GAUGE_KEYS_X * 65536 + i2f(16),  SB_GAUGE_BLUE_KEY_Y * 65536 + i2f(13) },
		{ SB_GAUGE_KEYS_X * 65536 + 16 * scale_x,  SB_GAUGE_BLUE_KEY_Y * 65536 + 13 * scale_y },
	};
	grs_point scale_pts_gold[] = {
		{ SB_GAUGE_KEYS_X * 65536, SB_GAUGE_GOLD_KEY_Y * 65536 },
		{ SB_GAUGE_KEYS_X * 65536 + i2f(16),  SB_GAUGE_GOLD_KEY_Y * 65536 + i2f(13) },
		{ SB_GAUGE_KEYS_X * 65536 + 16 * scale_x,  SB_GAUGE_GOLD_KEY_Y * 65536 + 13 * scale_y },
	};
	grs_point scale_pts_red[] = {
		{ SB_GAUGE_KEYS_X * 65536, SB_GAUGE_RED_KEY_Y * 65536 },
		{ SB_GAUGE_KEYS_X * 65536 + i2f(16),  SB_GAUGE_RED_KEY_Y * 65536 + i2f(13) },
		{ SB_GAUGE_KEYS_X * 65536 + 16 * scale_x,  SB_GAUGE_RED_KEY_Y * 65536 + 13 * scale_y },
	};

	gr_set_current_canvas( get_current_game_screen() );

	bm = &GameBitmaps[Gauges[(flags&PLAYER_FLAGS_BLUE_KEY)?SB_GAUGE_BLUE_KEY:SB_GAUGE_BLUE_KEY_OFF].index];
	PIGGY_PAGE_IN(Gauges[(flags&PLAYER_FLAGS_BLUE_KEY)?SB_GAUGE_BLUE_KEY:SB_GAUGE_BLUE_KEY_OFF]);
	scale_bitmap(bm,scale_pts_blue);
	bm = &GameBitmaps[Gauges[(flags&PLAYER_FLAGS_GOLD_KEY)?SB_GAUGE_GOLD_KEY:SB_GAUGE_GOLD_KEY_OFF].index];
	PIGGY_PAGE_IN(Gauges[(flags&PLAYER_FLAGS_GOLD_KEY)?SB_GAUGE_GOLD_KEY:SB_GAUGE_GOLD_KEY_OFF]);
	scale_bitmap(bm, scale_pts_gold);
	bm = &GameBitmaps[Gauges[(flags&PLAYER_FLAGS_RED_KEY)?SB_GAUGE_RED_KEY:SB_GAUGE_RED_KEY_OFF].index];
	PIGGY_PAGE_IN(Gauges[(flags&PLAYER_FLAGS_RED_KEY)?SB_GAUGE_RED_KEY:SB_GAUGE_RED_KEY_OFF]);
	scale_bitmap(bm, scale_pts_red);

}

//	Draws invulnerable ship, or maybe the flashing ship, depending on invulnerability time left.
void draw_invulnerable_ship()
{
	static fix time=0;
	fix scale_x = fixdiv(i2f(grd_curscreen->sc_w), i2f(320));
	fix scale_y = fixdiv(i2f(grd_curscreen->sc_h), i2f(200));
	grs_point scale_pts_cockpit[] = {
		{ SHIELD_GAUGE_X * 65536, SHIELD_GAUGE_Y * 65536 },
		{ SHIELD_GAUGE_X * 65536 + i2f(35), SHIELD_GAUGE_Y * 65536 + i2f(32) },
		{ SHIELD_GAUGE_X * 65536 + fixmul(i2f(35), scale_x), SHIELD_GAUGE_Y * 65536 + fixmul(i2f(32), scale_y) }
	};
	grs_point scale_pts_bar[] = {
		{ SB_SHIELD_GAUGE_X * 65536, SB_SHIELD_GAUGE_Y * 65536 },
		{ SB_SHIELD_GAUGE_X * 65536 + i2f(35), SB_SHIELD_GAUGE_Y * 65536 + i2f(32) },
		{ SB_SHIELD_GAUGE_X * 65536 + fixmul(i2f(35), scale_x), SB_SHIELD_GAUGE_Y * 65536 + fixmul(i2f(32), scale_y) }
	};

	gr_set_current_canvas( get_current_game_screen() );

	if (((Players[Player_num].invulnerable_time + INVULNERABLE_TIME_MAX - GameTime) > F1_0*4) || (GameTime & 0x8000)) {

		if (Cockpit_mode == CM_STATUS_BAR)	{
			PIGGY_PAGE_IN(Gauges[GAUGE_INVULNERABLE+invulnerable_frame]);
			scale_bitmap(&GameBitmaps[Gauges[GAUGE_INVULNERABLE+invulnerable_frame].index], scale_pts_bar);
		} else {
			PIGGY_PAGE_IN(Gauges[GAUGE_INVULNERABLE+invulnerable_frame]);
			scale_bitmap(&GameBitmaps[Gauges[GAUGE_INVULNERABLE+invulnerable_frame].index], scale_pts_cockpit);
		}

		time += FrameTime;

		while (time > INV_FRAME_TIME) {
			time -= INV_FRAME_TIME;
			if (++invulnerable_frame == N_INVULNERABLE_FRAMES)
				invulnerable_frame=0;
		}
	} else if (Cockpit_mode == CM_STATUS_BAR)
		sb_draw_shield_bar(f2ir(Players[Player_num].shields));
	else
		draw_shield_bar(f2ir(Players[Player_num].shields));
}

#ifdef HOSTAGE_FACES
draw_hostage_gauge()
{
	int drew;

	gr_set_current_canvas(Canv_game_offscrn);

	drew = do_hostage_effects();

	if (drew) {
		int boxofs = (Cockpit_mode==CM_STATUS_BAR)?2:0;

		gr_set_current_canvas(Canv_game);
		copy_gauge_box(&gauge_boxes[boxofs+1],&Canv_game_offscrn->cv_bitmap);

		old_weapon[1][VR_current_page] = old_ammo_count[1][VR_current_page] = -1;
	}

}
#endif

extern int Missile_gun;
extern int allowed_to_fire_laser(void);
extern int allowed_to_fire_missile(void);

rgb player_rgb[] = {
							{15,15,23},
							{27,0,0},
							{0,23,0},
							{30,11,31},
							{31,16,0},
							{24,17,6},
							{14,21,12},
							{29,29,0},
						};


//draw the reticle
void show_reticle(int force_big_one)
{
	int x,y;
	int laser_ready,missile_ready,laser_ammo,missile_ammo;
	int cross_bm_num,primary_bm_num,secondary_bm_num;

	x = grd_curcanv->cv_w/2;
	y = grd_curcanv->cv_h/2;

	grs_point scale_pts_cross[] = {
		{ i2f(x) - fixmul(i2f(4), Scale_factor), i2f(y) - fixmul(i2f(2), Scale_factor) },
		{ 0, 0 }, // Not used, who cares
		{ i2f(x) - fixmul(i2f(4), Scale_factor) + fixmul(i2f(9), Scale_factor), i2f(y) - fixmul(i2f(2), Scale_factor) + fixmul(i2f(7), Scale_factor) }
	};
	grs_point scale_pts_primary[] = {
		{ i2f(x) - fixmul(i2f(15), Scale_factor), i2f(y) + fixmul(i2f(6), Scale_factor) },
		{ 0, 0 }, // Not used, who cares
		{ i2f(x) - fixmul(i2f(15), Scale_factor) + fixmul(i2f(31), Scale_factor), i2f(y) + fixmul(i2f(6), Scale_factor) + fixmul(i2f(5), Scale_factor) }
	};
	grs_point scale_pts_secondary[] = {
		{ i2f(x) - fixmul(i2f(12), Scale_factor), i2f(y) + fixmul(i2f(1), Scale_factor) },
		{ 0, 0 }, // Not used, who cares
		{ i2f(x) - fixmul(i2f(12), Scale_factor) + fixmul(i2f(25), Scale_factor), i2f(y) + fixmul(i2f(1), Scale_factor) + fixmul(i2f(10), Scale_factor) }
	};

	laser_ready = allowed_to_fire_laser();
	missile_ready = allowed_to_fire_missile();

	laser_ammo = player_has_weapon(Primary_weapon,0);
	missile_ammo = player_has_weapon(Secondary_weapon,1);

	primary_bm_num = (laser_ready && laser_ammo==HAS_ALL);
	secondary_bm_num = (missile_ready && missile_ammo==HAS_ALL);

	if (primary_bm_num && Primary_weapon==LASER_INDEX && (Players[Player_num].flags & PLAYER_FLAGS_QUAD_LASERS))
		primary_bm_num++;

	if (Secondary_weapon!=CONCUSSION_INDEX && Secondary_weapon!=HOMING_INDEX)
		secondary_bm_num += 3;		//now value is 0,1 or 3,4
	else if (secondary_bm_num && !(Missile_gun&1))
			secondary_bm_num++;

	cross_bm_num = ((primary_bm_num > 0) || (secondary_bm_num > 0));

	Assert(primary_bm_num <= 2);
	Assert(secondary_bm_num <= 4);
	Assert(cross_bm_num <= 1);

	if (grd_curcanv->cv_bitmap.bm_w > 200 || force_big_one) {
		PIGGY_PAGE_IN(Gauges[RETICLE_CROSS + cross_bm_num]);
		grs_bitmap *bm = &GameBitmaps[Gauges[RETICLE_CROSS + cross_bm_num].index];
		scale_bitmap(&GameBitmaps[Gauges[RETICLE_CROSS + cross_bm_num].index],scale_pts_cross);
		PIGGY_PAGE_IN(Gauges[RETICLE_PRIMARY + primary_bm_num]);
		bm = &GameBitmaps[Gauges[RETICLE_PRIMARY + primary_bm_num].index];
		scale_bitmap(&GameBitmaps[Gauges[RETICLE_PRIMARY + primary_bm_num].index],scale_pts_primary);
		PIGGY_PAGE_IN(Gauges[RETICLE_SECONDARY + secondary_bm_num]);
		bm = &GameBitmaps[Gauges[RETICLE_SECONDARY + secondary_bm_num].index];
		scale_bitmap(&GameBitmaps[Gauges[RETICLE_SECONDARY + secondary_bm_num].index],scale_pts_secondary);
	}
	else {
		PIGGY_PAGE_IN(Gauges[SML_RETICLE_CROSS + cross_bm_num]);
		gr_ubitmapm(x-2,y-1,&GameBitmaps[Gauges[SML_RETICLE_CROSS + cross_bm_num].index]);
		PIGGY_PAGE_IN(Gauges[SML_RETICLE_PRIMARY + primary_bm_num]);
		gr_ubitmapm(x-8,y+2,&GameBitmaps[Gauges[SML_RETICLE_PRIMARY + primary_bm_num].index]);
		PIGGY_PAGE_IN(Gauges[SML_RETICLE_SECONDARY + secondary_bm_num]);
		gr_ubitmapm(x-6,y-2,&GameBitmaps[Gauges[SML_RETICLE_SECONDARY + secondary_bm_num].index]);
	}

#ifndef SHAREWARE
#ifdef NETWORK
	if ((Newdemo_state == ND_STATE_PLAYBACK) || (((Game_mode & GM_MULTI_COOP) || (Game_mode & GM_TEAM)) && Show_reticle_name))
	{
		// Draw player callsign for player in sights 
		fvi_query fq;
		vms_vector orient;
		int Hit_type;
		fvi_info Hit_data;

		fq.p0 		= &ConsoleObject->pos;
		orient 		= ConsoleObject->orient.fvec;
		vm_vec_scale(&orient, F1_0*1024);
		vm_vec_add2(&orient, fq.p0);
		fq.p1 		= &orient;
		fq.rad 		= 0;
		fq.thisobjnum = ConsoleObject - Objects;
		fq.flags 	= FQ_TRANSWALL | FQ_CHECK_OBJS;
		fq.startseg	= ConsoleObject->segnum;
		fq.ignore_obj_list = NULL;

		Hit_type = find_vector_intersection(&fq, &Hit_data);
		if ((Hit_type == HIT_OBJECT) && (Objects[Hit_data.hit_object].type == OBJ_PLAYER))
		{
			// Draw callsign on HUD
			char s[CALLSIGN_LEN+1];
			int w, h, aw;
			int x1, y1;
			int pnum;
			int color_num;

			pnum = Objects[Hit_data.hit_object].id;

			if ((Game_mode & GM_TEAM) && (get_team(pnum) != get_team(Player_num)) && (Newdemo_state != ND_STATE_PLAYBACK))
				return;

			if (Game_mode & GM_TEAM)
				color_num = get_team(pnum);
			else
				color_num = pnum;
			sprintf(s, "%s", Players[pnum].callsign);
			gr_get_string_size(s, &w, &h, &aw);
			gr_set_fontcolor(gr_getcolor(player_rgb[color_num].r,player_rgb[color_num].g,player_rgb[color_num].b),-1 );
			x1 = x-(w/2);
			y1 = y+12;
			gr_string (x1, y1, s);
//	 		}
		}
#ifndef NDEBUG
		else if ((Hit_type == HIT_OBJECT) && (Objects[Hit_data.hit_object].type == OBJ_ROBOT))
		{
			char s[CALLSIGN_LEN+1];
			int w, h, aw;
			int x1, y1;
			int color_num = 0;

			sprintf(s, "%d", Hit_data.hit_object);
			gr_get_string_size(s, &w, &h, &aw);
			gr_set_fontcolor(gr_getcolor(player_rgb[color_num].r,player_rgb[color_num].g,player_rgb[color_num].b),-1 );
			x1 = x-(w/2);
			y1 = y+12;
			gr_string (x1, y1, s);
		}
#endif
	}
#endif
#endif
}

#ifdef NETWORK
void hud_show_kill_list()
{
	int n_players,player_list[MAX_NUM_NET_PLAYERS];
	int n_left,i,x0,x1,y,save_y,fth;

	if (Show_kill_list_timer > 0)
	{
		Show_kill_list_timer -= FrameTime;
		if (Show_kill_list_timer < 0)
			Show_kill_list = 0;
	}
	
#ifdef SHAREWARE
	if (Game_mode & GM_MULTI_COOP)
	{
		Show_kill_list = 0;
		return;
	}
#endif

	gr_set_curfont( GAME_FONT );

	n_players = multi_get_kill_list(player_list);

	if (Show_kill_list == 2)
		n_players = 2;

	if (n_players <= 4)
		n_left = n_players;
	else
		n_left = (n_players+1)/2;

	//If font size changes, this code might not work right anymore 
	Assert(GAME_FONT->ft_h==5 && GAME_FONT->ft_w==7);

	fth = GAME_FONT->ft_h;

	x0 = 1; x1 = 43;

#ifndef SHAREWARE
	if (Game_mode & GM_MULTI_COOP)
		x1 = 31;
#endif

	save_y = y = grd_curcanv->cv_h - n_left*(fth+1);

	if (Cockpit_mode == CM_FULL_COCKPIT) {
		save_y = y -= 6;
#ifndef SHAREWARE
		if (Game_mode & GM_MULTI_COOP)
			x1 = 33;
		else
#endif
			x1 = 43;
	}

	for (i=0;i<n_players;i++) {
		int player_num;
		char name[9];
		int sw,sh,aw;

		if (i==n_left) {
			if (Cockpit_mode == CM_FULL_COCKPIT)
				x0 = grd_curcanv->cv_w - 53;
			else
				x0 = grd_curcanv->cv_w - 60;
#ifndef SHAREWARE
			if (Game_mode & GM_MULTI_COOP)
				x1 = grd_curcanv->cv_w - 27;
			else
#endif
				x1 = grd_curcanv->cv_w - 15;
			y = save_y;
		}
	
		if (Show_kill_list == 2)
			player_num = i;
		else
			player_num = player_list[i];

		if (Show_kill_list == 1)
		{
			int color;

			if (Players[player_num].connected != 1)
				gr_set_fontcolor(gr_getcolor(12, 12, 12), -1);
			else if (Game_mode & GM_TEAM) {
				color = get_team(player_num);
				gr_set_fontcolor(gr_getcolor(player_rgb[color].r,player_rgb[color].g,player_rgb[color].b),-1 );
			}
			else {
				color = player_num;
				gr_set_fontcolor(gr_getcolor(player_rgb[color].r,player_rgb[color].g,player_rgb[color].b),-1 );
			}
		}	

		else 
		{
			gr_set_fontcolor(gr_getcolor(player_rgb[player_num].r,player_rgb[player_num].g,player_rgb[player_num].b),-1 );
		}

		if (Show_kill_list == 2)
			strcpy(name, Netgame.team_name[i]);
		else
			strcpy(name,Players[player_num].callsign);	// Note link to above if!!
		gr_get_string_size(name,&sw,&sh,&aw);
		while (sw > (x1-x0-3)) {
			name[strlen(name)-1]=0;
			gr_get_string_size(name,&sw,&sh,&aw);
		}
		gr_printf(x0,y,"%s",name);
		if (Show_kill_list == 2)	
			gr_printf(x1,y,"%3d",team_kills[i]);
#ifndef SHAREWARE
		else if (Game_mode & GM_MULTI_COOP)
			gr_printf(x1,y,"%-6d",Players[player_num].score);
#endif
		else
			gr_printf(x1,y,"%3d",Players[player_num].net_kills_total);
		y += fth+1;

	}
}
#endif

//draw all the things on the HUD
void draw_hud()
{
	//	Show score so long as not in rearview
	if ( !Rear_view && Cockpit_mode!=CM_REAR_VIEW && Cockpit_mode!=CM_STATUS_BAR) {
		hud_show_score();
		if (score_time)
			hud_show_score_added();
	}

	//	Show other stuff if not in rearview or letterbox.
	if (!Rear_view && Cockpit_mode!=CM_REAR_VIEW) { // && Cockpit_mode!=CM_LETTERBOX) {
		if (Cockpit_mode==CM_STATUS_BAR || Cockpit_mode==CM_FULL_SCREEN)
			hud_show_homing_warning();

		if (Cockpit_mode==CM_FULL_SCREEN) {
			hud_show_energy();
			hud_show_shield();
			hud_show_weapons();
			hud_show_keys();
			hud_show_cloak_invuln();

			if ( ( Newdemo_state==ND_STATE_RECORDING ) && ( Players[Player_num].flags != old_flags[VR_current_page] )) {
				newdemo_record_player_flags(old_flags[VR_current_page], Players[Player_num].flags);
				old_flags[VR_current_page] = Players[Player_num].flags;
			}
		}

		#ifdef NETWORK
		#ifndef RELEASE
		if (!(Game_mode&GM_MULTI && Show_kill_list))
			show_time();
		#endif
		#endif
		if (Cockpit_mode != CM_LETTERBOX && (!Use_player_head_angles))
			show_reticle(0);
		HUD_render_message_frame();

		if (Cockpit_mode!=CM_STATUS_BAR)
			hud_show_lives();
		#ifdef NETWORK
		if (Game_mode&GM_MULTI && Show_kill_list)
			hud_show_kill_list();
		#endif
	}

	if (Rear_view && Cockpit_mode!=CM_REAR_VIEW) {
		HUD_render_message_frame();
		gr_set_curfont( GAME_FONT );
		gr_set_fontcolor(gr_getcolor(0,31,0),-1 );
		if (Newdemo_state == ND_STATE_PLAYBACK)
			gr_scale_printf(0x8000,grd_curcanv->cv_h-(grd_curscreen->sc_h*0.07), Scale_factor, Scale_factor,TXT_REAR_VIEW);
		else
			gr_scale_printf(0x8000,grd_curcanv->cv_h-(grd_curscreen->sc_h*0.05), Scale_factor, Scale_factor,TXT_REAR_VIEW);
	}

}

//print out some player statistics
void render_gauges()
{
	int energy = f2ir(Players[Player_num].energy);
	int shields = f2ir(Players[Player_num].shields);
	int cloak = ((Players[Player_num].flags&PLAYER_FLAGS_CLOAKED) != 0);

	Assert(Cockpit_mode==CM_FULL_COCKPIT || Cockpit_mode==CM_STATUS_BAR);

	#ifdef HOSTAGE_FACES
	draw_hostage_gauge();
	#endif

	if (shields < 0 ) shields = 0;

	gr_set_current_canvas(get_current_game_screen());
	gr_set_curfont( GAME_FONT );

	if (Newdemo_state == ND_STATE_RECORDING)
		if (Players[Player_num].homing_object_dist >= 0)
			newdemo_record_homing_distance(Players[Player_num].homing_object_dist);

	if (Cockpit_mode == CM_FULL_COCKPIT) {
		if (energy != old_energy[VR_current_page]) {
			if (Newdemo_state==ND_STATE_RECORDING ) {
#ifdef SHAREWARE
				newdemo_record_player_energy(energy);
#else
				newdemo_record_player_energy(old_energy[VR_current_page], energy);
#endif
			}
			draw_energy_bar(energy);
			draw_numerical_display(shields, energy);
			old_energy[VR_current_page] = energy;
		}

		if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE) {
			draw_numerical_display(shields, energy);
			draw_invulnerable_ship();
			old_shields[VR_current_page] = shields ^ 1;
		} else if (shields != old_shields[VR_current_page]) {		// Draw the shield gauge
			if (Newdemo_state==ND_STATE_RECORDING ) {
#ifdef SHAREWARE
				newdemo_record_player_shields(shields);
#else
				newdemo_record_player_shields(old_shields[VR_current_page], shields);
#endif
			}
			draw_shield_bar(shields);
			draw_numerical_display(shields, energy);
			old_shields[VR_current_page] = shields;
		}
	
		if (Players[Player_num].flags != old_flags[VR_current_page]) {
			if (Newdemo_state==ND_STATE_RECORDING )
				newdemo_record_player_flags(old_flags[VR_current_page], Players[Player_num].flags);
			draw_keys();
			old_flags[VR_current_page] = Players[Player_num].flags;
		}

		show_homing_warning();
	
	} else if (Cockpit_mode == CM_STATUS_BAR) {

		if (energy != old_energy[VR_current_page]) {
			if (Newdemo_state==ND_STATE_RECORDING ) {
#ifdef SHAREWARE
				newdemo_record_player_energy(energy);
#else
				newdemo_record_player_energy(old_energy[VR_current_page], energy);
#endif
			}
			sb_draw_energy_bar(energy);
			old_energy[VR_current_page] = energy;
		}
	
		if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE) {
			draw_invulnerable_ship();
			old_shields[VR_current_page] = shields ^ 1;
			sb_draw_shield_num(shields);
		} 
		else 
			if (shields != old_shields[VR_current_page]) {		// Draw the shield gauge
				if (Newdemo_state==ND_STATE_RECORDING ) {
#ifdef SHAREWARE
					newdemo_record_player_shields(shields);
#else
					newdemo_record_player_shields(old_shields[VR_current_page], shields);
#endif
				}
				sb_draw_shield_bar(shields);
				old_shields[VR_current_page] = shields;
				sb_draw_shield_num(shields);
			}

		if (Players[Player_num].flags != old_flags[VR_current_page]) {
			if (Newdemo_state==ND_STATE_RECORDING )
				newdemo_record_player_flags(old_flags[VR_current_page], Players[Player_num].flags);
			sb_draw_keys();
			old_flags[VR_current_page] = Players[Player_num].flags;
		}
	

		if ((Game_mode & GM_MULTI) && !(Game_mode & GM_MULTI_COOP))
		{
			if (Players[Player_num].net_killed_total != old_lives[VR_current_page]) {
				sb_show_lives();
				old_lives[VR_current_page] = Players[Player_num].net_killed_total;
			}
		}
		else
		{
			if (Players[Player_num].lives != old_lives[VR_current_page]) {
				sb_show_lives();
				old_lives[VR_current_page] = Players[Player_num].lives;
			}
		}

		if ((Game_mode&GM_MULTI) && !(Game_mode & GM_MULTI_COOP)) {
			if (Players[Player_num].net_kills_total != old_score[VR_current_page]) {
				sb_show_score();
				old_score[VR_current_page] = Players[Player_num].net_kills_total;
			}
		}
		else {
			if (Players[Player_num].score != old_score[VR_current_page]) {
				sb_show_score();
				old_score[VR_current_page] = Players[Player_num].score;
			}

			if (score_time)
				sb_show_score_added();
		}

	}

	if (cloak != old_cloak[VR_current_page] || cloak_fade_state || (cloak && GameTime>Players[Player_num].cloak_time+CLOAK_TIME_MAX-i2f(3))) {
		if (Cockpit_mode == CM_FULL_COCKPIT)
			draw_player_ship(cloak,old_cloak[VR_current_page],SHIP_GAUGE_X,SHIP_GAUGE_Y);
		else
			draw_player_ship(cloak,old_cloak[VR_current_page],SB_SHIP_GAUGE_X,SB_SHIP_GAUGE_Y);

		old_cloak[VR_current_page]=cloak;
	}


	draw_weapon_boxes();

}

//	---------------------------------------------------------------------------------------------------------
//	Call when picked up a laser powerup.
//	If laser is active, set old_weapon[0] to -1 to force redraw.
void update_laser_weapon_info(void)
{
	if (old_weapon[0][VR_current_page] == 0)
		old_weapon[0][VR_current_page] = -1;
}
