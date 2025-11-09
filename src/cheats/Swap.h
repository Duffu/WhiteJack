#pragma once
#include "core/Utils.h"
#include "ICheat.h"
#include "raylib.h"
#include "managers/UIManager.h"
class Peek : public ICheat
{

private:
    Player &m_player;
    Deck &m_deck;
    CheatState m_currentState;
    ArrowState m_arrowState;
    float opacityMultiplier;

    Rectangle m_bar;
    Rectangle m_successZone;
    Rectangle m_arrow;

    float m_cardPopSpeed;
    float m_arrowBaroffset;

    Timer m_gameTimer;
    Timer m_pauseTimer;

public:
    Peek(Deck &deck);
    ~Peek() override;
    void Start();
    void Update(float dt) override;
    void Draw(UIManager &uiManager) override;
    CheatState GetState() const override { return m_currentState; }
};