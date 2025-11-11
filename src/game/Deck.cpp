#include "Deck.h"
#include "core/Utils.h"
#include <random>

Deck::Deck()
{
    ResetAndShuffle();
}
Deck::~Deck()
{
}
void Deck::Shuffle()
{
    std::shuffle(m_cards.begin(), m_cards.end(), g_randomEngine);
}
Card Deck::DealCard()
{
    Card dealtCard = m_cards.back();
    m_cards.pop_back();
    return dealtCard;
}
int Deck::GetRemainingCount() const
{
    return static_cast<int>(m_cards.size());
}
void Deck::ResetAndShuffle()
{
    m_cards.clear();
    for (int suit = static_cast<int>(Suit::HEARTS); suit <= static_cast<int>(Suit::SPADES); ++suit)
    {
        for (int rank = static_cast<int>(Rank::ACE); rank <= static_cast<int>(Rank::KING); ++rank)
        {
            m_cards.emplace_back(static_cast<Suit>(suit), static_cast<Rank>(rank));
        }
    }
    Shuffle();
}