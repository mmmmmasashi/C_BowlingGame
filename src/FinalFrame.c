#include <stddef.h>

#include "FinalFrame.h"

enum { FRAME_ROLL_MAX = 2 };

typedef struct {
    FrameInterface* _funcTable;/* 必ず先頭に置く */
    int _pinNums[FRAME_ROLL_MAX];
    int _ballCount;
    Frame* _nextFrame;
} FinalFrame;

/* Frameモジュールから呼ばれるinterface実装関数*/
static void tellNextFrame(Frame* frame, Frame* nextFrame);
static void destroy(Frame* frame);
static void addRoll(Frame* frame, int pinNum);
static int score(const Frame* frame);
static bool isFull(const Frame* frame);
static int bonusForSpare(const Frame* frame);
static int bonusForStrike(const Frame* frame);

/* 内部のヘルパー関数 */
static void initFrame(FinalFrame* frame);
static bool isStrike(const FinalFrame* frame);
static bool isSpare(const FinalFrame* frame);
static int sumOfAllPins(const FinalFrame* frame);

static FrameInterface standardFuncTable = {
    tellNextFrame,
    destroy,
    addRoll,
    score,
    isFull,
    bonusForSpare,
    bonusForStrike,
};

Frame* FinalFrame_Create(void)
{
    FinalFrame* frame = (FinalFrame*)malloc(sizeof(FinalFrame));
    initFrame(frame);
    return (Frame*)frame;
}

static void tellNextFrame(Frame* frame, Frame* nextFrame)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;
    standardFrame->_nextFrame = nextFrame;
}

static void destroy(Frame* frame)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;
    free(standardFrame);
}

static void addRoll(Frame* frame, int pinNum)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;

    int idx = standardFrame->_ballCount;
    standardFrame->_pinNums[idx] = pinNum;
    standardFrame->_ballCount++;
}

static int score(const Frame* frame)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;
    Frame* nextFrame = standardFrame->_nextFrame;

    int basicScore = sumOfAllPins(standardFrame);

    if (isStrike(standardFrame))
    {
        return basicScore + Frame_BonusForStrike(nextFrame);
    }
    else if (isSpare(standardFrame))
    {
        return basicScore + Frame_BonusForSpare(nextFrame);
    }
    else
    {
        return basicScore;
    }
}

static bool isFull(const Frame* frame)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;

    if (isStrike(standardFrame)) return true;
    return (standardFrame->_ballCount >= 2);
}

static int bonusForSpare(const Frame* frame)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;
    return standardFrame->_pinNums[0];
}

static int bonusForStrike(const Frame* frame)
{
    FinalFrame* standardFrame = (FinalFrame*)frame;
    return standardFrame->_pinNums[0] + standardFrame->_pinNums[1];
}

static void initFrame(FinalFrame* frame)
{
    frame->_funcTable = &standardFuncTable;
    frame->_ballCount = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frame->_pinNums[i] = 0;
    }
    frame->_nextFrame = NULL;
}

static bool isStrike(const FinalFrame* frame)
{
    return 10 == frame->_pinNums[0];
}

static bool isSpare(const FinalFrame* frame)
{
    //TODO: strikeでもtrueになる
    return 10 == sumOfAllPins(frame);
}

static int sumOfAllPins(const FinalFrame* frame)
{
    int pinNumTotal = 0;
    for (int i = 0; i < frame->_ballCount; i++)
    {
        pinNumTotal += frame->_pinNums[i];
    }
    return pinNumTotal;
}