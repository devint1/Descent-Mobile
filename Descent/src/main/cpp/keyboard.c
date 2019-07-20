//
// Created by devin on 4/17/16.
//

#include <jni.h>
#include "types.h"

extern JavaVM *jvm;
extern jobject Descent_view;

extern void key_handler(unsigned char scancode, bool down);

int textIsActive() {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;
	jboolean retval;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentView");
	method = (*env)->GetMethodID(env, clazz, "textIsActive", "()Z");
	retval = (*env)->CallBooleanMethod(env, Descent_view, method);
	(*env)->DeleteLocalRef(env, clazz);
	return retval;
}

void activateText() {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentView");
	method = (*env)->GetMethodID(env, clazz, "activateText", "()V");
	(*env)->CallVoidMethod(env, Descent_view, method);
	(*env)->DeleteLocalRef(env, clazz);
}

void deactivateText() {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentView");
	method = (*env)->GetMethodID(env, clazz, "deactivateText", "()V");
	(*env)->CallVoidMethod(env, Descent_view, method);
	(*env)->DeleteLocalRef(env, clazz);
}

void Java_tuchsen_descent_DescentView_keyHandler(JNIEnv *env, jclass type, jchar c, jboolean down) {
	key_handler((unsigned char) c, down);
}
