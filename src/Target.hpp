#include <vector>
#include <unordered_map>
#include <utility>

class Target
{
    Target(int pointsVie = 100, int speed = 10, int value = 15)
    {
        m_PointsVie = pointsVie;
        m_Speed = speed;
        m_Value = value;
        m_Position = std::make_pair(0, 0);
    };
    int m_PointsVie;
    int m_Speed;
    int m_Value;
    std::pair<int, int> m_Position;

    void move(std::pair<int, int> newPosition);
    void takeDamage(int damage);
    bool isDead();

    void update();
};
