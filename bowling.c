#include <stdbool.h>
#include <stdio.h>
#include "bowling.h"

#define FRAME_NUM (10)
#define PINS_IN_FRAME (10)
#define NORMAL_FRAME_NUM (FRAME_NUM - 1)
#define ROLL_IN_LAST_FRAME (3)
#define ROLL_IN_NORMAL_FRAME (2)

static int _pinNumTable[NORMAL_FRAME_NUM][ROLL_IN_NORMAL_FRAME]; // 通常フレーム
static int _pinNumTableOfLast[ROLL_IN_LAST_FRAME];               // 最終フレーム
static int _countOfFinishedFrame = 0;
static int _countOfRollInFrame = 0;

static bool IsStrikeAt(int frameIdx);
static bool IsSpareAt(int frameIdx);

static bool IsLastFrameFinished();

static int ScoreOfFrame(int frameIdx);
static int ScoreOfNormalFrame(int frameIdx);
static int ScoreOfLastFrame();

static int GetPinNumOf(int frameIdx, int rollIdx);
static void SetPinNum(int pinNum);

static void UpdateRollStatus();
static void GoNextFrame();
static bool IsLastFrame(int frameIdx);

void Game_Init(void)
{
    _countOfFinishedFrame = 0;
    _countOfRollInFrame = 0;
    for (int i = 0; i < NORMAL_FRAME_NUM; i++)
    {
        _pinNumTable[i][0] = 0;
        _pinNumTable[i][1] = 0;
    }

    for (int i = 0; i < ROLL_IN_LAST_FRAME; i++)
    {
        _pinNumTableOfLast[i] = 0;
    }
}

void Game_Roll(int pinNum)
{
    SetPinNum(pinNum);
    UpdateRollStatus();
}

static void UpdateRollStatus()
{
    _countOfRollInFrame++;

    bool isFrameFinished = false;

    if (IsLastFrame(_countOfFinishedFrame))
    {
        isFrameFinished = IsLastFrameFinished();
    }
    else
    {
        isFrameFinished = IsStrikeAt(_countOfFinishedFrame) || _countOfRollInFrame == 2;
    }

    if (isFrameFinished)
    {
        GoNextFrame();
    }
}

static bool IsLastFrameFinished()
{
    bool isMarkAndThreeRolls = _countOfRollInFrame == 3;
    bool isStrike = _pinNumTableOfLast[0] == PINS_IN_FRAME;
    bool isSpare = !isStrike && (_pinNumTableOfLast[0] + _pinNumTableOfLast[1] == PINS_IN_FRAME);
    bool isNoMarkFinish = !isSpare && isSpare && _countOfRollInFrame >= 2;

    return isMarkAndThreeRolls || isNoMarkFinish;
}

static void GoNextFrame()
{
    _countOfFinishedFrame++;
    _countOfRollInFrame = 0;
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

/// @brief フレーム/インデックスを抽象化した、ピン数へのアクセサ
static int GetPinNumOf(int frameIdx, int rollIdx)
{
    if (IsLastFrame(frameIdx))
        return _pinNumTableOfLast[rollIdx];
    return _pinNumTable[frameIdx][rollIdx];
}

static void SetPinNum(int pinNum)
{
    int frameIdx = _countOfFinishedFrame;
    int rollIdx = _countOfRollInFrame;
    if (IsLastFrame(frameIdx))
    {
        _pinNumTableOfLast[rollIdx] = pinNum;
    }
    else
    {
        _pinNumTable[frameIdx][rollIdx] = pinNum;
    }
}

static bool IsLastFrame(int frameIdx)
{
    int frameCount = frameIdx + 1;
    return frameCount == FRAME_NUM;
}

static bool IsStrikeAt(int frameIdx)
{
    return GetPinNumOf(frameIdx, 0) == PINS_IN_FRAME;
}

static bool IsSpareAt(int frameIdx)
{
    if (IsStrikeAt(frameIdx))
        return false;

    return GetPinNumOf(frameIdx, 0) + GetPinNumOf(frameIdx, 1) == PINS_IN_FRAME;
}

static int ScoreOfFrame(int frameIdx)
{
    if (IsLastFrame(frameIdx))
        return ScoreOfLastFrame();

    return ScoreOfNormalFrame(frameIdx);
}

static int ScoreOfNormalFrame(int frameIdx)
{
    int normalScore = _pinNumTable[frameIdx][0] + _pinNumTable[frameIdx][1];
    int bonusScore = 0;

    if (IsStrikeAt(frameIdx))
    {
        int nextFrameIdx = frameIdx + 1;
        if (IsStrikeAt(nextFrameIdx))
        {
            // 次フレームがStrikeの場合、更に次からボーナス用のピン数を取得する必要がある
            bonusScore = _pinNumTable[frameIdx + 1][0] + _pinNumTable[frameIdx + 2][0];
        }
        else
        {
            bonusScore = _pinNumTable[frameIdx + 1][0] + _pinNumTable[frameIdx + 1][1];
        }
    }

    else if (IsSpareAt(frameIdx))
    {
        bonusScore = _pinNumTable[frameIdx + 1][0];
    }
    return normalScore + bonusScore;
}

static int ScoreOfLastFrame()
{
    int sumOfPins = 0;
    for (int i = 0; i < ROLL_IN_LAST_FRAME; i++)
    {
        sumOfPins += _pinNumTableOfLast[i];
    }
    return sumOfPins;
}
