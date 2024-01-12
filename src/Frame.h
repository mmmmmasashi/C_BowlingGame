#ifndef FRAME_H
#define FRAME_H

#include <stdbool.h>

enum { FRAME_ROLL_MAX = 2 };

/* 参考:前方宣言する理由
  typedef struct { ...} Frame;とすると、
 _nextFrameで再帰的に記載する際に、エラーになるため */
typedef struct Frame Frame;

typedef struct {
    void (*TellNextFrame)(Frame* frame, Frame* nextFrame);
    void (*Destroy)(Frame* frame);
    void (*AddRoll)(Frame* frame, int pinNum);
    int (*Score)(const Frame* frame);
    bool (*IsFull)(const Frame* frame);
} FrameInterface;

//TODO:中身どうなる？Ifだけ？
struct Frame{
    FrameInterface* _funcTable;
    int _pinNums[FRAME_ROLL_MAX];
    int _ballCount;
    Frame* _nextFrame;
};

void Frame_TellNextFrame(Frame* frame, Frame* nextFrame);
void Frame_Destroy(Frame* frame);
void Frame_AddRoll(Frame* frame, int pinNum);
int Frame_Score(const Frame* frame);
bool Frame_IsFull(const Frame* frame);

#endif /* FRAME_H */