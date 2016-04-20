//
// Created by devin on 4/17/16.
//

#include <android/sensor.h>
#include <jni.h>

extern JavaVM *jvm;
extern jobject Activity;

void startMotion() {

}

void getAttitude(double *roll, double *pitch, double *yaw) {
    JNIEnv *env;
    jclass clazz;
    jmethodID method;
    jfloatArray orientation;
    jfloat *orientationElements;

    (*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_6);
    clazz = (*env)->FindClass(env, "tuchsen/descent/DescentActivity");
    method = (*env)->GetMethodID(env, clazz, "getOrientation", "()[F");
    orientation = (*env)->CallObjectMethod(env, Activity, method);
    orientationElements = (*env)->GetFloatArrayElements(env, orientation, 0);
    *yaw = orientationElements[0];
    *pitch = orientationElements[1];
    *roll = orientationElements[2];
    (*env)->ReleaseFloatArrayElements(env, orientation, orientationElements, 0);
    (*env)->DeleteLocalRef(env, clazz);
    (*env)->DeleteLocalRef(env, orientation);
}

void getRotationRate(double *x, double *y, double *z) {

}

void getAcceleration(double *x, double *y, double *z) {

}
