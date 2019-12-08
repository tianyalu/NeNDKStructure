#include <jni.h>
#include <string>

//混合式编译
extern "C" {
#include <libavcodec/avcodec.h>
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_sty_ne_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(av_version_info()); //4.0.5
}
