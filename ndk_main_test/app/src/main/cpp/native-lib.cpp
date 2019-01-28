#include <jni.h>
#include <string>
#include "main_looper.h"
#include "jvm_helper.h"

extern "C"
{

JNIEXPORT void JNICALL
Java_com_example_oceanlong_ndkmaintest_MainActivity_init(JNIEnv *env, jobject instance) {

    JniHelper::setJVM(env);

    MainLooper::GetInstance()->init();
    LOGD("init env : %p", env);


}

JNIEXPORT jstring

JNICALL
Java_com_example_oceanlong_ndkmaintest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_com_example_oceanlong_ndkmaintest_MainActivity_nativeToast(JNIEnv *env, jobject instance, jstring text_) {
    const char* ctext = JniHelper::jstr2char(env, text_);
    LOGD("nativeToast  : %s", ctext);
    MainLooper::GetInstance()->send(ctext);
    env->ReleaseStringUTFChars(text_, ctext);

}


}
