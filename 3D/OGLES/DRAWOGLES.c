//
//  DRAWOGLES.c
//  3D
//
//  Created by Devin Tuchsen on 11/1/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifdef OGLES
#include <math.h>
#include "drawogles.h"
#include "globvars.h"
#include "gr.h"
#include "3d.h"
#include "mem.h"

extern ubyte gr_current_pal[256*3];
extern int Gr_scanline_darkening_level;

int g3_draw_tmap_ogles(int nv, g3s_point **pointlist, g3s_uvl *uvl_list, grs_bitmap *bm) {
	GLfloat *vertices, *colors, *texture_coords;
	int i;
	
	vertices = malloc(sizeof(GLfloat) * 3 * nv);
	colors = malloc(sizeof(GLfloat) * 4 * nv);
	texture_coords = malloc(sizeof(GLfloat) * 2 * nv);
	
	// Build vertex list
	for (i = 0; i < nv; ++i) {
		vertices[i * 3] = f2fl(pointlist[i]->p3_vec.x);
		vertices[i * 3 + 1] = f2fl(pointlist[i]->p3_vec.y);
		vertices[i * 3 + 2] = -f2fl(pointlist[i]->p3_vec.z);
	}
	
	// Build color list (lighting)
	for (i = 0; i < nv; ++i) {
		colors[i * 4] = f2fl(uvl_list[i].l);
		colors[i * 4 + 1] = f2fl(uvl_list[i].l);
		colors[i * 4 + 2] = f2fl(uvl_list[i].l);
		colors[i * 4 + 3] = 1.0f;
	}
	
	// Build texture coord list
	for (i = 0; i < nv; ++i) {
		texture_coords[i * 2] = f2fl(uvl_list[i].u);
		texture_coords[i * 2 + 1] = f2fl(uvl_list[i].v);
	}
	
	glEnable(GL_TEXTURE_2D);
	ogles_bm_bind_teximage_2d(bm);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glTexCoordPointer(2, GL_FLOAT, 0, texture_coords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, nv);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	free(vertices);
	free(colors);
	free(texture_coords);
	return 0;
}

int g3_draw_poly_ogles(int nv, g3s_point **pointlist) {
	GLfloat *vertices;
	GLubyte alpha;
	int i;
	
	vertices = malloc(sizeof(GLfloat) * 3 * nv);
	
	// Build vertex list
	for (i = 0; i < nv; ++i) {
		vertices[i * 3] = f2fl(pointlist[i]->p3_vec.x);
		vertices[i * 3 + 1] = f2fl(pointlist[i]->p3_vec.y);
		vertices[i * 3 + 2] = -f2fl(pointlist[i]->p3_vec.z);
	}
	
	if (Gr_scanline_darkening_level >= GR_FADE_LEVELS) {
		alpha = 255;
	} else {
		alpha = Gr_scanline_darkening_level * 4;
	}
	
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColor4ub(gr_current_pal[grd_curcanv->cv_color * 3] * 4,
			  gr_current_pal[grd_curcanv->cv_color * 3 + 1] * 4,
			  gr_current_pal[grd_curcanv->cv_color * 3 + 2] * 4, alpha);
	glDrawArrays(GL_TRIANGLE_FAN, 0, nv);
	glDisableClientState(GL_VERTEX_ARRAY);
	free(vertices);
	return 0;
}

int g3_draw_line_ogles(g3s_point *p0, g3s_point *p1) {
	GLfloat x0, y0, z0, x1, y1, z1;
	
	x0 = f2fl(p0->x);
	y0 = f2fl(p0->y);
	z0 = -f2fl(p0->z);
	x1 = f2fl(p1->x);
	y1 = f2fl(p1->y);
	z1 = -f2fl(p1->z);
	
	GLfloat vertices[] = { x0, y0, z0, x1, y1, z1 };
	
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4ub(gr_current_pal[grd_curcanv->cv_color * 3] * 4,
			   gr_current_pal[grd_curcanv->cv_color * 3 + 1] * 4,
			   gr_current_pal[grd_curcanv->cv_color * 3 + 2] * 4, 255);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	return 1;
}

int g3_draw_sphere_ogles(g3s_point *pnt, fix rad) {
	GLfloat x, y, z, rx, ry;
	GLfloat vertices[60];
	int i = 0;

	x = f2fl(pnt->x);
	y = f2fl(pnt->y);
	z = -f2fl(pnt->z);
	rx = f2fl(fixmul(rad, Matrix_scale.x));
	ry = f2fl(rad);

	for (i = 19; i >= 0; --i) {
		float theta = 2.0f * M_PI * (float)i / 20.0f;
		
		vertices[i * 3] = x + sin(theta) * rx;
		vertices[i * 3 + 1] = y + cos(theta) * ry;
		vertices[i * 3 + 2] = z;
	}

	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4ub(gr_current_pal[grd_curcanv->cv_color * 3] * 4,
			   gr_current_pal[grd_curcanv->cv_color * 3 + 1] * 4,
			   gr_current_pal[grd_curcanv->cv_color * 3 + 2] * 4, 255);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glDisableClientState(GL_VERTEX_ARRAY);
	return 1;
}

#endif
