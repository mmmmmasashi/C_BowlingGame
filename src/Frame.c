#include "Frame.h"

static void initFrame(Frame* frame);

Frame* Frame_Create(void)
{
    Frame* frame = (Frame*)malloc(sizeof(Frame));
    initFrame(frame);
    return frame;
}

void Frame_Destroy(Frame* frame)
{
    free(frame);
}

void Frame_AddRoll(Frame* frame, int pinNum)
{
    int idx = frame->_ballCount;
    frame->_pinNums[idx] = pinNum;
    frame->_ballCount++;
}

int Frame_Score(const Frame* frame)
{
    int frameScore = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frameScore += frame->_pinNums[i];
    }

    return frameScore;
}

bool Frame_IsFull(const Frame* frame)
{
    return (frame->_ballCount >= 2);
}

static void initFrame(Frame* frame)
{
    frame->_ballCount = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frame->_pinNums[i] = 0;
    }
}