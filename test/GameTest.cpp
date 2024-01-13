#include "CppUTest/CommandLineTestRunner.h"
#include "Game.h"
#include "GameFactory.h"

TEST_GROUP(GameTestGroup){
    
    Game* game;
    
    void setup(void)
    {
        game = GameFactory_Create();
    }

    void teardown(void)
    {
        Game_Destroy(game);
        game = NULL;
    }

    void RollManyTimes(int pinNum, int times)
    {
        for (int i = 0; i < times; i++)
        {
            Game_Roll(game, pinNum);
        }
    }
};

TEST(GameTestGroup, AllGutter)
{
    RollManyTimes(0, 20);
    CHECK_EQUAL(0, Game_Score(game));
}

TEST(GameTestGroup, NoMark)
{
    Game_Roll(game, 1);
    Game_Roll(game, 2);

    RollManyTimes(0, 2 * 9);
    
    CHECK_EQUAL(3, Game_Score(game));
}

TEST(GameTestGroup, NoMark_2Frames)
{
    Game_Roll(game, 1);
    Game_Roll(game, 2);

    Game_Roll(game, 3);
    Game_Roll(game, 4);

    RollManyTimes(0, 2 * 8);
    
    CHECK_EQUAL(3 + 7, Game_Score(game));
}

TEST(GameTestGroup, Spare)
{
    Game_Roll(game, 1);
    Game_Roll(game, 9);

    Game_Roll(game, 2);
    Game_Roll(game, 3);

    RollManyTimes(0, 2 * 8);
    
    CHECK_EQUAL(12 + 5, Game_Score(game));
}

TEST(GameTestGroup, SpareAnotherCase)
{
    Game_Roll(game, 1);
    Game_Roll(game, 9);

    Game_Roll(game, 3);
    Game_Roll(game, 0);

    RollManyTimes(0, 2 * 8);
    
    CHECK_EQUAL(13 + 3, Game_Score(game));
}

TEST(GameTestGroup, Strike)
{
    Game_Roll(game, 10);

    Game_Roll(game, 1);
    Game_Roll(game, 2);

    RollManyTimes(0, 2 * 8);
    
    CHECK_EQUAL(13 + 3, Game_Score(game));
}

TEST(GameTestGroup, CanRollThreeTimesInLastFrame)
{
    RollManyTimes(0, 2 * 9);

    Game_Roll(game, 1);
    Game_Roll(game, 9);
    Game_Roll(game, 2);

    CHECK_EQUAL(12, Game_Score(game));
}

IGNORE_TEST(GameTestGroup, PerfectGame)
{
    RollManyTimes(10, 12);
    CHECK_EQUAL(300, Game_Score(game));
}

TEST(GameTestGroup, CanGetCurrentFrameNumber)
{
    CHECK_EQUAL(1, Game_GetCurrentFrameNumber(game));

    Game_Roll(game, 1);
    Game_Roll(game, 2);

    CHECK_EQUAL(2, Game_GetCurrentFrameNumber(game));
}
