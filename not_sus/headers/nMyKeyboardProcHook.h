//
// Created by matti on 2022-05-30.
//

#ifndef UWU_MODE_NMYKEYBOARDPROCHOOK_H
#define UWU_MODE_NMYKEYBOARDPROCHOOK_H

#include <windows.h>
#include <winuser.h>
#include <ctime>
#include <random>

namespace UwuHook
{
    extern HHOOK keyboardHook;
    extern LRESULT CALLBACK keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
}


#endif //UWU_MODE_NMYKEYBOARDPROCHOOK_H
