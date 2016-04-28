//
//  BITBLTOGLES.h
//  2D
//
//  Created by Devin Tuchsen on 10/30/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef BITBLTOGLES_h
#define BITBLTOGLES_h

#ifdef OGLES
#include "gr.h"

extern void gr_ubitmapm_ogles(int dx, int dy, grs_bitmap * src);

#endif
#endif /* BITBLTOGLES_h */
