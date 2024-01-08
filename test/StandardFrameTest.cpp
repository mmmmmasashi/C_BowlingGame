#include "CppUTest/CommandLineTestRunner.h"
#include "StandardFrame.h"

TEST_GROUP(FrameTestGroup)
{
    IFrame frame;
    void setup(void)
    {
        frame = StandardFrame_Create();
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
    frame->AddPins(frame, 0);
    frame->AddPins(frame, 0);
    
    CHECK_FALSE(frame->AddPins(frame, 0));
}