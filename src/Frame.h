#ifndef FRAME_H
#define FRAME_H

#include <stdbool.h>

typedef struct Frame Frame;

typedef struct {
    /* TODO: TellNextだけはStandard専用では？ここにいるのは不適切*/
    void (*TellNextFrame)(Frame* frame, Frame* nextFrame);
    void (*Destroy)(Frame* frame);
    void (*AddRoll)(Frame* frame, int pinNum);
    int (*Score)(const Frame* frame);
    bool (*IsFull)(const Frame* frame);
    int (*BonusForSpare)(const Frame* frame);
    int (*BonusForStrike)(const Frame* frame);
} FrameInterface;

struct Frame{
    FrameInterface* _funcTable;
};

void Frame_TellNextFrame(Frame* frame, Frame* nextFrame);
void Frame_Destroy(Frame* frame);
void Frame_AddRoll(Frame* frame, int pinNum);
int Frame_Score(const Frame* frame);
bool Frame_IsFull(const Frame* frame);
int Frame_BonusForSpare(const Frame* frame);
int Frame_BonusForStrike(const Frame* frame);

#endif /* FRAME_H */