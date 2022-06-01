//
// Created by matti on 2022-05-30.
//

#include "../headers/nMyKeyboardProcHook.h"
#include "../headers/nUwuProcessor.h"

namespace UwuHook
{
    HHOOK keyboardHook;
}

LRESULT CALLBACK UwuHook::keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        std::vector<INPUT> inputsV;
        bool bModify;

        auto keyValue = (PKBDLLHOOKSTRUCT)lParam;

        bModify = InputToUwuTranslator::getUwuOutputArray(inputsV, keyValue->vkCode);

        if (bModify)
        {
            SendInput(inputsV.size(), &inputsV[0], sizeof(INPUT));
            return -1;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}