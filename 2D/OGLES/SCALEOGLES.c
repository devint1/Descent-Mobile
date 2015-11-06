//
//  SCALEOGL.c
//  2D
//
//  Created by Devin Tuchsen on 10/29/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES
#include <OpenGLES/ES1/gl.h>
#include <string.h>
#include "gr.h"
#include "scaleogles.h"
#include "oglestex.h"

void scale_bitmap_ogles(grs_bitmap *bp, int x0, int y0, int x1, int y1) {
	GLfloat x0f, y0f, x1f, y1f;
	
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
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

#endif
