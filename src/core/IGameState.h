#pragma once

class IGameState
{
public:
    virtual ~IGameState();
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    virtual void OnEnter();
    virtual void OnExit();
};