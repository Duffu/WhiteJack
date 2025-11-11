#include "Player.h"
Player::Player() : m_trustHearts(5), m_maxTrustHearts(5)
{
}
Player::~Player()
{
}
void Player::modifyTrustHearts(int amount)
{
    m_trustHearts += amount;
}