//
// Created by oceanlong on 2018/10/17.
//

#include <fcntl.h>
#include "main_looper.h"
#include <stdint.h>
#include "string.h"
#include <stdlib.h>
#include <unistd.h>
#include "toast_helper.h"

#define LOOPER_MSG_LENGTH 81

MainLooper *MainLooper::g_MainLooper = NULL;


MainLooper *MainLooper::GetInstance()
{
    if (!g_MainLooper)
    {
        g_MainLooper = new MainLooper();
    }
    return g_MainLooper;
}

MainLooper::MainLooper(){
    pthread_mutex_init(&looper_mutex_, NULL);
}

MainLooper::~MainLooper() {
    if (mainlooper && readpipe != -1)
    {
        ALooper_removeFd(mainlooper, readpipe);
    }
    if (readpipe != -1)
    {
        close(readpipe);
    }
    if (writepipe != -1)
    {
        close(writepipe);
    }
    pthread_mutex_destroy(&looper_mutex_);
}

void MainLooper::init() {

    int msgpipe[2];
    pipe(msgpipe);
    readpipe = msgpipe[0];
    writepipe = msgpipe[1];

    mainlooper = ALooper_prepare(0);
    int ret = ALooper_addFd(mainlooper, readpipe, 1, ALOOPER_EVENT_INPUT, MainLooper::handle_message, NULL);
}



int MainLooper::handle_message(int fd, int events, void *data) {

    char buffer[LOOPER_MSG_LENGTH];
    memset(buffer, 0, LOOPER_MSG_LENGTH);
    read(fd, buffer, sizeof(buffer));
    LOGD("receive msg %s" , buffer);
    Toast::GetInstance()->toast(buffer);
    return 1;
}


void MainLooper::send(const char *msg) {

    pthread_mutex_lock(&looper_mutex_);
    LOGD("send msg %s" , msg);
    write(writepipe, msg, strlen(msg));
    pthread_mutex_unlock(&looper_mutex_);
}

