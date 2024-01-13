#ifndef STANDARD_FRAME_H
#define STANDARD_FRAME_H

#include "Frame.h"

typedef struct StandardFrameStruct StandardFrame;

Frame* StandardFrame_Create(Frame* nextFrame);

#endif /* STANDARD_FRAME_H */