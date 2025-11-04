#pragma once
#include <vector>
#include "Card.h"
class Hand
{
private:
    std::vector<Card> m_cards;

public:
    Hand();
    ~Hand();
    void AddCard(const Card &card);
    int GetValue() const;
    Card &GetLastCard() { return m_cards.back(); }
    void Clear();
};
