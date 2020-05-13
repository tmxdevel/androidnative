#include <jni.h>
#include <string>
#include <cstdio>

#include "defines.h"
#include "native-lib.h"
#include "CRenderer.h"

std::string fromJString(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_MainActivity_freeGraphics(JNIEnv *env, jobject thiz) {
    if(g_app != nullptr) {
        delete g_app;
        g_app = nullptr;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_onCreated(JNIEnv *env, jobject thiz, jint id){
    CRenderer *renderer = g_app->getRenderer(id);
    renderer->onCreate();
    LOGD("Created renderer with id: %d", id);
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_onChanged(JNIEnv *env, jobject thiz, jint id,
                                                       jint width, jint height) {
    CRenderer *renderer = g_app->getRenderer(id);
    renderer->onChanged(width,height);
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_onDraw(JNIEnv *env, jobject thiz, jint id) {
    CRenderer *renderer = g_app->getRenderer(id);
    renderer->onDraw();
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_loadVertexShader(JNIEnv *env, jobject thiz, jint id,
                                                              jstring shader) {
    CRenderer *renderer = g_app->getRenderer(id);
    renderer->setVertexShader(fromJString(env, shader));
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_loadFragmentShader(JNIEnv *env, jobject thiz, jint id,
                                                                jstring shader) {
    CRenderer *renderer = g_app->getRenderer(id);
    renderer->setFragmentShader(fromJString(env, shader));
}

extern "C"
JNIEXPORT void JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_initShader(JNIEnv *env, jobject thiz, jint id) {
    CRenderer *renderer = g_app->getRenderer(id);
    renderer->initShaders();
}

extern "C"
JNIEXPORT jint JNICALL
Java_ind_tmxdev_nativeandroid_NativeRenderer_getProgram(JNIEnv *env, jobject thiz, jint id) {
    CRenderer *renderer = g_app->getRenderer(id);
    return renderer->programId();
}

