#pragma once
#include "game/Card.h"
#include <random>
extern std::mt19937 g_randomEngine;

struct Timer
{
    float lifetime = 0.0f;
};
void StartTimer(Timer &timer, float lifeTime);
void UpdateTimer(Timer &timer, float dt);
bool TimerDone(const Timer &timer);
int getRandomInt(int min, int max);
std::string SuitToString(Suit suit);
std::string RankToString(Rank rank);
int GetSuitFileBase(Suit suit);
Suit GetSuitFromInt(int value);
