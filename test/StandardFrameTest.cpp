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
    frame->AddPins(frame, 2);
    frame->AddPins(frame, 3);
    CHECK_EQUAL(5, frame->Score(frame));
}

TEST(FrameTestGroup, OverRoll)
{
    frame->AddPins(frame, 0);
    CHECK_FALSE(frame->IsFilled(frame));

    frame->AddPins(frame, 0);
    CHECK_TRUE(frame->IsFilled(frame));
}

// IGNORE_TEST(FrameTestGroup, Spare)
// {
//     frame->AddPins(frame, 1);
//     frame->AddPins(frame, 9);
//     IFrame nextFrame = StandardFrame_Create();
//     nextFrame->Destroy(nextFrame);
// }