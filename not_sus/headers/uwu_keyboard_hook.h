//
// Created by matti on 2022-05-30.
//

#ifndef UWU_MODE_UWU_KEYBOARD_HOOK_H
#define UWU_MODE_UWU_KEYBOARD_HOOK_H

#include <windows.h>

namespace uwu_keyboard_hook
{
    extern HHOOK keyboardHook;
    extern LRESULT CALLBACK keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
}


#endif //UWU_MODE_UWU_KEYBOARD_HOOK_H
