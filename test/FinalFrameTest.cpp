#include "CppUTest/CommandLineTestRunner.h"
#include "FinalFrame.h"

TEST_GROUP(FinalFrameTestGroup){
};

TEST(FinalFrameTestGroup, NoMark_IsFull)
{
    Frame* frame = FinalFrame_Create();
    Frame_AddRoll(frame, 0);
    Frame_AddRoll(frame, 0);
    CHECK_TRUE(Frame_IsFull(frame));
    Frame_Destroy(frame);
}
