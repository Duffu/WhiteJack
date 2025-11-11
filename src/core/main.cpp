#include <iostream>
#include "raylib.h"
#include "Constants.h"
#include "Game.h"
#include "states/StateGameplay.h"
#include "states/StateGuide.h"
int main()
{
    Game game;
    game.ChangeState(new StateGuide());
    game.Run();

    return 0;
}