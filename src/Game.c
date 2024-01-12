#include "stddef.h"
#include "Game.h"

static Frame* getCurrentFrame(const Game* game);

Game* Game_Create(void)
{
    Game* game = (Game*)malloc(sizeof(Game));
    for (int i = 0; i < FRAME_NUM; i++)
    {
        game->_frames[i] = Frame_Create();
    }
    game->_currentFrameIdx = 0;

    return game;
}

void Game_Destroy(Game* game)
{
    for (int i = 0; i < FRAME_NUM; i++)
    {
        Frame_Destroy(game->_frames[i]);
        game->_frames[i] = NULL;
    }
    
    free(game);
}

void Game_Roll(Game* game, int pinNum)
{
    Frame* frameCurrent = getCurrentFrame(game);
    Frame_AddPin(frameCurrent, pinNum);
    
    //更新
    if (Frame_IsFull(frameCurrent))
    {
        game->_currentFrameIdx++;
    }
}

int Game_Score(const Game* game)
{
    int totalScore = 0;
    for (int i = 0; i < FRAME_NUM; i++)
    {
        Frame* frame = game->_frames[i];
        totalScore += Frame_Score(frame);
    }
    
    return totalScore;
}

int Game_GetCurrentFrameNumber(const Game* game)
{
    return game->_currentFrameIdx + 1;
}

static Frame* getCurrentFrame(const Game* game)
{
    return game->_frames[game->_currentFrameIdx];
}