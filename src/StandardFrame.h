#ifndef STANDARD_FRAME_H
#define STANDARD_FRAME_H

#include "Frame.h"

typedef struct StandardFrameStruct StandardFrame;

Frame* StandardFrame_Create(void);
void StandardFrame_TellNextFrame(StandardFrame* frame, Frame* nextFrame);

#endif /* STANDARD_FRAME_H */