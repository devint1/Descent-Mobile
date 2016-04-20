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

extern int g3_draw_tmap_ogles(int nv, g3s_point **pointlist, g3s_uvl *uvl_list, grs_bitmap *bm);
extern int g3_draw_poly_ogles(int nv, g3s_point **pointlist);
extern int g3_draw_line_ogles(g3s_point *p0, g3s_point *p1);
extern int g3_draw_sphere_ogles(g3s_point *pnt, fix rad);
#endif

#endif /* DRAWOGLES_h */
