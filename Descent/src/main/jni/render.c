//
// Created by devin on 4/17/16.
//

#include <EGL/egl.h>
#include "gr.h"

extern void draw_buttons();

void getRenderBufferSize(GLint *width, GLint *height) {
	eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_WIDTH, width);
	eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_HEIGHT, height);
}

void showRenderBuffer() {
	draw_buttons();
	eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_READ));
}