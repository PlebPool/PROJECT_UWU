#include <windows.h>
#include <winuser.h>
#include <ctime>

const unsigned short W_KEY = 0x57;
const unsigned short O_KEY = 0x4F;

HHOOK keyboardHook;

INPUT wInput{};
INPUT oInput{};
clock_t lastTime;

LRESULT CALLBACK KeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        auto keyValue = (char)((PKBDLLHOOKSTRUCT)lParam)->vkCode;
        if (keyValue == 'R' || keyValue == 'L')
        {
            SendInput(1, &wInput, sizeof(INPUT));
            return -1;
        }
        if (keyValue == 'O')
        {
            if (!lastTime || clock() - lastTime >= 0.5*CLOCKS_PER_SEC)
            {
                lastTime = clock();
                INPUT inputs[2];
                inputs[0] = oInput;
                inputs[1] = wInput;
                SendInput(2, &inputs[0], sizeof(INPUT));
                return -1;
            }
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    wInput.type = INPUT_KEYBOARD;
    wInput.ki.wVk = W_KEY;
    oInput.type = INPUT_KEYBOARD;
    oInput.ki.wVk = O_KEY;
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyBoardProc, nullptr, NULL);
    MSG msg{nullptr};
    while (GetMessage(&msg, nullptr, 0, 0) != 0);
    UnhookWindowsHookEx(keyboardHook);
}

