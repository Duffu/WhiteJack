#pragma once
#include "Hand.h"

class Player
{
private:
    int m_trustHearts;
    Hand m_hand;

public:
    Player();
    ~Player();
    int getTrustHearts() const { return m_trustHearts; }
    void setTrustHearts(int trustHearts) { m_trustHearts = trustHearts; }
    Hand &getHand() { return m_hand; }
    const Hand &getHand() const { return m_hand; }
};