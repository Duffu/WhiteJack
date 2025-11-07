#pragma once
#include "Hand.h"

class Client
{
private:
    int m_credits;
    Hand m_hand;
    int m_patience;
    int m_maxPatience;
    int m_Attention;
    int m_maxAttention;

public:
    Client();
    ~Client();
    int getCredits() const { return m_credits; }
    void setCredits(int credits) { m_credits = credits; }
    const Hand &getHand() const { return m_hand; }
    Hand &getHand() { return m_hand; }
    int getPatience() const { return m_patience; }
    void setPatience(int patience) { m_patience = patience; }
    void modifyPatience(float amount);
    int getAttention() const { return m_Attention; }
    void setAttention(int attention) { m_Attention = attention; }
    void modifyAttention(float amount);

    int getMaxPatience() const { return m_maxPatience; }
};
