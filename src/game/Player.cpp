#include "Player.h"
Player::Player() : m_trustHearts(3), m_maxTrustHearts(3)
{
}
Player::~Player()
{
}
void Player::modifyTrustHearts(int amount)
{
    m_trustHearts += amount;
}