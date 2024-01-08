#ifndef FRAME_H
#define FRAME_H

#include <stdbool.h>

typedef struct IFrameStruct {
    bool (*AddPins)(IFrameStruct*, int pinNum);
    int (*Score)(IFrameStruct*);
    void (*Destroy)(IFrameStruct*);
} IFrameStruct;

typedef IFrameStruct * IFrame;

#endif /* FRAME_H */