//
// Created by devin on 4/19/16.
//
#include <android/asset_manager_jni.h>
#include <EGL/egl.h>
#include "gr.h"
#include "cfile.h"

JavaVM *jvm;
jobject Activity;
jobject Descent_view;
bool Want_pause;

extern int descent_main(int argc, char **argv);

extern void init_buttons(jint w, jint h);

void Java_tuchsen_descent_DescentView_descentMain(JNIEnv *env, jclass type, jint w, jint h,
												  jobject activity, jobject descent_view, jobject asset_manager,
												  jstring document_path, jstring cache_path) {
	char ws[6], hs[6];

	// Init globals
	Want_pause = false;
	Activity = activity;
	Descent_view = descent_view;
	(*env)->GetJavaVM(env, &jvm);

	// Need to preserve the buffer for things to display corretly
	eglSurfaceAttrib(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_SWAP_BEHAVIOR,
					 EGL_BUFFER_PRESERVED);

	// Get Android things for accessing files
	Asset_manager = AAssetManager_fromJava(env, asset_manager);
	Document_path = (*env)->GetStringUTFChars(env, document_path, NULL);
	Cache_path = (*env)->GetStringUTFChars(env, cache_path, NULL);

	// Start Descent with the magical hacked command line args!
	sprintf(ws, "%d", (int) w);
	sprintf(hs, "%d", (int) h);
	const char *args[] = {"", "-width", ws, "-height", hs};
	init_buttons(w, h);
	descent_main(5, (char **) args);
}

void Java_tuchsen_descent_DescentActivity_descentPause(JNIEnv *env, jclass type) {
	Want_pause = true;
}
