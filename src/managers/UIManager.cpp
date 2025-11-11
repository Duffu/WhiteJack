#include "UIManager.h"
#include <iostream>
#include "string.h"
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
    DrawText((std::to_string((int)current)).c_str(), bounds.x + bounds.width + 10, bounds.y, 20, GRAY);

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

void UIManager::DrawCardBack(int posX, int posY)
{
    Texture2D tex = ResourceManager::GetInstance().GetTexture("card_back");
    DrawTexture(tex, posX, posY, WHITE);
}

void UIManager::DrawScore(int score, Vector2 position)
{
    std::string ScoreText = "Score: " + std::to_string(score);
    DrawText(ScoreText.c_str(), position.x, position.y, 20, WHITE);
}

void UIManager::DrawTips(int posX, int posY)
{
    const char *tipsTitle = "Tips";
    const char *tip1 = "Client wins don't reduce your score.";
    const char *tip2 = "Losing the client's patience is Game Over!";

    const char *title = "Controls";

    // Basic moves
    const char *keyH = "[H]";
    const char *textH = "Hit";
    const char *keyS = "[S]";
    const char *textS = "Stand";
    const char *keyF = "[F]";
    const char *textF = "Flip Card";

    // Cheats
    const char *keyP = "[P]";
    const char *textP = "Peek Deck";
    const char *keyE = "[E]";
    const char *textE = "Peek Hand";
    const char *keyX = "[L]";
    const char *textX = "Swap Card";

    int y = posY;
    int fontSize = 20;
    int keyColX = posX + 200;
    int textColX = posX + 250;
    int indentX = posX + 40;
    int lineHeight = 30;
    int sectionSpacing = 40;

    DrawText(tipsTitle, indentX, y, fontSize - 4, YELLOW);
    y += sectionSpacing;

    DrawText(tip1, indentX, y, fontSize - 4, WHITE);
    y += lineHeight;
    DrawText(tip2, indentX, y, fontSize - 4, WHITE);
    y += sectionSpacing;

    DrawText(title, textColX - 50, y, fontSize, YELLOW);
    y += sectionSpacing;

    // Basic
    DrawText(keyH, keyColX, y, fontSize, WHITE);
    DrawText(textH, textColX, y, fontSize, WHITE);
    y += lineHeight;

    DrawText(keyS, keyColX, y, fontSize, WHITE);
    DrawText(textS, textColX, y, fontSize, WHITE);
    y += lineHeight;

    DrawText(keyF, keyColX, y, fontSize, WHITE);
    DrawText(textF, textColX, y, fontSize, WHITE);
    y += sectionSpacing; // Extra space for next section

    // Cheats
    DrawText(keyP, keyColX, y, fontSize, RED);
    DrawText(textP, textColX, y, fontSize, RED);
    y += lineHeight;

    DrawText(keyE, keyColX, y, fontSize, RED);
    DrawText(textE, textColX, y, fontSize, RED);
    y += lineHeight;

    DrawText(keyX, keyColX, y, fontSize, RED);
    DrawText(textX, textColX, y, fontSize, RED);
    y += lineHeight;
}

void UIManager::DrawRewatchGuide(int posX, int posY)
{
    const char *rewatch1 = "Press [G]";
    const char *rewatch2 = "to rewatch Guide and restart game";
    DrawText(rewatch1, posX, posY, 17, WHITE);
    DrawText(rewatch2, posX, posY + 20, 17, WHITE);
}