#pragma once
#include "core/Utils.h"
#include "ICheat.h"
#include "raylib.h"
#include "managers/UIManager.h"
class Swap : public ICheat
{

private:
    Player &m_player;
    Deck &m_deck;
    CheatState m_currentState;
    Rectangle m_target;
    float m_cardPopSpeed = 0.5f;
    int m_clickScore;

    Timer m_gameTimer;
    Timer m_cardPopTimer;

    void MoveTargetCard();

public:
    Swap(Deck &deck, Player &player);
    ~Swap() override;
    void Start();
    void Update(float dt) override;
    void Draw(UIManager &uiManager) override;
    CheatState GetState() const override { return m_currentState; }
};