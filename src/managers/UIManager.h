#pragma once
#include "ResourceManager.h"
#include "raylib.h"
#include "game/Hand.h"
#include "game/Card.h"

class UIManager
{
private:
public:
    UIManager();
    ~UIManager();
    void DrawHand(Hand &hand, Vector2 position);
    void DrawMeter();
    void DrawValue(int value, Vector2 position);
    void DrawHeartMeter(int currentHealth, int maxHealth, Vector2 position);
    void DrawScore(int score, Vector2 position);
    void DrawMessage(const std::string &message, Vector2 position);
    void DrawButton(const std::string &label, Vector2 position, Vector2 size);
    void DrawMoney(int amount, Vector2 position);
    void DrawGameOver(Vector2 position);
    void DrawRoundLost(Vector2 position);
    void DrawRoundWon(Vector2 position);
    void DrawRoundPush(Vector2 position);
};
