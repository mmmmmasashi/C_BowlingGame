#ifndef Game_H
#define Game_H

#include "Frame.h"

typedef struct{
    Frame* _frames[10];
} Game;

Game* Game_Create(void);
void Game_Roll(Game* game, int pinNum);
int Game_Score(Game* game);

#endif /* Game_H */