#include <stddef.h>
#include "Frame.h"

void Frame_Destroy(Frame* frame)
{
    frame->_funcTable->Destroy(frame);
}

void Frame_AddRoll(Frame* frame, int pinNum)
{
    frame->_funcTable->AddRoll(frame, pinNum);
}

int Frame_Score(const Frame* frame)
{
    return frame->_funcTable->Score(frame);
}

bool Frame_IsFull(const Frame* frame)
{
    return frame->_funcTable->IsFull(frame);
}

int Frame_BonusForSpare(const Frame* frame)
{
    return frame->_funcTable->BonusForSpare(frame);
}

int Frame_BonusForStrike(const Frame* frame)
{
    return frame->_funcTable->BonusForStrike(frame);
}
