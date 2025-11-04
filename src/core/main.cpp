#include <iostream>
#include "raylib.h"
#include "Constants.h"
#include "Game.h"
#include "states/StateGameplay.h"
int main()
{
    Game game;
    game.ChangeState(new StateGameplay());
    game.Run();

    return 0;
}