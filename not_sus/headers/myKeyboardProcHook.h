//
// Created by matti on 2022-05-30.
//

#ifndef UWU_MODE_MYKEYBOARDPROCHOOK_H
#define UWU_MODE_MYKEYBOARDPROCHOOK_H

#include <windows.h>
#include <winuser.h>
#include <ctime>

namespace uwuHook
{
    extern HHOOK keyboardHook;
    extern INPUT wInput;
    extern INPUT oInput;
    extern INPUT enterInput;
    extern clock_t lastTime;
    extern LRESULT CALLBACK keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
}


#endif //UWU_MODE_MYKEYBOARDPROCHOOK_H
