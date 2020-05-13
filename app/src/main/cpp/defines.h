#ifndef NATIVEANDROID_DEFINES_H
#define NATIVEANDROID_DEFINES_H

#include <android/log.h>
#include <vector>
#include <cstdio>

#define  LOG_TAG    "NATIVE_LOG"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //NATIVEANDROID_DEFINES_H
