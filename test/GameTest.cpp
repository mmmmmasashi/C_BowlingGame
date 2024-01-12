#include "CppUTest/CommandLineTestRunner.h"
#include "Game.h"

TEST_GROUP(GameTestGroup){
    
    Game* game;
    
    void setup(void)
    {
        game = Game_Create();
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

TEST(GameTestGroup, CanGetCurrentFrameNumber)
{
    CHECK_EQUAL(1, Game_GetCurrentFrame(game));

    Game_Roll(game, 1);
    Game_Roll(game, 2);

    CHECK_EQUAL(2, Game_GetCurrentFrame(game));

}
