//
// Created by mattias.wegblad on 2022-05-31.
//

#ifndef UWU_MODE_NUWUPROCESSOR_H
#define UWU_MODE_NUWUPROCESSOR_H

#include <vector>
#include "nMyKeyboardProcHook.h"

namespace InputToUwuTranslator
{
    bool getUwuOutputArray(std::vector<INPUT> &dest, DWORD virtualKeyCode);
}

#endif //UWU_MODE_NUWUPROCESSOR_H
