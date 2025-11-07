#include "UIManager.h"

UIManager::UIManager()
{
}
UIManager::~UIManager()
{
}
void UIManager::DrawHand(Hand &hand, Vector2 position)
{
    const float cardOffsetX = 40.0f;
    for (auto &card : hand.GetCards())
    {
        Texture2D tex = ResourceManager::GetInstance().GetTexture(card);

        DrawTexture(tex, (int)position.x, (int)position.y, WHITE);

        position.x += cardOffsetX;
    }
}

void UIManager::DrawMeter()
{
    // Implementation for drawing a meter (e.g., health, score) can be added here
}
void UIManager::DrawValue(int value, Vector2 position)
{
    std::string valueText = "Value: " + std::to_string(value);
    DrawText(valueText.c_str(), position.x, position.y, 20, WHITE);
}

void UIManager::DrawGameOver(Vector2 position)
{
    std::string valueText = "GAME OVER";
    DrawText(valueText.c_str(), position.x, position.y, 20, WHITE);
}
void UIManager::DrawRoundLost(Vector2 position)
{
    std::string valueText = "CLIENT WIN";
    DrawText(valueText.c_str(), position.x, position.y, 20, WHITE);
}
void UIManager::DrawRoundWon(Vector2 position)
{
    std::string valueText = "DEALER WIN";
    DrawText(valueText.c_str(), position.x, position.y, 20, WHITE);
}
void UIManager::DrawRoundPush(Vector2 position)
{
    std::string valueText = "PUSH";
    DrawText(valueText.c_str(), position.x, position.y, 20, WHITE);
}
