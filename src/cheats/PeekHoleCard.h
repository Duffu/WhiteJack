#pragma once
#include "core/Utils.h"
#include "ICheat.h"
#include "raylib.h"
#include "managers/UIManager.h"

class PeekHoleCard : public ICheat
{

private:
    Player &m_player;

    CheatState m_currentState;
    ArrowState m_arrowState;
    float opacityMultiplier;

    Rectangle m_bar;
    Rectangle m_successZones[3];
    Rectangle m_arrow;

    float m_arrowSpeed;
    float m_arrowBaroffset;
    int m_currentZoneHit;
    int m_currentZoneToHit;
    Timer m_gameTimer;
    Timer m_pauseTimer;

public:
    PeekHoleCard(Player &m_player);
    ~PeekHoleCard() override;
    void Start();
    void Update(float dt) override;
    void Draw(UIManager &uiManager) override;
    CheatState GetState() const override { return m_currentState; }
};