#include "CppUTest/CommandLineTestRunner.h"
#include "Bowling.h"

TEST_GROUP(BowlingGameTestGroup){
    Game game;
    void setup(void)
    {
        game = Game_Create();
    }

    void teardown(void)
    {
        Game_Destroy(game);
    }

    void RollMany(int pinNum, int times)
    {
        for (int i = 0; i < times; i++)
        {
            Game_Roll(game, pinNum);
        }
    }
};

TEST(BowlingGameTestGroup, AllGutter)
{
    RollMany(0, 2 * 10);
    CHECK_EQUAL(0, Game_Score(game));
}

TEST(BowlingGameTestGroup, NoMark)
{
    Game_Roll(game, 2);
    Game_Roll(game, 3);

    RollMany(0, 2 * 9);

    CHECK_EQUAL(5, Game_Score(game));
}