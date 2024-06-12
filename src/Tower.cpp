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

// void Tower::drawTower(std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height)
// {
//     float x = (m_Position.first / (float)_width) * 2 - 1;
//     float y = 1 - (m_Position.second / (float)_height) * 2;
//     getPosAndDraw(textures, x, y, _width, _height, viewSize, map_width, map_height);
// }

// void Tower::getPosAndDraw(std::unordered_map<std::string, GLuint> textures, float x, float y, int _width, int _height, float viewSize, int map_width, int map_height)
// {
//     float viewHeight = _height / viewSize;
//     float viewWidth = _width / viewSize;

//     int xTransformed = int(x * (viewWidth / 2)) % int(viewSize);
//     int yTransformed = int(y * (viewHeight / 2)) % int(viewSize);

//     if (xTransformed >= (map_width / 2))
//     {
//         xTransformed = (map_width / 2) - 1;
//     }
//     if (xTransformed <= -(map_width / 2))
//     {
//         xTransformed = -(map_width / 2);
//     }

//     if (yTransformed >= map_height / 2)
//     {
//         yTransformed = (map_height / 2) - 1;
//     }
//     if (yTransformed <= -(map_height / 2))
//     {
//         yTransformed = -(map_height / 2) + 1;
//     }

//     glPushMatrix();
//     glTranslatef(xTransformed, yTransformed, 0);
//     draw_quad_with_texture(textures[m_TextureFile]);
//     glPopMatrix();
// }