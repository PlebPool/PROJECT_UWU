//
// Created by matti on 2022-05-30.
//

#include "../headers/myKeyboardProcHook.h"

const unsigned short W_KEY = 0x57;
const unsigned short O_KEY = 0x4F;
const unsigned short U_KEY = 0x55;
const unsigned short ENTER_KEY = 0x0D;
const unsigned short SPACE_KEY = 0x20;
DWORD lastInput;

DWORD toBePrintedByNext; // Maybe rename to "trailingW"
bool skipToBePrintedBtNext = false;

namespace uwuHook
{
    HHOOK keyboardHook;
    INPUT wInput{.type = INPUT_KEYBOARD, .ki = {W_KEY}};
    INPUT oInput{.type = INPUT_KEYBOARD, .ki = {O_KEY}};
    INPUT uInput{.type = INPUT_KEYBOARD, .ki = {U_KEY}};
    INPUT enterInput{.type = INPUT_KEYBOARD, .ki = {ENTER_KEY}};
    INPUT spaceInput{.type = INPUT_KEYBOARD, .ki = {SPACE_KEY}};
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
//        if ((char)keyValue->vkCode == 'O') // TODO look into toBePrintedByNext.
//        {
//            if ((!lastTime || clock() - lastTime >= 0.5*CLOCKS_PER_SEC) && lastInput != 'O' && lastInput != 'C')
//            {
//                lastTime = clock();
//                INPUT inputs[] = {oInput, wInput};
//                SendInput(2, &inputs[0], sizeof(INPUT));
//                return -1;
//            }
//        }
        if ((!lastTime || clock() - lastTime >= 0.5*CLOCKS_PER_SEC) && keyValue->vkCode == ENTER_KEY)
        {
            lastTime = clock();
            unsigned int size;
            INPUT* inputs;
            if (lastInput != SPACE_KEY)
            { // TODO make these two arrays static, to avoid creating and deleting these arrays everytime.
                inputs = new INPUT[5]{spaceInput, uInput, wInput, uInput, enterInput};
                size = 5;
            } else
            {
                inputs = new INPUT[4]{uInput, wInput, uInput, enterInput};
                size = 4;
            }
            SendInput(size, &inputs[0], sizeof(INPUT));
            delete [] inputs;
            return -1;
        }
        lastInput = keyValue->vkCode;
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}