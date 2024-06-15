#include "Tower.hpp"
#include "Config/ConfigTarget.hpp"
#include "Config/ConfigTower.hpp"
#include "Map.hpp"

#include "GLHelpers.hpp"

Tower::Tower()
{
    m_Type = "tower";
    m_Power = 0;
    m_Range = 0;
    m_ShotSpeed = 0;
    m_Cost = 0;
    m_Position = std::make_pair(0, 0);
    target_to_attack = -1;
    shotDelay = 0;
    lastShotTime = 0;
}

void Tower::initTower(ItdTower itd_tower, std::pair<int, int> position, int id_type_tower)
{
    m_Type = itd_tower.allTowers[id_type_tower].m_Type;
    m_Power = itd_tower.allTowers[id_type_tower].m_Power;
    m_Range = itd_tower.allTowers[id_type_tower].m_Range;
    m_ShotSpeed = itd_tower.allTowers[id_type_tower].m_ShotSpeed;
    m_Cost = itd_tower.allTowers[id_type_tower].m_Cost;
    m_Position = position;
}

void Tower::loadTower(std::pair<int, int> position, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height)
{
    float x = (position.first / (float)_width) * 2 - 1;
    float y = 1 - (position.second / (float)_height) * 2;
    // getPosAndDraw(textures, x, y, _width, _height, viewSize, map_width, map_height);
    float viewHeight = _height / viewSize;
    float viewWidth = _width / viewSize;

    int xTransformed = int(x * (viewWidth / 2)) % int(viewSize);
    int yTransformed = int(y * (viewHeight / 2)) % int(viewSize);

    if (xTransformed >= (map_width / 2))
    {
        xTransformed = (map_width / 2) - 1;
    }
    if (xTransformed <= -(map_width / 2))
    {
        xTransformed = -(map_width / 2);
    }

    if (yTransformed >= map_height / 2)
    {
        yTransformed = (map_height / 2);
    }
    
    if (yTransformed <= -(map_height / 2))
    {
        yTransformed = -(map_height / 2);
    }

    glPushMatrix();
    glTranslatef(xTransformed, yTransformed, 0);
    draw_quad_with_texture(textures[m_TextureFile]);
    glPopMatrix();
}

void Tower::check_targets(std::vector<Target> &Waves, int _width, int _height, float viewSize, int map_width, int map_height, const double currentTime, int &money)
{
    float x = (m_Position.first / (float)_width) * 2 - 1;
    float y = 1 - (m_Position.second / (float)_height) * 2;
    // getPosAndDraw(textures, x, y, _width, _height, viewSize, map_width, map_height);
    float viewHeight = _height / viewSize;
    float viewWidth = _width / viewSize;

    int xTransformed = int(x * (viewWidth / 2)) % int(viewSize) + (map_width / 2);
    int yTransformed = (int(y * (viewHeight / 2)) % int(viewSize)) + (map_height / 2);

    // Log::Debug("position tour : " + std::to_string(xTransformed) + ", " + std::to_string(yTransformed));
    for (size_t i = 0; i < Waves.size(); i++)
    {
        // Log::Debug("wave[i] :" + Waves[i].m_Type);
        // Log::Debug("wave[i].position " + std::to_string(Waves[i].m_TargetPosition.first) + ", " + std::to_string(Waves[i].m_TargetPosition.second));
        float distance = sqrt(pow(Waves[i].m_TargetPosition.first - xTransformed, 2) + pow(Waves[i].m_TargetPosition.second - yTransformed, 2));
        // Log::Debug("distance : " + std::to_string(distance));
        // Log::Debug("range : " + std::to_string(m_Range));

        if (abs(distance) <= m_Range && !Waves[i].m_isDead && target_to_attack == -1)
        {
            // Log::Debug("target to attack : " + Waves[i].m_Type);
            target_to_attack = i;
        }
        if (abs(distance) > m_Range && target_to_attack == i)
        {
            target_to_attack = -1;
        }
    }

    if ((target_to_attack != -1) && (currentTime - lastShotTime >= m_ShotSpeed))
    {
        // Log::Debug("targets to attack size : " + std::to_string(targets_to_attack.size()));
        Waves[target_to_attack].attaque(m_Power);
        Waves[target_to_attack].m_PointsVie -= m_Power;
        lastShotTime = currentTime;
    }

    if (Waves[target_to_attack].m_PointsVie <= 0 && target_to_attack != -1)
    {
        Waves[target_to_attack].m_isDead = true;
        Waves[target_to_attack].m_PointsVie = 0;
        money += Waves[target_to_attack].m_Value;
        target_to_attack = -1;
    }
}