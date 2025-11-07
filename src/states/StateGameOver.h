#pragma once
#include "core/IGameState.h"
#include "raylib.h"

class StateGameOver : public IGameState
{
public:
    StateGameOver();
    ~StateGameOver() override;

    void Update(float dt, Game *game) override;
    void Draw() override;
};