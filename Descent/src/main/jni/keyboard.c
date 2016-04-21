//
// Created by devin on 4/17/16.
//

#include <jni.h>
#include "types.h"

extern JavaVM *jvm;
extern jobject Activity;

extern void key_handler(unsigned char scancode, bool down);

int textIsActive() {
    JNIEnv *env;
    jclass clazz;
    jmethodID method;
    jboolean retval;

    (*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_6);
    clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
    method = (*env)->GetMethodID(env, clazz, "textIsActive", "()Z");
    retval = (*env)->CallBooleanMethod(env, Activity, method);
    (*env)->DeleteLocalRef(env, clazz);
    return retval;
}

void activateText() {
    JNIEnv *env;
    jclass clazz;
    jmethodID method;

    (*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_6);
    clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
    method = (*env)->GetMethodID(env, clazz, "activateText", "()V");
    (*env)->CallVoidMethod(env, Activity, method);
    (*env)->DeleteLocalRef(env, clazz);
}

void deactivateText() {
    JNIEnv *env;
    jclass clazz;
    jmethodID method;

    (*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_6);
    clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
    method = (*env)->GetMethodID(env, clazz, "deactivateText", "()V");
    (*env)->CallVoidMethod(env, Activity, method);
    (*env)->DeleteLocalRef(env, clazz);
}

void Java_tuchsen_descent_DescentActivity_keyHandler(JNIEnv *env, jobject thiz, jchar c) {
    key_handler((unsigned char)c, true);
    key_handler((unsigned char)c, false);
}
