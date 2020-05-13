#ifndef NATIVEANDROID_NATIVE_LIB_H
#define NATIVEANDROID_NATIVE_LIB_H

#include "CApplication.h"

CApplication *g_app = new CApplication();

extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_MainActivity_freeGraphics(JNIEnv *env, jobject thiz);


extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_onCreated(JNIEnv *env, jobject thiz, jint id);


extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_onChanged(JNIEnv *env, jobject thiz, jint id,

                                                       jint width, jint height);
extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_onDraw(JNIEnv *env, jobject thiz, jint id);

extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_loadVertexShader(JNIEnv *env, jobject thiz, jint id,
                                                              jstring shader);

extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_loadFragmentShader(JNIEnv *env, jobject thiz, jint id,
                                                                jstring shader);

extern "C" JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_initShader(JNIEnv *env, jobject thiz, jint id);

extern "C"
JNIEXPORT jint JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_getProgram(JNIEnv *env, jobject thiz, jint id);



#endif //NATIVEANDROID_NATIVE_LIB_H