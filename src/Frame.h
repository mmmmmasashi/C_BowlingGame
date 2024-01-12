#ifndef FRAME_H
#define FRAME_H

#include <stdbool.h>

//TODO:変更
enum { FRAME_ROLL_MAX = 2 };
typedef struct {
    int _pinNums[FRAME_ROLL_MAX];
    int _ballCount;
} Frame;

Frame* Frame_Create(void);
void Frame_Destroy(Frame* frame);
void Frame_AddRoll(Frame* frame, int pinNum);
int Frame_Score(const Frame* frame);
bool Frame_IsFull(const Frame* frame);

#endif /* FRAME_H */