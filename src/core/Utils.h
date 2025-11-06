#pragma once
#include "game/Card.h"
#include <random>

int getRandomInt(int min, int max);
std::string SuitToString(Suit suit);
std::string RankToString(Rank rank);
int GetSuitFileBase(Suit suit);
Suit GetSuitFromInt(int value);
void Delay(float delayTime, float dt);