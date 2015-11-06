//
//  SETUPOGLES.c
//  3D
//
//  Created by Devin Tuchsen on 11/1/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

// TODO: Should be coming from view bounds instead of hard-coded "600.0"
#ifdef OGLES
#include <OpenGLES/ES1/gl.h>
#include <math.h>
#include "gr.h"
#include "setupogles.h"
#include "viewcontrollerc.h"

void g3_ogles_start_frame() {
	GLfloat x0, x1, y0, y1;
	GLint x, y;
	GLsizei width, height;
	
	x = (grd_curcanv->cv_bitmap.bm_x * 600.0) / grd_curscreen->sc_w;
	y = (grd_curcanv->cv_bitmap.bm_y * 600.0) / grd_curscreen->sc_h;
	width = (grd_curcanv->cv_bitmap.bm_w * 600.0) / grd_curscreen->sc_w;
	height = (grd_curcanv->cv_bitmap.bm_h * 600.0) / grd_curscreen->sc_h;
	y = 600 - y - height;
	
	glViewport(x, y, width, height);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	y1 = 0.01f * tan(90.0f * M_PI / 360.0f);
	y0 = -y1;
	x0 = y0;
	x1 = y1;
	glFrustumf(x0, x1, y0, y1, 0.01f, 5000.0f);
	glMatrixMode(GL_MODELVIEW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void g3_ogles_end_frame() {
	glViewport(0, 0, 600, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glCullFace(GL_BACK);
	glDisable(GL_DEPTH_TEST);
}

#endif
