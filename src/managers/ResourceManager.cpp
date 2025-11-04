#include "ResourceManager.h"
ResourceManager::ResourceManager()
{
    LoadTexture("card_back", "assets/card_Back.png");
    // 55 cause the nice guy who made the assets decided to put one of the back, front and empty texture after each rank
    // so we have to skip 14 28 42
    /* current set
    HEARTS:
        return 1;
    DIAMONDS:
        return 29;
    CLUBS:
        return 43;
    SPADES:
        return 15;
    */

    for (int i = 1; i <= 55; i++)
    {
        if (i == 14 || i == 28 || i == 42)
        {
            continue;
        }
        std::string cardRank;
        std::string cardSuit;
        std::string initialNumber;
        std::string textureName;
        std::string filePath;
        if (i <= 13)
        {
            cardSuit = "hearts";
            cardRank = RankToString(static_cast<Rank>(i));
        }
        else if (i <= 27)
        {
            cardSuit = "spades";
            int rankValue = i - 14;
            cardRank = RankToString(static_cast<Rank>(rankValue));
        }
        else if (i <= 41)
        {
            cardSuit = "diamonds";
            int rankValue = i - 28;
            cardRank = RankToString(static_cast<Rank>(rankValue));
        }
        else if (i <= 55)
        {
            cardSuit = "clubs";
            int rankValue = i - 42;
            cardRank = RankToString(static_cast<Rank>(rankValue));
        }

        if (i < 10)
        {
            initialNumber = "0" + std::to_string(i);
        }
        else
        {
            initialNumber = std::to_string(i);
        }
        textureName = cardRank + "_of_" + cardSuit;
        filePath = "assets/" + initialNumber + "_kerenel_Cards" + ".png";
        LoadTexture(textureName, filePath);
    }
}
ResourceManager::~ResourceManager()
{
    for (auto const &pair : m_textures)
    {
        UnloadTexture(pair.second);
    }
}

void ResourceManager::LoadTexture(const std::string &name, const std::string &filePath)
{
    Texture2D texture = ::LoadTexture(filePath.c_str());
    m_textures[name] = texture;
}
Texture2D ResourceManager::GetTexture(const std::string &name)
{
    return m_textures.at(name);
}

Texture2D ResourceManager::GetTexture(const Card &card)
{
    // .at() for safety
    if (!card.getIsFaceUp())
    {
        return m_textures.at("card_back");
    }
    std::string cardRank = RankToString(card.GetRank());
    std::string cardSuit = SuitToString(card.GetSuit());
    std::string textureName = cardRank + "_of_" + cardSuit;
    return m_textures.at(textureName);
}