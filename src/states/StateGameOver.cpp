#include "states/StateGameOver.h"
#include "core/Game.h"
#include "states/StateGameplay.h"

StateGameOver::StateGameOver() {}
StateGameOver::~StateGameOver() {}

void StateGameOver::Update(float dt, Game *game)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        game->ChangeState(new StateGameplay());
    }
}

void StateGameOver::Draw()
{
    DrawText("GAME OVER", 300, 300, 40, RED);
    DrawText("Press ENTER to play again", 250, 400, 20, WHITE);
}