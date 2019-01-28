//
// Created by oceanlong on 2018/10/17.
//

#ifndef NDK_MAIN_TEST_MAIN_LOOPER_H
#define NDK_MAIN_TEST_MAIN_LOOPER_H

#include <android/looper.h>
#include <string>
#include "logger.h"

class MainLooper
{
public:
    static MainLooper *GetInstance();
    ~MainLooper();
    void init();
    void send(const char* msg);

private:
    static MainLooper *g_MainLooper;
    MainLooper();
    ALooper* mainlooper;
    int readpipe;
    int writepipe;
    pthread_mutex_t looper_mutex_;
    static int handle_message(int fd, int events, void *data);
};

#endif //NDK_MAIN_TEST_MAIN_LOOPER_H
