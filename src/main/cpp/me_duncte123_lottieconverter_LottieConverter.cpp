#include "gif.h"
#include "../include/me_duncte123_lottieconverter_LottieConverter.h"
#include "./rlottie/inc/rlottie.h"


#include<iostream>
#include<string>
#include<vector>
#include<array>

#ifndef _WIN32
#include<libgen.h>
#else
#include <windows.h>
#include <stdlib.h>
#endif

// Copied from https://github.com/Samsung/rlottie/blob/v0.2/example/lottie2gif.cpp
// All credit goes to the original creators
class GifBuilder {
public:
    explicit GifBuilder(const std::string &fileName, const uint32_t width,
                        const uint32_t height, const int bgColor=0xffffffff, const uint32_t delay = 2)
    {
        GifBegin(&handle, fileName.c_str(), width, height, delay);
        bgColorR = (uint8_t) ((bgColor & 0xff0000) >> 16);
        bgColorG = (uint8_t) ((bgColor & 0x00ff00) >> 8);
        bgColorB = (uint8_t) ((bgColor & 0x0000ff));
    }
    ~GifBuilder()
    {
        GifEnd(&handle);
    }
    void addFrame(rlottie::Surface &s, uint32_t delay = 2)
    {
        argbTorgba(s);
        GifWriteFrame(&handle,
                      reinterpret_cast<uint8_t *>(s.buffer()),
                      s.width(),
                      s.height(),
                      delay);
    }
    void argbTorgba(rlottie::Surface &s)
    {
        uint8_t *buffer = reinterpret_cast<uint8_t *>(s.buffer());
        uint32_t totalBytes = s.height() * s.bytesPerLine();

        for (uint32_t i = 0; i < totalBytes; i += 4) {
            unsigned char a = buffer[i+3];
            // compute only if alpha is non zero
            if (a) {
                unsigned char r = buffer[i+2];
                unsigned char g = buffer[i+1];
                unsigned char b = buffer[i];

                if (a != 255) { //un premultiply
                    unsigned char r2 = (unsigned char) ((float) bgColorR * ((float) (255 - a) / 255));
                    unsigned char g2 = (unsigned char) ((float) bgColorG * ((float) (255 - a) / 255));
                    unsigned char b2 = (unsigned char) ((float) bgColorB * ((float) (255 - a) / 255));
                    buffer[i] = r + r2;
                    buffer[i+1] = g + g2;
                    buffer[i+2] = b + b2;

                } else {
                    // only swizzle r and b
                    buffer[i] = r;
                    buffer[i+2] = b;
                }
            } else {
                buffer[i+2] = bgColorB;
                buffer[i+1] = bgColorG;
                buffer[i] = bgColorR;
            }
        }
    }

private:
    GifWriter      handle;
    uint8_t bgColorR, bgColorG, bgColorB;
};

std::string jstring2string(JNIEnv *env, jstring jStr) {
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

JNIEXPORT jstring JNICALL Java_me_duncte123_lottieconverter_LottieConverter_getMessage
  (JNIEnv *env, jobject thisObject) {
    return env->NewStringUTF("This is a test from C++");
}

JNIEXPORT jbyteArray JNICALL Java_me_duncte123_lottieconverter_LottieConverter_generateGif
        (JNIEnv *env, jobject thisObject, jstring lottieJson, jstring cacheKey) {
    auto animation = rlottie::Animation::loadFromData(
            jstring2string(env, lottieJson),
            jstring2string(env, cacheKey)
    );

//    size_t width;
//    size_t height;

//    animation->size(width, height);
//
//    auto buffer = std::unique_ptr<uint32_t[]>(new uint32_t[width * height]);
//    size_t frameCount = animation->totalFrame();

//    // TODO: figure out how to make it return bytes
//    GifBuilder builder("tmp-gif-test.gif", width, height);

//    for (size_t i = 0; i < frameCount ; i++) {
//        rlottie::Surface surface(buffer.get(), width, height, width * 4);
//        animation->renderSync(i, surface);
//        builder.addFrame(surface);
//    }

//    std::cout<<"Generated GIF file : tmp-gif-test.gif"<<std::endl;

    return env->NewByteArray(0);
}
