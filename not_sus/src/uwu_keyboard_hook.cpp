//
// Created by matti on 2022-05-30.
//

#include "../headers/uwu_keyboard_hook.h"
#include "../headers/input_to_uwu_translator.h"

namespace uwu_keyboard_hook
{
    HHOOK keyboardHook;
}

LRESULT CALLBACK uwu_keyboard_hook::keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        std::vector<INPUT> inputsV;
        bool bModify;

        auto keyValue = (PKBDLLHOOKSTRUCT)lParam;

        bModify = input_to_uwu_translator::getUwuOutputArray(inputsV, keyValue->vkCode);

        if (bModify)
        {
            SendInput(inputsV.size(), &inputsV[0], sizeof(INPUT));
            return -1;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}