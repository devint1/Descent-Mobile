//
// Created by devin on 4/19/16.
//
#include <jni.h>
#include "mouse.h"

extern void mouse_handler (short x, short y, bool down);

void Java_tuchsen_descent_DescentGLSurfaceView_mouseHandler(JNIEnv *env, jclass thiz, jshort x,
                                                            jshort y, jboolean down) {
    mouse_handler(x, y, down);
}
