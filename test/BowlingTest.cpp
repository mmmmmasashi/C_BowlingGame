#include "CppUTest/CommandLineTestRunner.h"
#include "Bowling.h"

TEST_GROUP(SampleTestGroup){};

TEST(SampleTestGroup, FailTest)
{
    FAIL("Fail Test");
}
