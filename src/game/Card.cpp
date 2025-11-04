#include "Card.h"

Card::Card(Suit suit, Rank rank, bool m_isFaceUp) : m_suit(suit), m_rank(rank), m_isFaceUp(false)
{
}

Card::~Card()
{
}

int Card::GetValue() const
{
    if (m_isFaceUp == false)
    {
        return 0;
    }
    if (m_rank == Rank::JACK || m_rank == Rank::QUEEN || m_rank == Rank::KING)
    {
        return 10;
    }

    return static_cast<int>(m_rank);
}
Suit Card::GetSuit() const
{
    return m_suit;
}
Rank Card::GetRank() const
{
    return m_rank;
}