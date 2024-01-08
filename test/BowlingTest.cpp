#include "CppUTest/CommandLineTestRunner.h"
#include "Bowling.h"

TEST_GROUP(BowlingGameTestGroup){};

TEST(BowlingGameTestGroup, AllGutter)
{
    Game game = Game_Create();
    for (int i = 0; i < 2 * 10; i++)
    {
        Game_Roll(game, 0);
    }

    CHECK_EQUAL(0, Game_Score(game));

    Game_Destroy(game);
    
}
