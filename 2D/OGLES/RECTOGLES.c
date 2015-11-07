//
//  RECTOGLES.c
//  2D
//
//  Created by Devin Tuchsen on 10/30/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES
#include <OpenGLES/ES1/gl.h>
#include "RECTOGLES.h"
#include "gr.h"
#include "palette.h"

extern ubyte gr_current_pal[256*3];

void gr_rect_ogles(int left,int top,int right,int bot) {
	GLfloat x0f, y0f, x1f, y1f;
	GLuint alpha;
	
	// Calculate OGLES coords
	x0f = (((left + grd_curcanv->cv_bitmap.bm_x) * 2.0f) / grd_curscreen->sc_w) - 1.0f;
	y0f = (((top + grd_curcanv->cv_bitmap.bm_y) * -2.0f) / grd_curscreen->sc_h) + 1.0f;
	x1f = (((right + grd_curcanv->cv_bitmap.bm_x) * 2.0f) / grd_curscreen->sc_w) - 1.0f;
	y1f = (((bot + grd_curcanv->cv_bitmap.bm_y) * -2.0f) / grd_curscreen->sc_h) + 1.0f;
	
	// Draw
	GLfloat vertices[] = { x0f, y1f, x1f, y1f, x1f, y0f, x0f, y0f };
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	if (Gr_scanline_darkening_level >= GR_FADE_LEVELS ) {
		alpha = 255;
	} else {
		alpha = 255 - ((float)Gr_scanline_darkening_level / (float)GR_FADE_LEVELS) * 255.0f;
	}
	glColor4ub(gr_current_pal[grd_curcanv->cv_color * 3], gr_current_pal[grd_curcanv->cv_color * 3 + 1], gr_current_pal[grd_curcanv->cv_color * 3 + 2], alpha);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

#endif
