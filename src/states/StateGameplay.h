#pragma once
#include "core/IGameState.h"
#include "game/Deck.h"
#include "game/Player.h"
#include "game/Client.h"
#include "managers/UIManager.h"
#include "utils.h"
#include "StateGameOver.h"
#include "cheats/ICheat.h"
#include "cheats/Peek.h"
#include "cheats/PeekHoleCard.h"
#include "cheats/Swap.h"
enum class RoundPhase
{
    DEALING,
    CLIENT_TURN,
    PLAYER_TURN,
    RESOLVE,
    CHEATING,
    PLANNING
};
enum class WinState
{
    NONE,
    PLAYER_WON,
    PLAYER_LOST,
    PUSH
};

class StateGameplay : public IGameState
{
private:
    Deck m_deck;
    Player m_player;
    Client m_client;
    RoundPhase m_currentPhase;
    WinState m_winState;
    UIManager m_uiManager;
    Timer m_aiDecisionTimer;
    Timer m_resolveTimer;
    Timer m_dealTimer;
    Timer m_planningTimer;
    int m_cardsDealtCount = 0;
    Peek m_peek;
    PeekHoleCard m_peekHoleCard;
    Swap m_swap;
    ICheat *m_currentCheat;
    Sound m_hurtSound;

public:
    StateGameplay();
    ~StateGameplay() override;
    void Update(float dt, Game *game) override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;

private:
    void UpdateClientTurn(float dt, Game *game);
    void UpdatePlayerTurn(float dt, Game *game);
    void UpdateResolve(float dt, Game *game);
    void UpdateDealing(float dt, Game *game);
    void UpdateCheating(float dt, Game *game);

    void StartNewRound();
    bool CheckGameOverConditions(Game *game);
};
