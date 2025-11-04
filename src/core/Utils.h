#pragma once
#include "game/Card.h"
#include <random>

int getRandomInt(int min, int max);
std::string SuitToString(Suit suit);
std::string ValueToString(Rank rank);
int GetSuitFileBase(Suit suit);