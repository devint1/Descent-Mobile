//
//  OGLTEXTURES.c
//  TEXMAP
//
//  Created by Devin Tuchsen on 10/29/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES

#ifdef ANDROID_NDK
#include <GLES/gl.h>
#else
#include <OpenGLES/ES1/gl.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "gr.h"
#include "rle.h"
#include "oglestex.h"

extern ubyte gr_current_pal[256*3];

void ogles_clear_canvas_textures() {
	//glDeleteTextures(NUM_OGL_TEXTURES, grd_curcanv->cv_ogles_textures);
}

void ogles_bm_bind_teximage_2d(grs_bitmap *bm) {
	GLubyte *image_data;
	ubyte *data, *sbits, *dbits;
	int i;
	
	if (!glIsTexture(bm->bm_ogles_tex_id)) {
		glGenTextures(1, &bm->bm_ogles_tex_id);
		glBindTexture(GL_TEXTURE_2D, bm->bm_ogles_tex_id);
		image_data = malloc(bm->bm_w * bm->bm_h * 4);
		if (bm->bm_flags & BM_FLAG_RLE) {
			ubyte *expanded = malloc(bm->bm_w * bm->bm_h * 3);
			sbits = &bm->bm_data[4 + bm->bm_h];
			dbits = expanded;
			for (int i = 0; i < bm->bm_h; i++) {
				gr_rle_decode(sbits, dbits);
				sbits += (int)bm->bm_data[4 + i];
				dbits += bm->bm_w;
			}
			data = expanded;
		} else {
			data = bm->bm_data;
		}
		for (i = 0; i < bm->bm_w * bm->bm_h; ++i) {
			image_data[i * 4] = gr_current_pal[data[i] * 3] * 4;
			image_data[i * 4 + 1] = gr_current_pal[data[i] * 3 + 1] * 4;
			image_data[i * 4 + 2] = gr_current_pal[data[i] * 3 + 2] * 4;
			image_data[i * 4 + 3] = data[i] == TRANSPARENCY_COLOR ? 0 : 255;
		}
		if (bm->bm_flags & BM_FLAG_RLE) {
			free(data);
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bm->bm_w, bm->bm_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		free(image_data);
	} else {
		glBindTexture(GL_TEXTURE_2D, bm->bm_ogles_tex_id);
	}
}

#endif
