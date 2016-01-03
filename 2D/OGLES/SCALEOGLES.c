//
//  SCALEOGL.c
//  2D
//
//  Created by Devin Tuchsen on 10/29/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES
#include <OpenGLES/ES1/gl.h>
#include <math.h>
#include <string.h>
#include "gr.h"
#include "scaleogles.h"
#include "oglestex.h"

extern ubyte gr_current_pal[256*3];
extern ubyte *gr_bitblt_fade_table;

void scale_bitmap_ogles(grs_bitmap *bp, int x0, int y0, int x1, int y1) {
	GLfloat x0f, y0f, x1f, y1f;
	GLfloat alpha = 1.0f;
	
	// Calculate OGLES coords
	x0f = ((x0 * 2.0f) / grd_curscreen->sc_w) - 1.0f;
	y0f = ((y0 * -2.0f) / grd_curscreen->sc_h) + 1.0f;
	x1f = ((x1 * 2.0f) / grd_curscreen->sc_w) - 1.0f;
	y1f = ((y1 * -2.0f) / grd_curscreen->sc_h) + 1.0f;
	
	// Draw
	GLfloat vertices[] = { x0f, y1f, x1f, y1f, x1f, y0f, x0f, y0f };
	GLfloat texCoords[] = { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	glEnable(GL_TEXTURE_2D);
	ogles_bm_bind_teximage_2d(bp);
	if (gr_bitblt_fade_table) {
		alpha = (float)gr_bitblt_fade_table[(int)fmax(y0, 0)] / 31.0f;
    } else {
        alpha = (float)Gr_scanline_darkening_level / (float)GR_FADE_LEVELS;
    }
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	// Magic value means this is a font that needs a color
	if (bp->avg_color == 255) {
		glColor4f(gr_current_pal[grd_curcanv->cv_font_fg_color * 3] / 63.0f,
				   gr_current_pal[grd_curcanv->cv_font_fg_color * 3 + 1] / 63.0f,
				   gr_current_pal[grd_curcanv->cv_font_fg_color * 3 + 2] / 63.0f, alpha);
	} else {
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
	}
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

#endif
