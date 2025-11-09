#include "Peek.h"
Peek::Peek(Deck &deck) : m_deck(deck)
{
    Start();
}
Peek::~Peek() {}
void Peek::Update(float dt)
{
    switch (m_currentState)
    {

    case CheatState::RUNNING:
    {
        // Check for timeout
        UpdateTimer(m_gameTimer, dt);
        if (TimerDone(m_gameTimer))
        {
            m_currentState = CheatState::FAIL;
            return;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            if (CheckCollisionRecs(m_arrow, m_successZone))
            {
                // SUCCESS

                m_gameTimer.lifetime = 0;
                m_currentState = CheatState::REWARD;
                StartTimer(m_pauseTimer, 3.0f);
            }
            else
            {
                m_currentState = CheatState::FAIL;
            }
            return;
        }

        // 3. Move the arrow
        if (m_arrowState == ArrowState::MOVING_DOWN)
        {
            m_arrow.y += m_arrowSpeed * dt;
        }
        if (m_arrowState == ArrowState::MOVING_UP)
        {
            m_arrow.y -= m_arrowSpeed * dt;
        }

        if (m_arrowState == ArrowState::MOVING_DOWN && m_arrow.y >= (m_bar.y + m_bar.height))
        {
            m_arrow.y = m_bar.y + m_bar.height;
            m_arrowState = ArrowState::MOVING_UP;
        }
        if (m_arrowState == ArrowState::MOVING_UP && m_arrow.y <= (m_bar.y))
        {
            m_arrow.y = m_bar.y;
            m_arrowState = ArrowState::MOVING_DOWN;
        }
    }
    break;
    case CheatState::REWARD:
    {
        Card &topCard = m_deck.getNextCard();
        if (!topCard.getIsFaceUp())
        {
            topCard.FlipCard();
        }
        UpdateTimer(m_pauseTimer, dt);

        if (TimerDone(m_pauseTimer))
        {
            if (topCard.getIsFaceUp())
            {
                topCard.FlipCard();
            }
            m_currentState = CheatState::SUCCESS;
        }
    }
    break;
    case CheatState::SUCCESS:
    case CheatState::FAIL:
        // Do nothing. The minigame is over.
        // StateGameplay will pick up this state.
        break;
    }
}
void Peek::Draw(UIManager &uiManager)
{
    if (m_currentState == CheatState::RUNNING)
    {
        DrawRectangleRec(m_bar, GRAY);
        DrawRectangleRec(m_arrow, RED);
        DrawRectangleRec(m_successZone, GREEN);
    }
    if (CheckCollisionRecs(m_arrow, m_successZone) && !(m_currentState == CheatState::REWARD))
    {
        DrawText("HIT SPACE!", 80, 150, 20, WHITE);
    }
    if (m_currentState == CheatState::SUCCESS || m_currentState == CheatState::REWARD)
    {
        DrawText("SUCCESS", 80, 150, 20, GREEN);
    }
    if (m_currentState == CheatState::FAIL)
    {
        DrawText("FAIL", 80, 150, 20, RED);
    }
    if (m_currentState == CheatState::REWARD)
    {
        uiManager.DrawPeekedCard(m_deck.getNextCard(), {120, 200}, 1.5);
    }
}
void Peek::Start()
{ // Reset the minigame

    float m_randomSuccessZoneValue = (float)getRandomInt(30, 170);
    m_arrowBaroffset = 10.0f;

    m_bar = {100, 200, 30, 400};
    m_successZone = {100, m_randomSuccessZoneValue + 200, 30, 50}; // A 100px zone in the middle
    m_arrow = {100, 200, 30, 5};

    m_arrowSpeed = 400.0f; // Pixels per second
    m_currentState = CheatState::RUNNING;
    m_arrowState = ArrowState::MOVING_DOWN;
    m_arrow.y = m_bar.y;
    StartTimer(m_gameTimer, 5.0f);
}
