#include "Bowling.h"
#include <stdlib.h>

typedef struct GameStruct {

} GameStruct;

Game Game_Create(void)
{
    Game game = (Game)malloc(sizeof(GameStruct));
    return game;
}

void Game_Roll(Game self,int pinsNum)
{

}

int Game_Score(Game self)
{
    return -1;
}

void Game_Destroy(Game self)
{
    free(self);
}
