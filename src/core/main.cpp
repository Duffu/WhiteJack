#include <iostream>
#include "raylib.h"
#include "Constants.h"
#include "Game.h"
#include "states/StateGameplay.h"
#include "states/StateGuide.h"
#include "core/Utils.h"

int main()
{
    std::random_device rd;
    g_randomEngine.seed(rd());
    InitAudioDevice();
    Game game;
    game.ChangeState(new StateGuide());
    game.Run();
    CloseAudioDevice();

    return 0;
}