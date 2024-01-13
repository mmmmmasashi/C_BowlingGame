#include "GameFactory.h"
#include "StandardFrame.h"
#include "FinalFrame.h"

static void initGame(Game* game);

Game* GameFactory_Create(void)
{
    Game* game = (Game*)malloc(sizeof(Game));
    initGame(game);
    return game;
}

static void initGame(Game* game)
{
    //次フレームへの参照を持たせるために、最終フレームから1フレームまでの
    //逆順で生成する

    int frameIdx = FRAME_NUM - 1;//最終フレーム
    game->_frames[frameIdx] = FinalFrame_Create();
    frameIdx--;

    for (; frameIdx >= 0; frameIdx--)
    {
        Frame* nextFrame = game->_frames[frameIdx + 1];
        game->_frames[frameIdx] = StandardFrame_Create(nextFrame);
    }
    game->_currentFrameIdx = 0;
}
