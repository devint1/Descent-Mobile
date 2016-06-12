//
//  RODOGLES.c
//  3D
//
//  Created by Devin Tuchsen on 11/2/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES
#include "rodogles.h"
#include "oglestex.h"

bool g3_draw_bitmap_ogles(g3s_point *pos, fix width, fix height, grs_bitmap *bm) {
	GLfloat x0f, y0f, x1f, y1f, zf;
	
	// Calculate OGLES coords
	x0f = f2fl(pos->x - width / 2);
	y0f = f2fl(pos->y - height / 2);
	x1f = f2fl(pos->x + width / 2);
	y1f = f2fl(pos->y + height / 2);
	zf = -f2fl(pos->z);
	
	// Draw
	GLfloat vertices[] = { x1f, y0f, zf, x0f, y0f, zf, x0f, y1f, zf, x1f, y1f, zf};
	GLfloat texCoords[] = { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	glEnable(GL_TEXTURE_2D);
	ogles_bm_bind_teximage_2d(bm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	return 0;
}

#endif