#include "CppUTest/CommandLineTestRunner.h"
#include "bowling.h"

TEST_GROUP(BowlingGameTestGroup){
    void RollMany(int pins, int n){
        for (int i = 0; i < n; i++){
            Game_Roll(pins);
}
}
}
;

TEST(BowlingGameTestGroup, TestAllGutter)
{
    Game_Init();
    RollMany(0, 20);
    CHECK_EQUAL(0, Game_Score());
}

TEST(BowlingGameTestGroup, TestNoMark)
{
    Game_Init();

    Game_Roll(2);
    Game_Roll(3);
    RollMany(0, 18);
    CHECK_EQUAL(5, Game_Score());
}

TEST(BowlingGameTestGroup, TestSpare)
{
    Game_Init();

    Game_Roll(2);
    Game_Roll(8);

    Game_Roll(1);
    Game_Roll(2);

    RollMany(0, 16);
    CHECK_EQUAL(11 + 3, Game_Score());
}

TEST(BowlingGameTestGroup, TestStrike)
{
    Game_Init();

    Game_Roll(10);

    Game_Roll(1);
    Game_Roll(2);

    RollMany(0, 2 * 8);
    CHECK_EQUAL(13 + 3, Game_Score());
}

TEST(BowlingGameTestGroup, TestPerfectGame)
{
    Game_Init();

    RollMany(10, 12); // 1 * 9 + 3
    CHECK_EQUAL(300, Game_Score());
}

TEST(BowlingGameTestGroup, TestLastFrameSpareCase)
{
    Game_Init();

    RollMany(0, 2 * 9);
    Game_Roll(1);
    Game_Roll(9);
    Game_Roll(3);

    CHECK_EQUAL(13, Game_Score());
}

int main(int ac, char **av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}