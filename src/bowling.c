#include "Bowling.h"
#include "Frame.h"

#include <stdlib.h>

#define FRAME_NUM (10)

typedef struct GameStruct {
    IFrame frames[FRAME_NUM];
    int frameIdx;
} GameStruct;

static IFrame getCurrentFrame(Game game);

Game Game_Create(void)
{
    Game game = (Game)malloc(sizeof(GameStruct));
    game->frameIdx = 0;
    for (int i = 0; i < FRAME_NUM; i++)
    {
        game->frames[i] = Frame_Create();
    }
    
    return game;
}

void Game_Roll(Game self,int pinsNum)
{
    IFrame currentFrame = getCurrentFrame(self);
    bool success = currentFrame->AddPins(currentFrame, pinsNum);

    if (success) return;
    self->frameIdx++;
    IFrame nextFrame = getCurrentFrame(self);
    nextFrame->AddPins(nextFrame, pinsNum);
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
