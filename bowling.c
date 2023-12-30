#include <stdbool.h>
#include <stdio.h>
#include "bowling.h"

#define FRAME_NUM (10)
#define PINS_IN_FRAME (10)

static int _pinNumTable[FRAME_NUM][2];
static int _countOfFinishedFrame = 0;
static int _countOfRollInFrame = 0;

static int ScoreOfFrame(int frameIdx);

void Game_Init(void)
{
    _countOfFinishedFrame = 0;
    _countOfRollInFrame = 0;
    for (int i = 0; i < 10; i++)
    {
        _pinNumTable[i][0] = 0;
        _pinNumTable[i][1] = 0;
    }
}

void Game_Roll(int pinNum)
{
    _pinNumTable[_countOfFinishedFrame][_countOfRollInFrame] = pinNum;
    _countOfRollInFrame++;

    bool isStrike = (_countOfRollInFrame == 1) && (pinNum == PINS_IN_FRAME);
    bool isFrameFinished = isStrike || _countOfRollInFrame == 2;

    if (isFrameFinished)
    {
        _countOfFinishedFrame++;
        _countOfRollInFrame = 0;
    }
}

int Game_Score(void)
{
    int totalScore = 0;
    for (int frameIdx = 0; frameIdx < FRAME_NUM; frameIdx++)
    {
        totalScore += ScoreOfFrame(frameIdx);
    }

    return totalScore;
}

static int ScoreOfFrame(int frameIdx)
{
    int normalScore = _pinNumTable[frameIdx][0] + _pinNumTable[frameIdx][1];

    bool isStrike = _pinNumTable[frameIdx][0] == PINS_IN_FRAME;
    bool isSpare = !isStrike && normalScore == PINS_IN_FRAME;

    if (isStrike)
    {
        int bonusScore = _pinNumTable[frameIdx + 1][0] + _pinNumTable[frameIdx + 1][1];
        return normalScore + bonusScore;
    }
    else if (isSpare)
    {
        int bonusScore = _pinNumTable[frameIdx + 1][0];
        return normalScore + bonusScore;
    }
    else
    {
        return normalScore;
    }
}
