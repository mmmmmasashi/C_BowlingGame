#include "bowling.h"

static int score = 0;

void Game_Init(void)
{
    score = 0;
}

void Game_Roll(int pinNum)
{
    score += pinNum;
}

int Game_Score(void)
{
    return score;
}
