#pragma once
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "core/Utils.h"

class Deck
{
private:
    std::vector<Card> m_cards;
    int penetration = getRandomInt(39, 42); // Percentage of the deck to be used before reshuffling
    void ResetAndShuffle();

public:
    Deck();
    ~Deck();
    void Shuffle();
    Card DealCard();
    int GetRemainingCount() const;
};