#pragma once
enum class Suit
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};
enum class Rank
{
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 1
};
class Card
{
private:
    Suit m_suit;
    Rank m_rank;
    bool m_isFaceUp;

public:
    Card(Suit m_suit, Rank m_rank, bool m_isFaceUp = false);
    ~Card();
    int GetValue() const;
    bool getIsFaceUp() const { return m_isFaceUp; }
    void FlipCard() { m_isFaceUp = !m_isFaceUp; }
    Suit GetSuit() const;
    Rank GetRank() const;
};
