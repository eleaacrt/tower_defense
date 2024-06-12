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
};

void Tower::initTower(ItdTower itd_tower, std::pair<int, int> position, int id_type_tower)
{
    m_Type = itd_tower.allTowers[id_type_tower].m_Type;
    m_Power = itd_tower.allTowers[id_type_tower].m_Power;
    m_Range = itd_tower.allTowers[id_type_tower].m_Range;
    m_ShotSpeed = itd_tower.allTowers[id_type_tower].m_ShotSpeed;
    m_Cost = itd_tower.allTowers[id_type_tower].m_Cost;
    m_Position = position;
}

void Tower::loadTower(std::pair<int, int> position, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize)
{
    glPushMatrix();
    glTranslatef((position.first / viewSize) - ((_width / 2) / viewSize), -((position.second - (_height / 2)) / viewSize), 1);
    draw_quad_with_texture(textures[m_TextureFile]);
    glPopMatrix();
}