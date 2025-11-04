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
    DrawText("Gameplay State is working", 350, 280, 20, LIGHTGRAY);
}

void StateGameplay::OnEnter()
{
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
}
void StateGameplay::OnExit()
{
}
void StateGameplay::UpdateClientTurn(float dt)
{
    while (m_client.getHand().GetValue() < 16 || getRandomInt(0, 100) <= 10) // Simple AI: hit if under 16 or 10% chance to hit otherwise (more about randomness later)
    {
        m_client.getHand().AddCard(m_deck.DealCard());
        m_client.getHand().GetLastCard().FlipCard();
    }
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
    int playerValue = m_player.getHand().GetValue();
    int clientValue = m_client.getHand().GetValue();

    if (playerValue > 21)
    {
        // Player busts
    }
    else if (clientValue > 21)
    {
        // Client busts
    }
    else if (playerValue > clientValue)
    {
        // Player wins
    }
    else if (clientValue > playerValue)
    {
        // Client wins
    }
    else
    {
        // Tie
    }

    // Reset hands for next round
    m_player.getHand().Clear();
    m_client.getHand().Clear();

    StartNewRound();
}

void StateGameplay::StartNewRound()
{
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
}