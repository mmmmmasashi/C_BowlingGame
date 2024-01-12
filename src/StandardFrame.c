#include <stddef.h>

#include "StandardFrame.h"
#include "Frame.h"

typedef struct {
    FrameInterface* _funcTable;/* 必ず先頭に置く */
    int _pinNums[FRAME_ROLL_MAX];
    int _ballCount;
    Frame* _nextFrame;
} StandardFrame;

/* Frameモジュールから呼ばれるinterface実装関数*/
static void tellNextFrame(Frame* frame, Frame* nextFrame);
static void destroy(Frame* frame);
static void addRoll(Frame* frame, int pinNum);
static int score(const Frame* frame);
static bool isFull(const Frame* frame);

/* 内部のヘルパー関数 */
static void initFrame(StandardFrame* frame);
static bool isStrike(const StandardFrame* frame);
static bool isSpare(const StandardFrame* frame);
static int sumOfAllPins(const StandardFrame* frame);

static FrameInterface standardFuncTable = {
    tellNextFrame,
    destroy,
    addRoll,
    score,
    isFull,
};

Frame* StandardFrame_Create(void)
{
    StandardFrame* frame = (StandardFrame*)malloc(sizeof(StandardFrame));
    initFrame(frame);
    return (Frame*)frame;
}

static void tellNextFrame(Frame* frame, Frame* nextFrame)
{
    StandardFrame* standardFrame = (StandardFrame*)frame;
    standardFrame->_nextFrame = nextFrame;
}

static void destroy(Frame* frame)
{
    StandardFrame* standardFrame = (StandardFrame*)frame;
    free(standardFrame);
}

static void addRoll(Frame* frame, int pinNum)
{
    StandardFrame* standardFrame = (StandardFrame*)frame;

    int idx = standardFrame->_ballCount;
    standardFrame->_pinNums[idx] = pinNum;
    standardFrame->_ballCount++;
}

static int score(const Frame* frame)
{
    StandardFrame* standardFrame = (StandardFrame*)frame;

    int basicScore = sumOfAllPins(standardFrame);

    if (isStrike(standardFrame))
    {
        int strikeBonus = standardFrame->_nextFrame->_pinNums[0] + standardFrame->_nextFrame->_pinNums[1];
        return basicScore + strikeBonus;
    }
    else if (isSpare(standardFrame))
    {
        int spareBonus = frame->_nextFrame->_pinNums[0];//次フレームの1投目
        return basicScore + spareBonus;
    }
    else
    {
        return basicScore;
    }
}

static bool isFull(const Frame* frame)
{
    StandardFrame* standardFrame = (StandardFrame*)frame;

    if (isStrike(standardFrame)) return true;
    return (standardFrame->_ballCount >= 2);
}

static void initFrame(StandardFrame* frame)
{
    frame->_funcTable = &standardFuncTable;
    frame->_ballCount = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frame->_pinNums[i] = 0;
    }
    frame->_nextFrame = NULL;
}

static bool isStrike(const StandardFrame* frame)
{
    return 10 == frame->_pinNums[0];
}

static bool isSpare(const StandardFrame* frame)
{
    //TODO: strikeでもtrueになる
    return 10 == sumOfAllPins(frame);
}

static int sumOfAllPins(const StandardFrame* frame)
{
    int pinNumTotal = 0;
    for (int i = 0; i < frame->_ballCount; i++)
    {
        pinNumTotal += frame->_pinNums[i];
    }
    return pinNumTotal;
}