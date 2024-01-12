#include "CppUTest/CommandLineTestRunner.h"
#include "Game.h"

TEST_GROUP(GameTestGroup){};

TEST(GameTestGroup, AllGutter)
{
    Game* game = Game_Create();

    for (int i = 0; i < 20; i++)
    {
        Game_Roll(game, 0);
    }
    
    CHECK_EQUAL(0, Game_Score(game));
}
