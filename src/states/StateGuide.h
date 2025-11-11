#pragma once
#include "core/IGameState.h"
#include "core/Game.h"
#include "managers/UIManager.h"
#include "core/Utils.h"
enum class GuideState
{
    INTRODUCTION, // explain that this guide will take less than a min and the current state of the game is just in the basics and it has no fancy stuff just the base logic
    PLAYGUIDE1,   // explaining different Buttons
    PLAYGUIDE2,   // explaining punishments
    PLAYGUIDE3,   // explaining combos
    PLAYGUIDE4,   // explaining cheating minigames
    END           // explain breifly the future features and wish them to have fun in the game

};
class StateGuide : public IGameState
{
private:
    GuideState m_guideState;
    Timer m_typewriterTimer;
    int m_charCounter;
    Timer m_doubleClickTimer; // Tracks time between clicks
    int m_clickCount;         // 0, 1, or 2
public:
    StateGuide();
    ~StateGuide() override;

    void Update(float dt, Game *game) override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;
};