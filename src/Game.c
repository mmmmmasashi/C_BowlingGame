#include "Game.h"

#include "Frame.h"
typedef struct {
    Frame _frames[10];
    int _currentIdx;
} Game;

Game _game;

void Game_Init()
{
    //TODO
    _game._currentIdx = 0;
    
    for (int i = 0; i < FRAME_NUM; i++)
    {
        Frame* currentFrame = getCurrentFrame();
        Frame_Init(currentFrame);
    }
    
    //次のフレームへのポインタを渡す or 初期化時に作る

    InitFrames();
}

void Game_Roll(int pinNum)
{
    Frame* currentFrame = getCurrentFrame();

    Frame_AddPins(currentFrame, pinNum);

    if (Frame_IsFull(currentFrame))
    {
        goNextFrame();
    }
    else
    {
        _game._currentIdx++;
    }
}

int Game_Score()
{
    int gameScore = 0;
    for (int i = 0; i < FRAME_NUM; i++)
    {
        Frame* currentFrame = getCurrentFrame();
        gameScore += Frame_Score(currentFrame);
    }
    return gameScore;
}