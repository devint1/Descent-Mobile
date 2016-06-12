//
//  RODOGLES.h
//  3D
//
//  Created by Devin Tuchsen on 11/2/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef RODOGLES_h
#define RODOGLES_h

#ifdef OGLES
#include "gr.h"
#include "3d.h"

extern bool g3_draw_bitmap_ogles(g3s_point *pos, fix width, fix height, grs_bitmap *bm);
#endif

#endif /* RODOGLES_h */
