//
//  BITBLTOGLES.c
//  2D
//
//  Created by Devin Tuchsen on 10/30/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES
#include "bitbltogles.h"
#include "oglestex.h"
#include "scaleogles.h"
#include "viewcontrollerc.h"
#include "gr.h"

void gr_ubitmapm_ogles(int dx, int dy, grs_bitmap * src) {
	GLfloat x0f, y0f, x1f, y1f;
	
	// Calculate OGLES coords
	x0f = ((dx * 2.0f) / grd_curscreen->sc_w) - 1.0f;
	y0f = ((dy * -2.0f) / grd_curscreen->sc_h) + 1.0f;
	x1f = (((dx + src->bm_w) * 2.0f) / grd_curscreen->sc_w) - 1.0f;
	y1f = (((dy + src->bm_h) * -2.0f) / grd_curscreen->sc_h) + 1.0f;
	
	// Draw
	GLfloat vertices[] = { x0f, y1f, x1f, y1f, x1f, y0f, x0f, y0f };
	GLfloat texCoords[] = { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	glEnable(GL_TEXTURE_2D);
	ogles_bm_bind_teximage_2d(src);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

#endif