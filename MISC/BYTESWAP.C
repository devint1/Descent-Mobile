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
* $Source: Smoke:miner:source:misc::RCS:byteswap.c $
* $Revision: 1.3 $
* $Author: allender $
* $Date: 1995/08/18 15:51:17 $
*
* code to swap bytes because of big/little endian problems.
*
* $Log: byteswap.c $
* Revision 1.3  1995/08/18  15:51:17  allender
* put back in old byteswapping code
*
* Revision 1.2  1995/05/04  20:10:06  allender
* use unsigned to prevent sign problems
*
* Revision 1.1  1995/03/30  15:01:49  allender
* Initial revision
*
*/

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

ushort swapshort(ushort s) {
	return ((s >> 8) & 0x00ff) | ((s << 8) & 0xff00);
}

uint swapint(uint i) {
	ushort s1, s2;

	s1 = (i >> 16) & 0x0000ffff;
	s2 = i & 0x0000ffff;
	return ((swapshort(s2) << 16) | swapshort(s1));
}
