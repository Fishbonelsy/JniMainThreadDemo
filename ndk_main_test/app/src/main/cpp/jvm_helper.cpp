//
// Created by oceanlong on 2018/10/23.
//

#include <jni.h>
#include <string.h>
#include "jvm_helper.h"
#include "logger.h"


JNIEnv *JniHelper::jvmEnv = NULL;

jobject JniHelper::gClassLoader = NULL;
jmethodID JniHelper::gFindClassMethod = NULL;

void JniHelper::setJVM(JNIEnv *env) {
    jvmEnv = env;
    jclass randomClass = env->FindClass("com/example/oceanlong/ndkmaintest/MainActivity");
    jclass classClass = env->GetObjectClass(randomClass);
    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    jmethodID getClassLoaderMethod = env->GetMethodID(classClass, "getClassLoader",
                                                      "()Ljava/lang/ClassLoader;");
    jobject localClassLoader = env->CallObjectMethod(randomClass, getClassLoaderMethod);
    gClassLoader = env->NewGlobalRef(localClassLoader);
    //我在Android中用findClass不行，改成loadClass才可以找到class
    gFindClassMethod = env->GetMethodID(classLoaderClass, "findClass",
                                        "(Ljava/lang/String;)Ljava/lang/Class;");
}

JNIEnv *JniHelper::getJVM() {
    return jvmEnv;
}

jstring JniHelper::char2jstr(const char* pat) {
    JNIEnv *env = getJVM();
    LOGD("char2jstr %p", env);
    // 定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("UTF-8");
    //将byte数组转换为java String,并输出
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);


}

jclass JniHelper::findClass(JNIEnv *env, const char* name) {
    jclass result = nullptr;
    if (env)
    {
        result = env->FindClass(name);
        jthrowable exception = env->ExceptionOccurred();
        if (exception)
        {
            env->ExceptionClear();
            return static_cast<jclass>(env->CallObjectMethod(gClassLoader, gFindClassMethod, env->NewStringUTF(name)));
        }
    }
    return result;
}

const char *JniHelper::jstr2char(JNIEnv *env, const jstring jstr) {
    jboolean isCopy = JNI_TRUE;
    const char *nativeString = env->GetStringUTFChars(jstr , &isCopy);
    return nativeString;
}


