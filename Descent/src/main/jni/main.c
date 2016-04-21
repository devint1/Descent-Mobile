//
// Created by devin on 4/19/16.
//
#include <android/asset_manager_jni.h>
#include <EGL/egl.h>
#include "cfile.h"

JavaVM *jvm;
jobject Activity;

extern int descent_main(int argc, char **argv);

extern void init_buttons(jint w, jint h);

void Java_tuchsen_descent_DescentRenderer_descentMain(JNIEnv *env, jobject thiz, jint w, jint h,
													  jobject activity, jobject asset_manager,
													  jstring document_path, jstring cache_path) {
	char ws[6], hs[6];

	Activity = activity;
	(*env)->GetJavaVM(env, &jvm);
	eglSurfaceAttrib(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_SWAP_BEHAVIOR,
					 EGL_BUFFER_PRESERVED);
	Asset_manager = AAssetManager_fromJava(env, asset_manager);
	Document_path = (*env)->GetStringUTFChars(env, document_path, NULL);
	Cache_path = (*env)->GetStringUTFChars(env, cache_path, NULL);
	sprintf(ws, "%d", (int) w);
	sprintf(hs, "%d", (int) h);
	const char *args[] = {"", "-width", ws, "-height", hs};
	init_buttons(w, h);
	descent_main(5, (char **) args);
}
