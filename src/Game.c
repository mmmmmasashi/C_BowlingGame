#include "Game.h"

Game* Game_Create(void)
{
    Game* game = (Game*)malloc(sizeof(Game));
    for (int i = 0; i < FRAME_NUM; i++)
    {
        game->_frames[i] = Frame_Create();
    }
        
    return game;
}

void Game_Roll(Game* game, int pinNum)
{
    Frame* frameCurrent = game->_frames[0];
    Frame_AddPin(frameCurrent, pinNum);
}

int Game_Score(Game* game)
{
    int totalScore = 0;
    for (int i = 0; i < FRAME_NUM; i++)
    {
        Frame* frame = game->_frames[i];
        totalScore += Frame_Score(frame);
    }
    
    return totalScore;
}

