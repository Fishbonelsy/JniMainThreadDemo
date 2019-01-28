//
// Created by oceanlong on 2018/10/23.
//

#ifndef NDK_MAIN_TEST_TOAST_HELPER_H
#define NDK_MAIN_TEST_TOAST_HELPER_H

#include <string>

class Toast{
public:
    static Toast * GetInstance();
    void toast(std::string text);

private:
    static Toast *g_Toast;
};

#endif //NDK_MAIN_TEST_TOAST_HELPER_H
