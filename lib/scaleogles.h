//
//  SCALEOGL.h
//  2D
//
//  Created by Devin Tuchsen on 10/29/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef SCALEOGL_h
#define SCALEOGL_h

#ifdef OGLES
extern void scale_bitmap_ogles(grs_bitmap *bp, int x0, int y0, int x1, int y1);
#endif

#endif /* SCALEOGL_h */
