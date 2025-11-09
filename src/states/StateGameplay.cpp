#include "states/StateGameplay.h"
#include "raylib.h"
#include <iostream>
#include <random>
#include "core/Utils.h"
#include "core/Game.h"
StateGameplay::StateGameplay() : m_peek(m_deck), m_peekHoleCard(m_player), m_swap(m_deck, m_player)
{
}
StateGameplay::~StateGameplay()
{
}
void StateGameplay::Update(float dt, Game *game)
{
    switch (m_currentPhase)
    {
    case RoundPhase::DEALING:
        UpdateDealing(dt, game);
        break;
    case RoundPhase::CLIENT_TURN:
        UpdateClientTurn(dt, game);
        break;
    case RoundPhase::PLAYER_TURN:
        UpdatePlayerTurn(dt, game);
        break;
    case RoundPhase::RESOLVE:
        UpdateResolve(dt, game);
        break;
    case RoundPhase::CHEATING:
        UpdateCheating(dt, game);
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
    Rectangle patienceBar = {100, 50, 200, 30};
    m_uiManager.DrawMeter(
        m_client.getPatience(),
        m_client.getMaxPatience(),
        patienceBar,
        RED);
    m_uiManager.DrawHealthBar(
        m_player.getTrustHearts(),
        m_player.getMaxTrustHearts(),
        {1100, 50});

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
    if (m_currentPhase == RoundPhase::CHEATING && m_currentCheat != nullptr)
    {
        m_currentCheat->Draw(m_uiManager);
    }
}

void StateGameplay::OnEnter()
{
    StartNewRound();
}
void StateGameplay::OnExit()
{
}

void StateGameplay::UpdateClientTurn(float dt, Game *game)
{
    UpdateTimer(m_aiDecisionTimer, dt);

    if (!TimerDone(m_aiDecisionTimer))
    {
        return; // AI is thinking don't do anythink
    }
    if (m_client.getHand().GetValue() > 21)
    {
        m_currentPhase = RoundPhase::RESOLVE;
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

void StateGameplay::UpdatePlayerTurn(float dt, Game *game)
{
    /*
    Player is given the freedom to Hit or Stand or Flip
     but (for now) we can't trust the user to play perfectly
     and not mess up the deck indices so i added that extra condition
     (further warnings implementation with punishments later)
    */
    if (IsKeyPressed(KEY_F))
    {
        if (!(m_player.getHand().GetLastCard().getIsFaceUp()))
        {
            m_player.getHand().GetLastCard().FlipCard();
        }
        else
        {
            m_player.modifyTrustHearts(-1);
            if (CheckGameOverConditions(game))
            {
                return;
            }
        }
    }
    if (IsKeyPressed(KEY_H) && m_player.getHand().GetLastCard().getIsFaceUp() == true)
    {
        if (m_player.getHand().GetValue() >= 17)
        {
            m_player.modifyTrustHearts(-1);
            if (CheckGameOverConditions(game))
            {
                return;
            }
        }
        else
        {
            m_player.getHand().AddCard(m_deck.DealCard());

            if (m_player.getHand().GetValue() > 21)
            {
                m_currentPhase = RoundPhase::RESOLVE;
            }
        }
    }
    else if (IsKeyPressed(KEY_S))
    {
        if (m_player.getHand().GetValue() < 17)
        {
            m_player.modifyTrustHearts(-1);
            if (CheckGameOverConditions(game))
            {
                return;
            }
        }
        else
        {
            m_currentPhase = RoundPhase::RESOLVE;
        }
    }
    else if (IsKeyPressed(KEY_P))
    {
        m_currentCheat = &m_peek;
        m_currentCheat->Start();
        m_currentPhase = RoundPhase::CHEATING;
    }
    else if (IsKeyPressed(KEY_M))
    {
        m_currentCheat = &m_peekHoleCard;
        m_currentCheat->Start();
        m_currentPhase = RoundPhase::CHEATING;
    }
    else if (IsKeyPressed(KEY_L))
    {
        m_currentCheat = &m_swap;
        m_currentCheat->Start();
        m_currentPhase = RoundPhase::CHEATING;
    }
}
void StateGameplay::UpdateCheating(float dt, Game *game)
{
    m_currentCheat->Update(dt);
    CheatState state = m_currentCheat->GetState();

    if (state == CheatState::RUNNING || state == CheatState::REWARD)
    {
        return; // DO NOTHING WE ARE STILL CHEATING
    }
    if (state == CheatState::FAIL)
    {
        m_player.modifyTrustHearts(-1);
        if (CheckGameOverConditions(game))
        {
            return;
        }
        m_currentPhase = RoundPhase::PLAYER_TURN; // lose a heart continue playing
    }
    if (state == CheatState::SUCCESS)
    {

        m_currentPhase = RoundPhase::PLAYER_TURN; // Cheat was a success continue playing
    }
    m_currentCheat = nullptr;
}
void StateGameplay::UpdateResolve(float dt, Game *game)
{

    int playerValue = m_player.getHand().GetValue();
    int clientValue = m_client.getHand().GetValue();

    if (m_winState == WinState::NONE)
    {
        int playerValue = m_player.getHand().GetValue();
        int clientValue = m_client.getHand().GetValue();

        if (playerValue > 21)
        {
            m_client.modifyPatience(15);
            m_winState = WinState::PLAYER_LOST;
        }
        else if (clientValue > 21)
        {
            m_client.modifyPatience(-20);
            if (CheckGameOverConditions(game))
            {
                return;
            }

            m_winState = WinState::PLAYER_WON;
        }
        else if (playerValue > clientValue)
        {
            m_client.modifyPatience(-10);
            if (CheckGameOverConditions(game))
            {
                return;
            }

            m_winState = WinState::PLAYER_WON;
        }
        else if (clientValue > playerValue)
        {
            m_client.modifyPatience(10);
            m_winState = WinState::PLAYER_LOST;
        }
        else
        {
            m_client.modifyPatience(-5);
            if (CheckGameOverConditions(game))
            {
                return;
            }

            m_winState = WinState::PUSH;
        }

        // Start the pause timer
        StartTimer(m_resolveTimer, 2.0f);
    }

    // wait for the timer to finish
    UpdateTimer(m_resolveTimer, dt);
    if (TimerDone(m_resolveTimer))
    {
        StartNewRound();
    }
}
void StateGameplay::UpdateDealing(float dt, Game *game)
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
    if (m_deck.GetRemainingCount() == 52)
    {
        m_deck.Shuffle();
    }
    if (m_deck.GetRemainingCount() <= m_deck.GetPenetration())
    {
        m_deck.ResetAndShuffle();
    }
    m_winState = WinState::NONE;
    m_currentPhase = RoundPhase::DEALING;
    m_cardsDealtCount = 0;
    StartTimer(m_dealTimer, 0.5f);
}

bool StateGameplay::CheckGameOverConditions(Game *game)
{
    if (m_client.getPatience() <= 0)
    {
        game->ChangeState(new StateGameOver());
        return true;
    }
    if (m_player.getTrustHearts() <= 0)
    {
        game->ChangeState(new StateGameOver());
        return true;
    }
    // TODO ATTENTION
    return false;
}