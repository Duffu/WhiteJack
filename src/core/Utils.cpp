#include "Utils.h"
int getRandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(eng);
}