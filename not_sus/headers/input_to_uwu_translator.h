//
// Created by mattias.wegblad on 2022-05-31.
//

#ifndef UWU_MODE_INPUT_TO_UWU_TRANSLATOR_H
#define UWU_MODE_INPUT_TO_UWU_TRANSLATOR_H

#include <vector>
#include "uwu_keyboard_hook.h"

namespace input_to_uwu_translator
{
    bool getUwuOutputArray(std::vector<INPUT> &dest, DWORD virtualKeyCode);
}

#endif //UWU_MODE_INPUT_TO_UWU_TRANSLATOR_H
