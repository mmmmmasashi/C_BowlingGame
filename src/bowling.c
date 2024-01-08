#include "Bowling.h"
#include "Frame.h"

#include <stdlib.h>

typedef struct GameStruct {
    IFrame frames[10];
    int frameIdx;
} GameStruct;

Game Game_Create(void)
{
    Game game = (Game)malloc(sizeof(GameStruct));
    game->frameIdx = 0;
    for (int i = 0; i < 10; i++)
    {
        game->frames[i] = Frame_Create();
    }
    
    return game;
}

void Game_Roll(Game self,int pinsNum)
{
    IFrame currentFrame = self->frames[self->frameIdx];
    bool success = currentFrame->AddPins(currentFrame, pinsNum);

    if (success) return;
    self->frameIdx++;
    IFrame nextFrame = self->frames[self->frameIdx];
    nextFrame->AddPins(nextFrame, pinsNum);
}

int Game_Score(Game self)
{
    int totalScore = 0;
    for (int i = 0; i < 10; i++)
    {
        IFrame frame = self->frames[i];
        totalScore += frame->Score(frame);
    }
    
    return totalScore;
}

void Game_Destroy(Game self)
{
    //TODO:
    free(self);
}
