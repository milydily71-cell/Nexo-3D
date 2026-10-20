#if defined(__ANDROID__)
#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <mutex>

namespace {
constexpr const char* kTag = "Nexo3D";
std::mutex gMutex;
ANativeWindow* gWindow = nullptr;
int gWidth = 0;
int gHeight = 0;
bool gInitialized = false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_nexo3d_NexoActivity_nativeInit(JNIEnv* env, jclass, jobject surface, jint width, jint height) {
    std::lock_guard<std::mutex> lock(gMutex);
    if (gWindow != nullptr) {
        ANativeWindow_release(gWindow);
        gWindow = nullptr;
    }
    gWindow = ANativeWindow_fromSurface(env, surface);
    gWidth = width;
    gHeight = height;
    gInitialized = gWindow != nullptr;
    __android_log_print(ANDROID_LOG_INFO, kTag,
        "Native surface attached (%dx%d). Vulkan swapchain/render loop is the next renderer milestone.",
        gWidth, gHeight);
    return gInitialized ? JNI_TRUE : JNI_FALSE;
}

extern "C" JNIEXPORT void JNICALL
Java_com_nexo3d_NexoActivity_nativeResize(JNIEnv*, jclass, jint width, jint height) {
    std::lock_guard<std::mutex> lock(gMutex);
    gWidth = width;
    gHeight = height;
    __android_log_print(ANDROID_LOG_VERBOSE, kTag, "Viewport resized to %dx%d", width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_nexo3d_NexoActivity_nativeTouch(JNIEnv*, jclass, jint action, jfloat x, jfloat y, jint pointers) {
    __android_log_print(ANDROID_LOG_VERBOSE, kTag, "Touch action=%d x=%.1f y=%.1f pointers=%d",
        action, x, y, pointers);
}

extern "C" JNIEXPORT void JNICALL
Java_com_nexo3d_NexoActivity_nativeShutdown(JNIEnv*, jclass) {
    std::lock_guard<std::mutex> lock(gMutex);
    gInitialized = false;
    if (gWindow != nullptr) {
        ANativeWindow_release(gWindow);
        gWindow = nullptr;
    }
    __android_log_print(ANDROID_LOG_INFO, kTag, "Native surface detached");
}
#endif
