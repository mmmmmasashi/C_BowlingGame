#include "CppUTest/CommandLineTestRunner.h"
#include "bowling.h"

TEST_GROUP(BowlingGameTestGroup){
    void RollMany(int pins, int n){
        for (int i = 0; i < n; i++){
            Game_Roll(pins);
        }
    }
};

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

int main(int ac, char **av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}