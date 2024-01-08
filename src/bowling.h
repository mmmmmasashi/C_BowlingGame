#ifndef BOWLING_H
#define BOWLING_H

typedef struct GameStruct * Game;

Game Game_Create(void);
void Game_Roll(Game,int pinsNum);
int Game_Score(Game);
void Game_Destroy(Game);

#endif /* BOWLING_H */