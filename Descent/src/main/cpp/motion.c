//
// Created by devin on 4/17/16.
//

#include <fix.h>
#include <jni.h>
#include <kconfig.h>

extern JavaVM *jvm;
extern jobject Activity;

void startMotion() {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
	method = (*env)->GetMethodID(env, clazz, "startMotion", "()V");
	(*env)->CallVoidMethod(env, Activity, method);
	(*env)->DeleteLocalRef(env, clazz);
}

void stopMotion() {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
	method = (*env)->GetMethodID(env, clazz, "stopMotion", "()V");
	(*env)->CallVoidMethod(env, Activity, method);
	(*env)->DeleteLocalRef(env, clazz);
}

void getRotationRate(double *x, double *y, double *z) {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;
	jfloatArray acceleration;
	jfloat *accelerationElements;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
	method = (*env)->GetMethodID(env, clazz, "getRotationRate", "()[F");
	acceleration = (*env)->CallObjectMethod(env, Activity, method);
	accelerationElements = (*env)->GetFloatArrayElements(env, acceleration, 0);
	*x = accelerationElements[0];
	*y = accelerationElements[1];
	*z = accelerationElements[2];
	(*env)->ReleaseFloatArrayElements(env, acceleration, accelerationElements, 0);
	(*env)->DeleteLocalRef(env, clazz);
	(*env)->DeleteLocalRef(env, acceleration);
}

int haveGyroscope() {
	JNIEnv *env;
	jclass clazz;
	jmethodID method;
	jboolean gyroscope;

	(*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6);
	clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
	method = (*env)->GetMethodID(env, clazz, "haveGyroscope", "()Z");
	gyroscope = (*env)->CallBooleanMethod(env, Activity, method);
	(*env)->DeleteLocalRef(env, clazz);
	return gyroscope;
}

jboolean Java_tuchsen_descent_DescentActivity_getUseGyroscope(JNIEnv *env, jclass type) {
	return Config_use_gyroscope;
}
