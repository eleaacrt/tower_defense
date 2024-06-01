#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>

class Target
{
public:
    Target();
    int m_PointsVie;
    int m_Speed;
    int m_Value;
    std::string m_Type;

    std::pair<int, int> m_Position;

    void move();
    void updatePostion(std::pair<int, int> newPosition);
    // void takeDamage(int damage);
    // bool isDead();
};
