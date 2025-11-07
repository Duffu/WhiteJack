#include "Client.h"
Client::Client() : m_credits(1000), m_patience(70), m_maxPatience(100), m_Attention(100), m_maxAttention(100)
{
}
Client::~Client()
{
}
void Client::modifyPatience(float amount)
{
    m_patience += amount;
}