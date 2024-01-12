#include "CppUTest/CommandLineTestRunner.h"
#include "Game.h"

TEST_GROUP(GameTestGroup){};

TEST(GameTestGroup, FailTest)
{
    FAIL("Fail Test");
}
