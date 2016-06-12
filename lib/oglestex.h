//
//  OGLTEXTURES.h
//  TEXMAP
//
//  Created by Devin Tuchsen on 10/29/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef OGLESTEX_h
#define OGLESTEX_h
#ifdef OGLES

#define NUM_OGL_TEXTURES 16384

#include "gr.h"

typedef struct _grs_bitmap grs_bitmap;

extern GLuint ogles_get_texture();
extern void ogles_bm_bind_teximage_2d(grs_bitmap *bm);
extern void ogles_clear_canvas_textures();

#endif
#endif /* OGLESTEX_h */
