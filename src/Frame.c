#include "Frame.h"
#include <stdbool.h>

#define BALL_MAX (2)

typedef struct StandardFrameStruct {
    IFrameStruct base;//ハマりメモ : ここは構造体。interfaceと同じデータ構造なので
    int pinNums[BALL_MAX];
    int ballCount;
} StandardFrameStruct;

typedef struct StandardFrameStruct* StandardFrame;
static bool addPins(IFrame frame, int pinNum)
{
    StandardFrame standardFrame = (StandardFrame)frame;
    if (standardFrame->ballCount >= BALL_MAX) return false;

    int idx = standardFrame->ballCount;
    standardFrame->pinNums[idx] = pinNum;
    standardFrame->ballCount++;
    return true;
}

static int score(IFrame frame)
{
    StandardFrame standardFrame = (StandardFrame)frame;
    int totalScore = 0;
    for (int i = 0; i < standardFrame->ballCount; i++)
    {
        totalScore += standardFrame->pinNums[i];
    }
    
    return totalScore;
}

static IFrameStruct _vTable = { addPins, score };

IFrame Frame_Create(void)
{
    StandardFrameStruct* frame = (StandardFrameStruct*)calloc(1, sizeof(StandardFrameStruct));
    frame->base = _vTable;
    for (int i = 0; i < BALL_MAX; i++)
    {
        frame->pinNums[i] = 0;
    }
    
    frame->ballCount = 0;
    return (IFrame)frame;
}

