#pragma once
#include "IGameState.h"
class StateMainMenu : public IGameState
{
public:
    StateMainMenu();
    ~StateMainMenu() override;
    void Update(float dt, Game *game) override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;
};