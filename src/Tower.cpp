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

    if (position.first >= (map_width))
    {
        position.first = (map_width)-1;
    }
    if (position.first <= -(map_width))
    {
        position.first = -(map_width);
    }

    if (position.second >= map_height)
    {
        position.second = (map_height);
    }
    if (position.second <= -(map_height))
    {
        position.second = -(map_height);
    }

    glPushMatrix();
    glTranslatef((position.first) / 2, position.second / 2, 0);
    draw_quad_with_texture(textures[m_TextureFile]);
    glPopMatrix();
}

void Tower::check_targets(std::vector<Target> &Waves, int _width, int _height, float viewSize, int map_width, int map_height, const double currentTime, int &money)
{
    // Log::Debug("position tour : " + std::to_string(xTransformed) + ", " + std::to_string(yTransformed));
    for (size_t i = 0; i < Waves.size(); i++)
    {
        // Log::Debug("wave[i] :" + Waves[i].m_Type);
        std::pair<float, float> target_position = {(Waves[i].m_TargetPosition.first) - (map_width / 2), (Waves[i].m_TargetPosition.second) - (map_height / 2)};
        std::pair<float, float> tower_position = {m_Position.first / 2, m_Position.second / 2};
        Log::Debug("tower position " + std::to_string(tower_position.first) + ", " + std::to_string(tower_position.second));
        Log::Debug("wave[i].position " + std::to_string(target_position.first) + ", " + std::to_string(target_position.second));
        float distance = sqrt(pow(target_position.first - tower_position.first, 2) + pow(target_position.second - tower_position.second, 2));
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