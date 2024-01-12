#include <stddef.h>
#include "Frame.h"

static void initFrame(Frame* frame);
static bool isSpare(const Frame* frame);
static int sumOfAllPins(const Frame* frame);

Frame* Frame_Create(void)
{
    Frame* frame = (Frame*)malloc(sizeof(Frame));
    initFrame(frame);
    return frame;
}

void Frame_TellNextFrame(Frame* frame, Frame* nextFrame)
{
    frame->_nextFrame = nextFrame;
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
    int basicScore = sumOfAllPins(frame);

    if (isSpare(frame))
    {
        int spareBonus = frame->_nextFrame->_pinNums[0];//次フレームの1投目
        return basicScore + spareBonus;
    }
    else
    {
        return basicScore;
    }
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
    frame->_nextFrame = NULL;
}

static bool isSpare(const Frame* frame)
{
    //TODO: strikeでもtrueになる
    return 10 == sumOfAllPins(frame);
}

static int sumOfAllPins(const Frame* frame)
{
    int pinNumTotal = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        pinNumTotal += frame->_pinNums[i];
    }
    return pinNumTotal;
}