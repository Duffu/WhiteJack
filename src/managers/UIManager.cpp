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

void UIManager::DrawMeter(float current, float max, Rectangle bounds, Color color)
{
    DrawRectangleRec(bounds, GRAY);

    float percentage = current / max;
    Rectangle filledBounds = bounds;
    filledBounds.width = bounds.width * percentage;

    DrawRectangleRec(filledBounds, color);
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
void UIManager::DrawHealthBar(int current, int max, Vector2 position)
{
    const float heartOffsetX = 60.0f;

    for (int i = 0; i < max; ++i)
    {
        Texture2D tex;

        if (i < current)
        {
            tex = ResourceManager::GetInstance().GetTexture("full_heart");
        }
        else
        {
            tex = ResourceManager::GetInstance().GetTexture("empty_heart");
        }

        DrawTexture(tex, (int)position.x, (int)position.y, WHITE);

        position.x += heartOffsetX;
    }
}

void UIManager::DrawPeekedCard(Card card, Vector2 position, float opacityMultiplier)
{

    Texture2D tex = ResourceManager::GetInstance().GetTexture(card);
    DrawTexture(tex, (int)position.x, (int)position.y, Fade(WHITE, opacityMultiplier));
}