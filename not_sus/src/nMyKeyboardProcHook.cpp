//
// Created by matti on 2022-05-30.
//

#include "../headers/nMyKeyboardProcHook.h"

const DWORD W_KEY = 0x57;
const DWORD O_KEY = 0x4F;
const DWORD U_KEY = 0x55;
const DWORD ENTER_KEY = 0x0D;
const DWORD SPACE_KEY = 0x20;
const DWORD Y_KEY = 0x59;
const DWORD R_KEY = 0x52;
const DWORD L_KEY = 0x4C;
const DWORD HYPHEN_KEY = 0xBD;

DWORD previousInput;

INPUT wInput{.type = INPUT_KEYBOARD, .ki{W_KEY}};
INPUT oInput{.type = INPUT_KEYBOARD, .ki{O_KEY}};
INPUT uInput{.type = INPUT_KEYBOARD, .ki{U_KEY}};
INPUT enterInput{.type = INPUT_KEYBOARD, .ki{ENTER_KEY}};
INPUT spaceInput{.type = INPUT_KEYBOARD, .ki{SPACE_KEY}};
INPUT yInput{.type = INPUT_KEYBOARD, .ki{Y_KEY}}; // Y
INPUT hyphenInput{.type = INPUT_KEYBOARD, .ki{HYPHEN_KEY}};
clock_t coolDown;

void resetCoolDown()
{
    coolDown = clock();
}

bool bOffCoolDown()
{
    return !coolDown || clock() - coolDown >= 0.5 * CLOCKS_PER_SEC;
}

namespace UwuHook
{
    HHOOK keyboardHook;
}
// TODO put a lot of this code in another namespace, separate from this hook one.
LRESULT CALLBACK UwuHook::keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{ // TODO Streamline logical flow with one or two exit "points". (SendInput) or (return CallNextHookEx)
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        bool bDontStutter = false;
        std::vector<INPUT> inputsV;
//        INPUT* inputs;
        size_t inputSize;
        bool bModify = false;

        auto keyValue = (PKBDLLHOOKSTRUCT)lParam;

        switch ((DWORD)keyValue->vkCode)
        {
            case R_KEY: case L_KEY: // R, L
                bModify = true;
                inputSize = 1;
                inputsV.clear();
                inputsV.push_back(wInput);
                break;
//            case O_KEY: // O
//                if ((!coolDown || clock() - coolDown >= 0.5 * CLOCKS_PER_SEC)
//                    && previousInput != 'O'
//                    && previousInput != 'C'
//                    && previousInput != 'Y'
//                    && previousInput != 'W'
//                    && previousInput != 'S'
//                    && previousInput != 'M'
//                    && previousInput != 'T')
//                {
//                    bModify = true;
//                    coolDown = clock();
//                    inputSize = 2;
//                    inputsV.clear();
//                    inputsV.insert(inputsV.end(), {oInput, wInput});
//                }
//                break;
            case ENTER_KEY: // ENTER
                if (bOffCoolDown())
                {
                    bDontStutter = true;
                    bModify = true;
                    resetCoolDown();
                    if (previousInput != SPACE_KEY)
                    { // TODO make these two arrays static, to avoid creating and deleting these arrays everytime.
                        inputSize = 5;
                        inputsV.clear();
                        inputsV.insert(inputsV.end(), {spaceInput, uInput, wInput, uInput, enterInput});
                    } else
                    {
                        inputSize = 4;
                        inputsV.clear();
                        inputsV.insert(inputsV.end(), {uInput, wInput, uInput, enterInput});
                    }
                }
                break;
            case Y_KEY: // Y
                if (bOffCoolDown())
                {
                    resetCoolDown();
                    bModify = true;
                    inputSize = 2;
                    inputsV.clear();
                    inputsV.insert(inputsV.end(), {yInput, yInput});
                }
                break;
        }
        if (!bDontStutter)
        {
            if (previousInput == SPACE_KEY && keyValue->vkCode != SPACE_KEY)
            {
                std::random_device dev;
                std::mt19937 engine (dev());
                std::uniform_real_distribution<float> distribution(0, 1);
                if (distribution(engine) > 0.80)
                {
                    static size_t stutterInputSize = 3;
                    std::vector<INPUT> stutterInputV;
                    if (bModify)
                    {
                        stutterInputV.clear();
                        stutterInputV.insert(stutterInputV.end(), {inputsV[0], hyphenInput, inputsV[0]});
                    } else
                    {
                        INPUT userInput{.type = INPUT_KEYBOARD, .ki{(WORD)keyValue->vkCode}};
                        stutterInputV.clear();
                        stutterInputV.insert(stutterInputV.end(), {userInput, hyphenInput, userInput});
                        bModify = true;
                    }
                    inputsV.insert(inputsV.begin(), stutterInputV.begin(), stutterInputV.end());
                    previousInput = '\0';
                }
            }
        }


        if (bModify)
        {
            SendInput(inputsV.size(), &inputsV[0], sizeof(INPUT));
            return -1;
        }
        previousInput = keyValue->vkCode;
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}