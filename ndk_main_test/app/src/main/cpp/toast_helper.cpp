//
// Created by oceanlong on 2018/10/23.
//

#include "toast_helper.h"
#include "jvm_helper.h"
#include "logger.h"

Toast *Toast::g_Toast = NULL;

Toast *Toast::GetInstance() {
    if (!g_Toast){
        g_Toast = new Toast();
    }
    return g_Toast;
}

void Toast::toast(std::string text) {
    JNIEnv *env = JniHelper::getJVM();
    LOGD("toast env : %p", env);

    jstring jtext = JniHelper::char2jstr(text.c_str());

    jclass javaclass = JniHelper::findClass(env,"com/example/oceanlong/ndkmaintest/MainActivity");
    jmethodID jfuncId = env->GetStaticMethodID(javaclass, "toast", "(Ljava/lang/String;)V");
    env->CallStaticVoidMethod(javaclass, jfuncId, jtext);
    env->DeleteLocalRef(jtext);
}
