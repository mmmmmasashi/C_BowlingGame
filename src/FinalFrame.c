#include <stddef.h>

#include "FinalFrame.h"

enum { FRAME_ROLL_MAX = 3 };

typedef struct {
    FrameInterface* _funcTable;/* 必ず先頭に置く */
    int _pinNums[FRAME_ROLL_MAX];
    int _ballCount;
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

static FrameInterface finalFrameFuncTable = {
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
    //do nothing
    //TODO:このIFがあるのが不自然。Interface構造体から削除する予定
}

static void destroy(Frame* frame)
{
    FinalFrame* finalFrame = (FinalFrame*)frame;
    free(finalFrame);
}

static void addRoll(Frame* frame, int pinNum)
{
    printf("*");
    FinalFrame* finalFrame = (FinalFrame*)frame;

    int idx = finalFrame->_ballCount;
    finalFrame->_pinNums[idx] = pinNum;
    finalFrame->_ballCount++;
}

static int score(const Frame* frame)
{
    FinalFrame* finalFrame = (FinalFrame*)frame;
    return sumOfAllPins(finalFrame);
}

static bool isFull(const Frame* frame)
{
    FinalFrame* finalFrame = (FinalFrame*)frame;

    if (finalFrame->_ballCount == 0) return false;
    if (finalFrame->_ballCount == 1) return false;
    if (finalFrame->_ballCount == 2)
    {
        if (isStrike(finalFrame)) return false;
        if (isSpare(finalFrame)) return false;
    }

    return true;
}

static int bonusForSpare(const Frame* frame)
{
    FinalFrame* finalFrame = (FinalFrame*)frame;
    return finalFrame->_pinNums[0];
}

static int bonusForStrike(const Frame* frame)
{
    FinalFrame* finalFrame = (FinalFrame*)frame;
    return finalFrame->_pinNums[0] + finalFrame->_pinNums[1];
}

static void initFrame(FinalFrame* frame)
{
    frame->_funcTable = &finalFrameFuncTable;
    frame->_ballCount = 0;
    for (int i = 0; i < FRAME_ROLL_MAX; i++)
    {
        frame->_pinNums[i] = 0;
    }
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