#include "Swap.h"
#include "core/Constants.h"
Swap::Swap(Deck &deck, Player &player) : m_player(player), m_deck(deck)
{
    Start();
}
Swap::~Swap()
{
}
void Swap::Update(float dt)
{
    switch (m_currentState)
    {
    case CheatState::RUNNING:
    {
        UpdateTimer(m_gameTimer, dt);
        if (TimerDone(m_gameTimer))
        {
            m_currentState = CheatState::FAIL; // Ran out of time
            return;
        }

        UpdateTimer(m_cardPopTimer, dt);
        if (TimerDone(m_cardPopTimer))
        {
            MoveTargetCard();
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();

            if (CheckCollisionPointRec(mousePos, m_target))
            {
                m_clickScore++;
                MoveTargetCard();

                if (m_clickScore >= 5)
                {
                    m_currentState = CheatState::REWARD;
                }
            }
            else
            {
                m_currentState = CheatState::FAIL;
            }
        }
    }
    break;
    case CheatState::REWARD:
    {
        Card &holeCard = m_player.getHand().GetLastCard();
        Card &topCard = m_deck.getNextCard();
        std::swap(holeCard, topCard);
        m_currentState = CheatState::SUCCESS;
    }
    break;

    case CheatState::FAIL:
    case CheatState::SUCCESS:
        break;
    }
}
void Swap::Draw(UIManager &uiManager)
{
    uiManager.DrawCardBack(m_target.x, m_target.y);

    std::string scoreText = "Score: " + std::to_string(m_clickScore) + " / 5";
    std::string timeText = "Time: " + std::to_string(m_gameTimer.lifetime);

    DrawText(scoreText.c_str(), 20, 640, 30, WHITE);
    DrawText(timeText.c_str(), 20, 680, 30, RED);
}
void Swap::Start()
{ // Reset the minigame
    m_target = {(float)getRandomInt(100, SCREEN_WIDTH - CARD_WIDTH - 100), (float)getRandomInt(100, SCREEN_HEIGHT - CARD_HEIGHT - 100), 56, 80};
    m_clickScore = 0;
    m_currentState = CheatState::RUNNING;

    StartTimer(m_gameTimer, 5.0f);
    StartTimer(m_cardPopTimer, 1.0f);
}

void Swap::MoveTargetCard()
{
    m_target.x = (float)getRandomInt(100, SCREEN_WIDTH - CARD_WIDTH - 100);
    m_target.y = (float)getRandomInt(100, SCREEN_HEIGHT - CARD_HEIGHT - 100);

    StartTimer(m_cardPopTimer, 1.0f);
}