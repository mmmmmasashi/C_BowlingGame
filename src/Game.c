#include "stddef.h"
#include "Game.h"

static Frame* getCurrentFrame(const Game* game);
static int scoreOfFrame(const Game* game, int frameIdx);
static void addRollToCurrentFrame(Game* game, int pinNum);
static void stepFramePositionIfFull(Game* game);

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
    addRollToCurrentFrame(game, pinNum);
    stepFramePositionIfFull(game);
}

int Game_Score(const Game* game)
{
    int totalScore = 0;

    for (int i = 0; i < FRAME_NUM; i++)
    {
        totalScore += scoreOfFrame(game, i);
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

static int scoreOfFrame(const Game* game, int frameIdx)
{
    Frame* frame = game->_frames[frameIdx];
    return Frame_Score(frame);
}

static void addRollToCurrentFrame(Game* game, int pinNum)
{
    Frame* frameCurrent = getCurrentFrame(game);
    Frame_AddRoll(frameCurrent, pinNum);
}

static void stepFramePositionIfFull(Game* game)
{
    Frame* frameCurrent = getCurrentFrame(game);
    if (Frame_IsFull(frameCurrent))
    {
        game->_currentFrameIdx++;
    }
}
