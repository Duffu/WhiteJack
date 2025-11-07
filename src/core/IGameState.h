#pragma once
class Game;
class IGameState
{
public:
    virtual ~IGameState();
    virtual void Update(float dt, Game *game) = 0;
    virtual void Draw() = 0;
    virtual void OnEnter();
    virtual void OnExit();
};