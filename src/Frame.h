#ifndef FRAME_H
#define FRAME_H

//TODO:変更
enum { FRAME_ROLL_MAX = 100 };
typedef struct {
    int _pinNums[FRAME_ROLL_MAX];
    int _ballCount;
} Frame;

Frame* Frame_Create(void);
void Frame_AddPin(Frame* frame, int pinNum);
int Frame_Score(Frame* frame);

#endif /* FRAME_H */