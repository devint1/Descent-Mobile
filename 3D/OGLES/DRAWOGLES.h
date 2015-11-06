//
//  DRAWOGLES.h
//  3D
//
//  Created by Devin Tuchsen on 11/1/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef DRAWOGLES_h
#define DRAWOGLES_h

#ifdef OGLES
#include "gr.h"
#include "3d.h"

int g3_draw_tmap_ogles(int nv, g3s_point **pointlist, g3s_uvl *uvl_list, grs_bitmap *bm);
int g3_draw_poly_ogles(int nv, g3s_point **pointlist);
#endif

#endif /* DRAWOGLES_h */
