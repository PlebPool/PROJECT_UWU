//
// Created by matti on 2022-05-30.
//

#include "../headers/uwu_keyboard_hook.h"
#include "../headers/input_to_uwu_translator.h"

namespace uwu_keyboard_hook
{
    HHOOK keyboardHook;
}

/**
 * If the key pressed is a key that needs to be translated, then translate it and send the translated keystrokes to the
 * system
 *
 * @param nCode The hook code passed to the current hook procedure. The next hook procedure uses this code to determine how
 * to process the hook information.
 * @param wParam The type of keyboard message.
 * @param lParam The lParam parameter is a pointer to a KBDLLHOOKSTRUCT structure.
 *
 * @return The return value is the result of the next hook procedure in the hook chain, or a -1 if we want to
 * send our own input instead.
 */
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