#include <stdbool.h>
#include <stdio.h>
#include "bowling.h"

#define FRAME_NUM (10)
#define PINS_IN_FRAME (10)
#define NORMAL_FRAME_NUM (FRAME_NUM - 1)
#define IDX_OF_LAST_FRAME (FRAME_NUM - 1)
#define ROLL_IN_LAST_FRAME (3)
#define ROLL_IN_NORMAL_FRAME (2)

static int _pinNumTable[NORMAL_FRAME_NUM][ROLL_IN_NORMAL_FRAME]; // 通常フレーム
static int _pinNumTableOfLast[ROLL_IN_LAST_FRAME];               // 最終フレーム
static int _countOfFinishedFrame = 0;
static int _countOfRollInFrame = 0;

static void updateGameProgress();
static void goNextFrame();

static bool isStrikeAt(int frameIdx);
static bool isSpareAt(int frameIdx);

static bool IsNormalFrameFinished();
static bool isLastFrameFinished();

static int scoreFrame(int frameIdx);
static int scoreNormalFrame(int frameIdx);
static int scoreLastFrame();
static int calcStrikeBonusOfNormalFrame(int frameIdx);

static int getPinNumOf(int frameIdx, int rollIdx);
static void recordPinNum(int pinNum);


static bool isLastFrame(int frameIdx);

void Game_Init(void)
{
    _countOfFinishedFrame = 0;
    _countOfRollInFrame = 0;
    
    for (int frameIdx = 0; frameIdx < NORMAL_FRAME_NUM; frameIdx++)
    {
        for (int rollIdx = 0; rollIdx < ROLL_IN_NORMAL_FRAME; rollIdx++)
        {
            _pinNumTable[frameIdx][rollIdx] = 0;
        }
    }

    for (int i = 0; i < ROLL_IN_LAST_FRAME; i++)
    {
        _pinNumTableOfLast[i] = 0;
    }
}

void Game_Roll(int pinNum)
{
    recordPinNum(pinNum);
    updateGameProgress();
}

int Game_Score(void)
{
    int totalScore = 0;
    for (int frameIdx = 0; frameIdx < FRAME_NUM; frameIdx++)
    {
        totalScore += scoreFrame(frameIdx);
    }

    return totalScore;
}

static bool isCurrentFrameFinished()
{
    if (isLastFrame(_countOfFinishedFrame))
    {
        return isLastFrameFinished();
    }
    else
    {
        return IsNormalFrameFinished();
    }
}

static void updateGameProgress()
{
    _countOfRollInFrame++;

    if (isCurrentFrameFinished())
    {
        goNextFrame();
    }
}

static bool isLastFrameFinished()
{
    if (!isLastFrame(_countOfFinishedFrame)) return false;
    if (isStrikeAt(IDX_OF_LAST_FRAME) || isSpareAt(IDX_OF_LAST_FRAME))
        return _countOfRollInFrame == 3;
    
    return _countOfFinishedFrame == 2;
}

static bool IsNormalFrameFinished()
{
    return isStrikeAt(_countOfFinishedFrame) || _countOfRollInFrame == 2;
}

static void goNextFrame()
{
    _countOfFinishedFrame++;
    _countOfRollInFrame = 0;
}

/// @brief フレーム/インデックスを抽象化した、ピン数へのアクセサ
static int getPinNumOf(int frameIdx, int rollIdx)
{
    if (isLastFrame(frameIdx))
        return _pinNumTableOfLast[rollIdx];
    return _pinNumTable[frameIdx][rollIdx];
}

static void recordPinNum(int pinNum)
{
    int frameIdx = _countOfFinishedFrame;
    int rollIdx = _countOfRollInFrame;

    if (isLastFrame(frameIdx))
    {
        _pinNumTableOfLast[rollIdx] = pinNum;
    }
    else
    {
        _pinNumTable[frameIdx][rollIdx] = pinNum;
    }
}

static bool isLastFrame(int frameIdx)
{
    int frameCount = frameIdx + 1;
    return frameCount == FRAME_NUM;
}

static bool isStrikeAt(int frameIdx)
{
    return getPinNumOf(frameIdx, 0) == PINS_IN_FRAME;
}

static bool isSpareAt(int frameIdx)
{
    if (isStrikeAt(frameIdx))
        return false;

    return getPinNumOf(frameIdx, 0) + getPinNumOf(frameIdx, 1) == PINS_IN_FRAME;
}

static int scoreFrame(int frameIdx)
{
    if (isLastFrame(frameIdx))
        return scoreLastFrame();

    return scoreNormalFrame(frameIdx);
}

static int calcStrikeBonusOfNormalFrame(int frameIdx)
{
    int nextFrameIdx = frameIdx + 1;
    if (isStrikeAt(nextFrameIdx))
    {
        // 次フレームがStrikeの場合、更に次からボーナス用のピン数を取得する必要がある
        return _pinNumTable[frameIdx + 1][0] + _pinNumTable[frameIdx + 2][0];
    }
    else
    {
        return _pinNumTable[frameIdx + 1][0] + _pinNumTable[frameIdx + 1][1];
    }
}

static int scoreNormalFrame(int frameIdx)
{
    int normalScore = _pinNumTable[frameIdx][0] + _pinNumTable[frameIdx][1];

    if (isStrikeAt(frameIdx))
    {
        return normalScore + calcStrikeBonusOfNormalFrame(frameIdx);
    }
    else if (isSpareAt(frameIdx))
    {
        int spareBonus = _pinNumTable[frameIdx + 1][0];
        return normalScore + spareBonus;
    }

    return normalScore;
}

static int scoreLastFrame()
{
    int sumOfPins = 0;
    for (int i = 0; i < ROLL_IN_LAST_FRAME; i++)
    {
        sumOfPins += _pinNumTableOfLast[i];
    }
    return sumOfPins;
}
