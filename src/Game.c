#include "stddef.h"
#include "Game.h"
#include "StandardFrame.h"

static void initGame(Game* game);
static void destroyFrames(Game* game);
static Frame* getCurrentFrame(const Game* game);
static int scoreOfFrameAt(const Game* game, int frameIdx);
static void addRollToCurrentFrame(Game* game, int pinNum);
static void goNextFrameIfIsFull(Game* game);

Game* Game_Create(void)
{
    Game* game = (Game*)malloc(sizeof(Game));
    initGame(game);
    return game;
}

void Game_Destroy(Game* game)
{
    destroyFrames(game);    
    free(game);
}

void Game_Roll(Game* game, int pinNum)
{
    addRollToCurrentFrame(game, pinNum);
    goNextFrameIfIsFull(game);
}

int Game_Score(const Game* game)
{
    int totalScore = 0;

    for (int i = 0; i < FRAME_NUM; i++)
    {
        totalScore += scoreOfFrameAt(game, i);
    }
    
    return totalScore;
}

int Game_GetCurrentFrameNumber(const Game* game)
{
    return game->_currentFrameIdx + 1;
}

static void initGame(Game* game)
{
    for (int i = 0; i < FRAME_NUM; i++)
    {
        game->_frames[i] = StandardFrame_Create();
    }

    for (int i = 0; i < FRAME_NUM - 1; i++)
    {
        Frame_TellNextFrame(game->_frames[i], game->_frames[i + 1]);
    }

    game->_currentFrameIdx = 0;
}

static void destroyFrames(Game* game)
{
    for (int i = 0; i < FRAME_NUM; i++)
    {
        Frame_Destroy(game->_frames[i]);
        game->_frames[i] = NULL;
    }
}

static Frame* getCurrentFrame(const Game* game)
{
    return game->_frames[game->_currentFrameIdx];
}

static int scoreOfFrameAt(const Game* game, int frameIdx)
{
    Frame* frame = game->_frames[frameIdx];
    return Frame_Score(frame);
}

static void addRollToCurrentFrame(Game* game, int pinNum)
{
    Frame* frameCurrent = getCurrentFrame(game);
    Frame_AddRoll(frameCurrent, pinNum);
}

static void goNextFrameIfIsFull(Game* game)
{
    Frame* frameCurrent = getCurrentFrame(game);
    if (Frame_IsFull(frameCurrent))
    {
        game->_currentFrameIdx++;
    }
}
