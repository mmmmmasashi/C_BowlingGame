#include "Frame.h"

Frame* Frame_Create(void)
{
    Frame* frame = (Frame*)malloc(sizeof(Frame));

    frame->_ballCount = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frame->_pinNums[i] = 0;
    }
    
    return frame;
}

void Frame_AddPin(Frame* frame, int pinNum)
{
    int idx = frame->_ballCount;
    frame->_pinNums[idx] = pinNum;
    frame->_ballCount++;
}

int Frame_Score(Frame* frame)
{
    int frameScore = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frameScore += frame->_pinNums[i];
    }

    return frameScore;
}