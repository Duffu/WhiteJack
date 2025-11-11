#include "Utils.h"
#include "raylib.h"
std::mt19937 g_randomEngine;
int getRandomInt(int min, int max)
{
    std::uniform_int_distribution<> distr(min, max);
    return distr(g_randomEngine);
}
std::string SuitToString(Suit suit)
{
    switch (suit)
    {
    case Suit::HEARTS:
        return "hearts";
    case Suit::DIAMONDS:
        return "diamonds";
    case Suit::CLUBS:
        return "clubs";
    case Suit::SPADES:
        return "spades";
    default:
        return "unknown";
    }
}
std::string RankToString(Rank rank)
{
    switch (rank)
    {
    case Rank::ACE:
        return "ace";
    case Rank::TWO:
        return "two";
    case Rank::THREE:
        return "three";
    case Rank::FOUR:
        return "four";
    case Rank::FIVE:
        return "five";
    case Rank::SIX:
        return "six";
    case Rank::SEVEN:
        return "seven";
    case Rank::EIGHT:
        return "eight";
    case Rank::NINE:
        return "nine";
    case Rank::TEN:
        return "ten";
    case Rank::JACK:
        return "jack";
    case Rank::QUEEN:
        return "queen";
    case Rank::KING:
        return "king";
    default:
        return "unknown";
    }
}
// these are dependent front the asset file structure need to be updated if the assets change
int GetSuitFileBase(Suit suit)
{
    switch (suit)
    {
    case Suit::HEARTS:
        return 1;
    case Suit::DIAMONDS:
        return 29;
    case Suit::CLUBS:
        return 43;
    case Suit::SPADES:
        return 15;
    default:
        return -1; // Invalid suit
    }
}

Suit GetSuitFromInt(int value)
{
    switch (value)
    {
    case 1:
        return Suit::HEARTS;
    case 29:
        return Suit::DIAMONDS;
    case 43:
        return Suit::CLUBS;
    case 15:
        return Suit::SPADES;
    default:
        break;
    }
}

void StartTimer(Timer &timer, float duration)
{
    timer.lifetime = duration;
}
void UpdateTimer(Timer &timer, float dt)
{
    if (timer.lifetime > 0.0f)
    {
        timer.lifetime -= dt;
    }
}
bool TimerDone(const Timer &timer)
{
    return timer.lifetime <= 0.0f;
}