#ifndef Game_H
#define Game_H

#include "Frame.h"

enum { FRAME_NUM = 10 };
typedef struct{
    Frame* _frames[FRAME_NUM];
} Game;

Game* Game_Create(void);
void Game_Destroy(Game* game);
void Game_Roll(Game* game, int pinNum);
int Game_Score(Game* game);

#endif /* Game_H */