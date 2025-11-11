#pragma once
#include "IGameState.h"
class Game
{
private:
    void Update(float dt);
    void Draw();
    void Init();
    void Shutdown();
    bool m_running;
    IGameState *m_currentState;
    double m_debugUpdateDuration;
    double m_debugDrawDuration;

public:
    Game();
    ~Game();

    void Run();
    void ChangeState(IGameState *newState);
};
