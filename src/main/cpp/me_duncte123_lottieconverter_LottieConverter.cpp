#include "../include/me_duncte123_lottieconverter_LottieConverter.h"

JNIEXPORT jstring JNICALL Java_me_duncte123_lottieconverter_LottieConverter_getMessage
  (JNIEnv *env, jobject thisObject) {
    return env->NewStringUTF("This is a test from C++");
}
