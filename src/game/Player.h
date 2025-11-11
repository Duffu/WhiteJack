#pragma once
#include "Hand.h"

class Player
{
private:
    int m_trustHearts;
    int m_maxTrustHearts;
    int m_score;
    Hand m_hand;

public:
    Player();
    ~Player();
    int getTrustHearts() const { return m_trustHearts; }
    int getMaxTrustHearts() const { return m_maxTrustHearts; }
    void modifyTrustHearts(int amount);
    Hand &getHand() { return m_hand; }
    const Hand &getHand() const { return m_hand; }
    int getScore() { return m_score; }
    void addScore(int amount) { m_score += amount; }
    void resetScore() { m_score = 0; }
};