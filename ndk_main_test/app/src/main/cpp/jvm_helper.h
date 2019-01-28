//
// Created by oceanlong on 2018/10/23.
//

#ifndef NDK_MAIN_TEST_JVM_HELPER_H
#define NDK_MAIN_TEST_JVM_HELPER_H

#include <jni.h>
#include <string>


class JniHelper{

private:
    static JNIEnv *jvmEnv;
    static jobject gClassLoader;
    static jmethodID gFindClassMethod;

public:
    static void setJVM(JNIEnv *env);
    static JNIEnv* getJVM();
    static jstring char2jstr(const char* pat);
    static const char* jstr2char(JNIEnv *env, const jstring jstr);
    static jclass findClass(JNIEnv *env, const char* name);


};


#endif //NDK_MAIN_TEST_JVM_HELPER_H
