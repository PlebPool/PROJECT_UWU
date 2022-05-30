//
// Created by matti on 2022-05-30.
//

#include "../headers/myKeyboardProcHook.h"

const unsigned short W_KEY = 0x57;
const unsigned short O_KEY = 0x4F;
const unsigned short ENTER_KEY = 0x0D;
char lastChar;

namespace uwuHook
{
    HHOOK keyboardHook;
    INPUT wInput{.type = INPUT_KEYBOARD, .ki = {W_KEY}};
    INPUT oInput{.type = INPUT_KEYBOARD, .ki = {O_KEY}};
    INPUT enterInput{.type = INPUT_KEYBOARD, .ki = {ENTER_KEY}};
    clock_t lastTime;
}

LRESULT CALLBACK uwuHook::keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        auto keyValue = (PKBDLLHOOKSTRUCT)lParam;
        if ((char)keyValue->vkCode == 'R' || (char)keyValue->vkCode == 'L')
        {
            SendInput(1, &wInput, sizeof(INPUT));
            return -1;
        }
        if ((char)keyValue->vkCode == 'O')
        {
            if ((!lastTime || clock() - lastTime >= 0.5*CLOCKS_PER_SEC)
                && lastChar != 'O'
                && lastChar != 'C')
            {
                lastTime = clock();
                INPUT inputs[2];
                inputs[0] = oInput;
                inputs[1] = wInput;
                SendInput(2, &inputs[0], sizeof(INPUT));
                return -1;
            }
        }
        lastChar = (char)keyValue->vkCode;
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}