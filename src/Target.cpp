#include "Target.hpp"
#include <sstream>

void Target::move(std::pair<int, int> newPosition)
{
    m_Position = newPosition;
}

void Target::takeDamage(int damage)
{
    m_PointsVie -= damage;
}

bool Target::isDead()
{
    return m_PointsVie <= 0;
}