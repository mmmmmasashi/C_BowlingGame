#include "Bowling.h"
#include "StandardFrame.h"

#include <stdlib.h>

#define FRAME_NUM (10)
#define FRAME_NUM_FIRST (1)
#define FRAME_NUM_LAST (10)

typedef struct GameStruct {
    IFrame frames[FRAME_NUM];
    int frameIdx;
} GameStruct;

static IFrame getCurrentFrame(Game game);

Game Game_Create(void)
{
    Game game = (Game)malloc(sizeof(GameStruct));
    game->frameIdx = 0;

    IFrame nextFrame = StandardFrame_Create_TmpLast();
    game->frames[FRAME_NUM - 1] = nextFrame;

    /* nextFrameへのポインタを渡すために、後ろから初期化していく*/
    for (int frameIdx = FRAME_NUM - 2; frameIdx >= 0; frameIdx--)
    {
        game->frames[frameIdx] = StandardFrame_Create(nextFrame);
        nextFrame = game->frames[frameIdx];
    }
    
    return game;
}

void Game_Roll(Game self,int pinsNum)
{
    IFrame currentFrame = getCurrentFrame(self);
    currentFrame->AddPins(currentFrame, pinsNum);

    if (currentFrame->IsFilled(currentFrame))
    {
        self->frameIdx++;
    }
}

int Game_Score(Game self)
{
    int totalScore = 0;
    for (int i = 0; i < FRAME_NUM; i++)
    {
        IFrame frame = self->frames[i];
        totalScore += frame->Score(frame);
    }
    
    return totalScore;
}

void Game_Destroy(Game self)
{
    for (int i = 0; i < FRAME_NUM; i++)
    {
        IFrame each = self->frames[i];
        each->Destroy(each);
    }
    
    free(self);
}

static IFrame getCurrentFrame(Game game)
{
    return game->frames[game->frameIdx];
}
