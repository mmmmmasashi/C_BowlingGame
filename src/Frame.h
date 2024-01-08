#ifndef FRAME_H
#define FRAME_H

#include <stdbool.h>

typedef struct IFrameStruct {
    bool (*AddPins)(IFrameStruct*, int pinNum);
    int (*Score)(IFrameStruct*);
} IFrameStruct;

typedef IFrameStruct * IFrame;

IFrame Frame_Create(void);

#endif /* FRAME_H */