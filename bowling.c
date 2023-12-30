#include <stdbool.h>
#include "bowling.h"

#define MAX_FRAME (10)

static int _pinNumTable[MAX_FRAME][2];
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

    bool isFrameFinished = _countOfRollInFrame == 2;
    if (isFrameFinished)
    {
        _countOfFinishedFrame++;
        _countOfRollInFrame = 0;
    }
}

int Game_Score(void)
{
    int totalScore = 0;
    for (int i = 0; i < MAX_FRAME; i++)
    {
        totalScore += ScoreOfFrame(i);
    }

    return totalScore;
}

static int ScoreOfFrame(int frameIdx)
{
    int normalScore = _pinNumTable[frameIdx][0] + _pinNumTable[frameIdx][1];

    bool isSpare = normalScore == 10;
    if (isSpare)
    {
        int bonusScore = _pinNumTable[frameIdx + 1][0];
        return normalScore + bonusScore;
    }
    else
    {
        return normalScore;
    }
}
