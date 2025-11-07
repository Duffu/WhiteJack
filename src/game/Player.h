#pragma once
#include "Hand.h"

class Player
{
private:
    int m_trustHearts;
    int m_maxTrustHearts;
    Hand m_hand;

public:
    Player();
    ~Player();
    int getTrustHearts() const { return m_trustHearts; }
    int getMaxTrustHearts() const { return m_maxTrustHearts; }
    void modifyTrustHearts(int amount);
    Hand &getHand() { return m_hand; }
    const Hand &getHand() const { return m_hand; }
};