#include "PeekHoleCard.h"
PeekHoleCard::PeekHoleCard(Player &player) : m_player(player)
{
    Start();
}
PeekHoleCard::~PeekHoleCard() {}
void PeekHoleCard::Update(float dt)
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
            Rectangle &currentTarget = m_successZones[m_currentZoneToHit];
            if (CheckCollisionRecs(m_arrow, currentTarget))
            {
                // SUCCESS
                m_currentZoneToHit++;
                if (m_currentZoneToHit >= 3)
                {
                    m_currentState = CheatState::REWARD;
                    StartTimer(m_pauseTimer, 3.0f); // 3-second reward
                }
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
        Card &holeCard = m_player.getHand().GetLastCard();
        if (!holeCard.getIsFaceUp())
            holeCard.FlipCard();

        UpdateTimer(m_pauseTimer, dt);
        if (TimerDone(m_pauseTimer))
        {
            // Timer's done, flip it back
            if (holeCard.getIsFaceUp())
                holeCard.FlipCard();
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
void PeekHoleCard::Draw(UIManager &uiManager)
{
    std::string timeText = "Time: " + std::to_string(m_gameTimer.lifetime);
    DrawText(timeText.c_str(), 20, 680, 30, RED);

    if (m_currentState == CheatState::RUNNING)
    {
        DrawRectangleRec(m_bar, GRAY);
        DrawRectangleRec(m_arrow, RED);
        for (int i = 0; i < 3; ++i)
        {
            Color zoneColor = (i == m_currentZoneToHit) ? GREEN : DARKGRAY;
            DrawRectangleRec(m_successZones[i], zoneColor);
        }
    }
    if (CheckCollisionRecs(m_arrow, m_successZones[m_currentZoneToHit]) && !(m_currentState == CheatState::REWARD))
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
        uiManager.DrawPeekedCard(m_player.getHand().GetLastCard(), {120, 200}, 1.5);
    }
}
void PeekHoleCard::Start()
{ // Reset the minigame

    m_bar = {100, 200, 30, 400};
    for (int i = 0; i < 3; ++i)
    {
        float randomY = (float)getRandomInt(30, 370); // 400 (bar) - 30 (zone)
        float zoneHeight = 35.0f;                     // "Smaller zones"
        m_successZones[i] = {100, m_bar.y + randomY, 30, zoneHeight};
    }
    m_arrow = {100, 200, 30, 5};
    m_currentZoneToHit = 0;
    m_arrowSpeed = 230.0f; // Pixels per second
    m_currentState = CheatState::RUNNING;
    m_arrowState = ArrowState::MOVING_DOWN;
    m_arrow.y = m_bar.y;
    StartTimer(m_gameTimer, 9.0f);
}
