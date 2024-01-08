#include "CppUTest/CommandLineTestRunner.h"
#include "StandardFrame.h"

TEST_GROUP(FrameTestGroup)
{
    IFrame frame;
    IFrame nextFrame;
    void setup(void)
    {
        nextFrame = StandardFrame_Create_TmpLast();
        nextFrame->AddPins(nextFrame, 3);
        frame = StandardFrame_Create(nextFrame);
    }

    void teardown(void)
    {
        nextFrame->Destroy(nextFrame);
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

TEST(FrameTestGroup, Spare)
{
    frame->AddPins(frame, 1);
    frame->AddPins(frame, 9);
    CHECK_EQUAL(13 + 3, frame->Score(frame));
}