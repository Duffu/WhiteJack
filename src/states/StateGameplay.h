#pragma once
#include "core/IGameState.h"
#include "game/Deck.h"
#include "game/Player.h"
#include "game/Client.h"
#include "managers/UIManager.h"

enum class RoundPhase
{
    DEALING,
    CLIENT_TURN,
    PLAYER_TURN,
    RESOLVE
};
class StateGameplay : public IGameState
{
private:
    Deck m_deck;
    Player m_player;
    Client m_client;
    RoundPhase m_currentPhase;
    UIManager m_uiManager;
    float m_aiDecisionTimer = 0.5f;
    bool m_roundResolved;
    float m_resolveTimer;

public:
    StateGameplay();
    ~StateGameplay() override;
    void Update(float dt) override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;

private:
    void UpdateClientTurn(float dt);
    void UpdatePlayerTurn(float dt);
    void UpdateResolve(float dt);
    void StartNewRound();
};
