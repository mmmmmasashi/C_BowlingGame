#include "CppUTest/CommandLineTestRunner.h"
#include "StandardFrame.h"

TEST_GROUP(FrameTestGroup)
{
    IFrame frame;
    void setup(void)
    {
        frame = StandardFrame_Create_TmpLast();
    }

    void teardown(void)
    {
        frame->Destroy(frame);
    }
};

TEST(FrameTestGroup, NoMark)
{
    bool isSuccess1st = frame->AddPins(frame, 2);
    CHECK_TRUE(isSuccess1st);

    bool isSuccess2nd = frame->AddPins(frame, 3);
    CHECK_TRUE(isSuccess2nd);
    CHECK_EQUAL(5, frame->Score(frame));
}

TEST(FrameTestGroup, OverRoll)
{
    CHECK_TRUE(frame->AddPins(frame, 0));
    CHECK_TRUE(frame->AddPins(frame, 0));
    CHECK_FALSE(frame->AddPins(frame, 0));
}

// IGNORE_TEST(FrameTestGroup, Spare)
// {
//     frame->AddPins(frame, 1);
//     frame->AddPins(frame, 9);
//     IFrame nextFrame = StandardFrame_Create();
//     nextFrame->Destroy(nextFrame);
// }