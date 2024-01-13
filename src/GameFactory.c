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
    //1-9は通常フレーム作成, 10フレームはFinalFrameを追加
    int i;
    for (i = 0; i < FRAME_NUM - 1; i++)
    {
        game->_frames[i] = StandardFrame_Create();
    }
    game->_frames[i] = FinalFrame_Create();

    //1-9フレームには、次のフレームへの参照を渡す
    for (int i = 0; i < FRAME_NUM - 1; i++)
    {
        StandardFrame_TellNextFrame((StandardFrame*)(game->_frames[i]), game->_frames[i + 1]);
    }

    game->_currentFrameIdx = 0;
}
