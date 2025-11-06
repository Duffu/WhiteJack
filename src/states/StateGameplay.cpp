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
    while (m_client.getHand().GetValue() < 16 || getRandomInt(0, 100) <= 10) // Simple AI: hit if under 16 or 10% chance to hit otherwise (more about randomness later)
    {
        m_client.getHand().AddCard(m_deck.DealCard());
        Delay(m_aiDecisionTimer, dt); // Simulate thinking time
        m_client.getHand().GetLastCard().FlipCard();
    }
    m_aiDecisionTimer = 0.5f; // Reset timer for next decision
    m_currentPhase = RoundPhase::PLAYER_TURN;
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
    if (!m_roundResolved)
    {
        // --- This is all your old win/loss logic ---
        int playerValue = m_player.getHand().GetValue();
        int clientValue = m_client.getHand().GetValue();

        if (playerValue > 21)
        { /* Player busts */
        }
        else if (clientValue > 21)
        { /* Client busts */
        }
        else if (playerValue > clientValue)
        { /* Player wins */
        }
        else if (clientValue > playerValue)
        { /* Client wins */
        }
        else
        { /* Tie */
        }

        m_roundResolved = true;
        m_resolveTimer = 0.2f;
    }

    else
    {
        m_resolveTimer -= dt;
        if (m_resolveTimer <= 0.0f)
        {
            StartNewRound();
        }
    }
}

void StateGameplay::StartNewRound()
{
    m_player.getHand().Clear();
    m_client.getHand().Clear();
    m_deck.Shuffle();

    m_currentPhase = RoundPhase::DEALING;

    m_client.getHand().AddCard(m_deck.DealCard());
    m_client.getHand().GetLastCard().FlipCard();
    m_client.getHand().AddCard(m_deck.DealCard());
    m_client.getHand().GetLastCard().FlipCard();

    m_player.getHand().AddCard(m_deck.DealCard());
    m_player.getHand().GetLastCard().FlipCard();
    m_player.getHand().AddCard(m_deck.DealCard());

    m_currentPhase = RoundPhase::CLIENT_TURN;
    m_aiDecisionTimer = 0.5f;
    m_roundResolved = false;
}