#include "states/StateGameplay.h"
#include "raylib.h"
#include <iostream>
#include <random>
#include "core/Utils.h"

StateGameplay::StateGameplay()
{
}
StateGameplay::~StateGameplay()
{
}
void StateGameplay::Update(float dt)
{
    switch (m_currentPhase)
    {
    case RoundPhase::DEALING:
        UpdateDealing(dt);
        break;
    case RoundPhase::CLIENT_TURN:
        UpdateClientTurn(dt);
        break;
    case RoundPhase::PLAYER_TURN:
        UpdatePlayerTurn(dt);
        break;
    case RoundPhase::RESOLVE:
        UpdateResolve(dt);
        break;
    default:
        break;
    }
}
void StateGameplay::Draw()
{
    m_uiManager.DrawHand(m_player.getHand(), {500, 600});
    m_uiManager.DrawHand(m_client.getHand(), {500, 100});
    m_uiManager.DrawValue(m_player.getHand().GetValue(), {800, 550});
    m_uiManager.DrawValue(m_client.getHand().GetValue(), {800, 150});

    switch (m_winState)
    {
    case WinState::PLAYER_WON:
        m_uiManager.DrawRoundWon({50, 400});
        break;
    case WinState::PLAYER_LOST:
        m_uiManager.DrawRoundLost({50, 400});
        break;
    case WinState::PUSH:
        m_uiManager.DrawRoundPush({50, 400});
        break;
    }
}

void StateGameplay::OnEnter()
{
    StartNewRound();
}
void StateGameplay::OnExit()
{
}
void StateGameplay::UpdateClientTurn(float dt)
{
    UpdateTimer(m_aiDecisionTimer, dt);

    if (!TimerDone(m_aiDecisionTimer))
    {
        return; // AI is thinking don't do anythink
    }

    if (m_client.getHand().GetValue() < 16 || getRandomInt(0, 100) <= 10)
    {
        m_client.getHand().AddCard(m_deck.DealCard());
        m_client.getHand().GetLastCard().FlipCard();
        StartTimer(m_aiDecisionTimer, 1.0f);
    }
    else if (m_client.getHand().GetValue() > 21)
    {
        m_currentPhase = RoundPhase::RESOLVE;
    }
    else
    {
        m_currentPhase = RoundPhase::PLAYER_TURN;
    }
}

void StateGameplay::UpdatePlayerTurn(float dt)
{
    /*
    Player is given the freedom to Hit or Stand or Flip
     but (for now) we can't trust the user to play perfectly
     and not mess up the deck indices so i added that extra condition
     (further warnings implementation with punishments later)
    */
    if (IsKeyPressed(KEY_F))
    {
        m_player.getHand().GetLastCard().FlipCard();
    }
    if (IsKeyPressed(KEY_H) && m_player.getHand().GetLastCard().getIsFaceUp() == true)
    {
        m_player.getHand().AddCard(m_deck.DealCard());
        m_player.getHand().GetLastCard().FlipCard();

        if (m_player.getHand().GetValue() > 21)
        {
            m_currentPhase = RoundPhase::RESOLVE;
        }
    }
    else if (IsKeyPressed(KEY_S))
    {
        m_currentPhase = RoundPhase::RESOLVE;
    }
}

void StateGameplay::UpdateResolve(float dt)
{

    int playerValue = m_player.getHand().GetValue();
    int clientValue = m_client.getHand().GetValue();

    if (m_winState == WinState::NONE)
    {
        int playerValue = m_player.getHand().GetValue();
        int clientValue = m_client.getHand().GetValue();

        if (playerValue > 21)
        {
            m_winState = WinState::PLAYER_LOST;
        }
        else if (clientValue > 21)
        {
            m_winState = WinState::PLAYER_WON;
        }
        else if (playerValue > clientValue)
        {
            m_winState = WinState::PLAYER_WON;
        }
        else if (clientValue > playerValue)
        {
            m_winState = WinState::PLAYER_LOST;
        }
        else
        {
            m_winState = WinState::PUSH;
        }

        // Start the pause timer
        StartTimer(m_resolveTimer, 2.0f);
    }

    // Now, we wait for the timer to finish
    UpdateTimer(m_resolveTimer, dt);
    if (TimerDone(m_resolveTimer))
    {
        StartNewRound();
    }
}
void StateGameplay::UpdateDealing(float dt)
{
    UpdateTimer(m_dealTimer, dt);

    if (!TimerDone(m_dealTimer))
    {
        return;
    }

    switch (m_cardsDealtCount)
    {
    case 0:
        m_client.getHand().AddCard(m_deck.DealCard());
        m_client.getHand().GetLastCard().FlipCard();
        break;
    case 1:
        m_player.getHand().AddCard(m_deck.DealCard());
        m_player.getHand().GetLastCard().FlipCard();
        break;
    case 2:
        m_client.getHand().AddCard(m_deck.DealCard());
        m_client.getHand().GetLastCard().FlipCard();
        break;
    case 3:
        m_player.getHand().AddCard(m_deck.DealCard());
        break;
    }

    m_cardsDealtCount++;

    if (m_cardsDealtCount >= 4)
    {
        m_currentPhase = RoundPhase::CLIENT_TURN;
        StartTimer(m_aiDecisionTimer, 1.0f);
    }
    else
    {
        StartTimer(m_dealTimer, 0.5f);
    }
}

void StateGameplay::StartNewRound()
{
    m_player.getHand().Clear();
    m_client.getHand().Clear();
    m_deck.Shuffle();

    m_winState = WinState::NONE;
    m_currentPhase = RoundPhase::DEALING;
    m_cardsDealtCount = 0;
    StartTimer(m_dealTimer, 0.5f);
}