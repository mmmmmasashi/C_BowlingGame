#include "CppUTest/CommandLineTestRunner.h"
#include "Frame.h"

TEST_GROUP(FrameTestGroup)
{

};

TEST(FrameTestGroup, NoMark)
{
    IFrame frame = Frame_Create();
    bool isSuccess1st = frame->AddPins(frame, 2);
    CHECK_TRUE(isSuccess1st);

    bool isSuccess2nd = frame->AddPins(frame, 3);
    CHECK_TRUE(isSuccess2nd);
    CHECK_EQUAL(5, frame->Score(frame));
}

TEST(FrameTestGroup, OverRoll)
{
    IFrame frame = Frame_Create();
    frame->AddPins(frame, 0);
    frame->AddPins(frame, 0);
    
    CHECK_FALSE(frame->AddPins(frame, 0));
}