//
// Created by mattias.wegblad on 2022-05-31.
//

#include <ctime>
#include "../headers/input_to_uwu_translator.h"
#include <random>

const DWORD W_KEY = 0x57;
const DWORD O_KEY = 0x4F;
const DWORD U_KEY = 0x55;
const DWORD ENTER_KEY = 0x0D;
const DWORD SPACE_KEY = 0x20;
const DWORD Y_KEY = 0x59;
const DWORD R_KEY = 0x52;
const DWORD L_KEY = 0x4C;
const DWORD HYPHEN_KEY = 0xBD;

INPUT wInput{.type = INPUT_KEYBOARD, .ki{W_KEY}};
INPUT oInput{.type = INPUT_KEYBOARD, .ki{O_KEY}};
INPUT uInput{.type = INPUT_KEYBOARD, .ki{U_KEY}};
INPUT enterInput{.type = INPUT_KEYBOARD, .ki{ENTER_KEY}};
INPUT spaceInput{.type = INPUT_KEYBOARD, .ki{SPACE_KEY}};
INPUT yInput{.type = INPUT_KEYBOARD, .ki{Y_KEY}}; // Y
INPUT hyphenInput{.type = INPUT_KEYBOARD, .ki{HYPHEN_KEY}};

clock_t coolDown = '\0';

DWORD previousInput;

void resetCoolDown()
{
    coolDown = clock();
}

bool bOffCoolDown()
{
    if (coolDown == '\0')
    {
        return true;
    }
    else
    {
        return clock() - coolDown >= 0.5 * CLOCKS_PER_SEC;
    }
}

bool insertUwu(std::vector<INPUT> &dest, bool clearVectorBefore)
{
    if (clearVectorBefore) dest.clear();
    if (bOffCoolDown())
    {
        resetCoolDown();
        if (previousInput != SPACE_KEY)
        {
            dest.insert(dest.end(), {spaceInput, uInput, wInput, uInput, enterInput});
        }
        else
        {
            dest.insert(dest.end(), {uInput, wInput, uInput, enterInput});
        }
        return true;
    }
    return false;
}

bool insertTwice(std::vector<INPUT> &dest, INPUT &input, bool clearVectorBefore)
{
    if (bOffCoolDown())
    {
        resetCoolDown();
        if (clearVectorBefore) dest.clear();
        dest.insert(dest.end(), {input, input});
        return true;
    }
    return false;
}

bool keySwapper(std::vector<INPUT> &dest, DWORD &virtualKeyCode)
{
    switch (virtualKeyCode)
    {
        case R_KEY: case L_KEY:
            dest.clear();
            dest.push_back(wInput);
            return true;
        case ENTER_KEY:
            if (previousInput != ENTER_KEY)
            {
                return insertUwu(dest, true);
            }
        case Y_KEY:
            return insertTwice(dest, yInput, true);
        default:
            break;
    }
    return false;
}

bool input_to_uwu_translator::getUwuOutputArray(std::vector<INPUT> &dest, DWORD virtualKeyCode)
{
    bool isModified;

    isModified = keySwapper(dest, virtualKeyCode);

    if (previousInput == SPACE_KEY && virtualKeyCode != SPACE_KEY)
    {
        std::random_device device;
        std::mt19937 engine(device());
        std::uniform_real_distribution<float> distribution(0, 1);
        if (distribution(engine) > 0.80)
        {
            isModified = true;
            std::vector<INPUT> stutterVector;
            INPUT dynamicInput{.type = INPUT_KEYBOARD, .ki{static_cast<WORD>(virtualKeyCode)}};
            stutterVector.insert(stutterVector.end(),
                                 {dynamicInput,
                                  hyphenInput,
                                  dynamicInput}
                                 );
            dest.insert(dest.begin(), stutterVector.begin(), stutterVector.end());
            previousInput = '\0'; // To avoid looping.
        }
    }

    if (!isModified)
    {
        previousInput = virtualKeyCode;
    }

    return isModified;
}
