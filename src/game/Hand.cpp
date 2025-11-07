#include "Hand.h"
Hand::Hand()
{
}
Hand::~Hand()
{
}
void Hand::AddCard(const Card &card)
{
    m_cards.push_back(card);
}
int Hand::GetValue() const
{
    int totalValue = 0;
    int aceCount = 0;
    for (const auto &card : m_cards)
    {
        if (card.getIsFaceUp())
        {
            totalValue += card.GetValue();
            if (card.GetRank() == Rank::ACE)
            {
                aceCount++;
            }
        }
    }
    // Handle Aces as 11 if it doesn't bust the hand
    while (aceCount > 0 && totalValue + 10 <= 21)
    {
        totalValue += 10;
        aceCount--;
    }
    return totalValue;
}
void Hand::Clear()
{
    m_cards.clear();
}
