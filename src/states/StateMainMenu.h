#pragma once
#include "IGameState.h"
class StateMainMenu : public IGameState
{
public:
    StateMainMenu();
    ~StateMainMenu() override;
    void Update(float dt) override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;
};