//
// Created by mattias.wegblad on 2022-05-31.
//

#include <ctime>
#include "../headers/nUwuProcessor.h"
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

clock_t coolDown;

DWORD previousInput;

void resetCoolDown()
{
    coolDown = clock();
}

bool bOffCoolDown()
{
    return !coolDown || clock() - coolDown >= 0.5 * CLOCKS_PER_SEC;
}

void insertUwu(std::vector<INPUT> &dest, bool clearVectorBefore)
{
    if (clearVectorBefore) dest.clear();
    if (previousInput != SPACE_KEY)
    {
        dest.insert(dest.end(), {spaceInput, uInput, wInput, uInput, enterInput});
    }
    else
    {
        dest.insert(dest.end(), {uInput, wInput, uInput, enterInput});
    }
}

void insertTwice(std::vector<INPUT> &dest, INPUT &input, bool clearVectorBefore)
{
    if (clearVectorBefore) dest.clear();
    dest.insert(dest.end(), {input, input});
}

int nUwuProcessor::getUwuOutputArray(std::vector<INPUT> &dest, DWORD virtualKeyCode)
{
    bool isModified = false;
    switch (virtualKeyCode)
    {
        case R_KEY: case L_KEY:
            isModified = true;
            dest.clear();
            dest.push_back(wInput);
            return 0;
        case ENTER_KEY:
            isModified = true;
            if (previousInput != ENTER_KEY)
            {
                insertUwu(dest, true);
            }
            return 0;
        case Y_KEY:
            isModified = true;
            insertTwice(dest, yInput, true);
            previousInput = '\0'; // To avoid looping.
            return 0;
        default:
            break;
    }

    if (previousInput == SPACE_KEY && virtualKeyCode != SPACE_KEY)
    {
        std::random_device device;
        std::mt19937 engine(device());
        std::uniform_real_distribution<float> distribution(0, 1);
        if (distribution(engine) > 0.80)
        {
            std::vector<INPUT> stutterVector;
            // TODO WIP
            previousInput = '\0'; // To avoid looping.
        }
    }
}
