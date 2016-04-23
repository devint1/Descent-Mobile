//
// Created by devin on 4/17/16.
//

#include <EGL/egl.h>
#include <jni.h>
#include <string.h>
#include "game.h"
#include "gamefont.h"
#include "texmerge.h"

extern JavaVM *jvm;
extern jobject Renderer;
extern bool Want_pause;
extern grs_bitmap nm_background;

extern void draw_buttons();

extern void mouse_handler(short x, short y, bool down);

void getRenderBufferSize(GLint *width, GLint *height) {
	eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_WIDTH, width);
	eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_HEIGHT, height);
}

void showRenderBuffer() {
	int i;
	GLint width, height;
	grs_font *font;
	JNIEnv *env;
	jclass clazz;
	jmethodID method;

	if (Want_pause) {
		(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
		clazz = (*env)->FindClass(env, "tuchsen/descent/DescentRenderer");

		// Pause this thread
		method = (*env)->GetMethodID(env, clazz, "pauseRenderThread", "()V");
		(*env)->CallVoidMethod(env, Renderer, method);

		// Reset EGL context
		method = (*env)->GetMethodID(env, clazz, "setEgl", "()V");
		(*env)->CallVoidMethod(env, Renderer, method);
		eglSurfaceAttrib(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW),
						 EGL_SWAP_BEHAVIOR,
						 EGL_BUFFER_PRESERVED);
		(*env)->DeleteLocalRef(env, clazz);

		// Purge all texture assets, since the EGL context was blown away
		for (i = 0; i < MAX_FONTS; ++i) {
			font = Gamefonts[i];
			glDeleteTextures(font->ft_maxchar - font->ft_minchar, font->ft_ogles_texes);
			memset(font->ft_ogles_texes, 0, (font->ft_maxchar - font->ft_minchar) * sizeof(GLuint));
		}
		for (i = 0; i < MAX_BITMAP_FILES; ++i) {
			glDeleteTextures(1, &GameBitmaps[i].bm_ogles_tex_id);
			GameBitmaps[i].bm_ogles_tex_id = 0;
		}
		texmerge_close();
		texmerge_init(50);
		glDeleteTextures(1, &nm_background.bm_ogles_tex_id);
		nm_background.bm_ogles_tex_id = 0;

		// Hack to show stuff like menus
		if (Game_mode != GM_NORMAL || In_screen) {
			mouse_handler(-1, -1, true);
			mouse_handler(-1, -1, false);
		}

		Want_pause = false;
	} else {
		draw_buttons();
		eglSwapBuffers(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_READ));
	}
}