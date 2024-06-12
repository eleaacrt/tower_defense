#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <glad/glad.h>

#include "Config/ConfigTower.hpp"

class ItdTower;

class Tower
{
public:
    Tower();
    ~Tower(){};

    std::string m_Type;
    // nb points à enlever à l'ennemi
    int m_Power;
    // portée de la tour
    int m_Range;
    // vitesse de tir
    int m_ShotSpeed;
    // coût de la tour
    int m_Cost;
    // texture file
    std::string m_TextureFile;
    // position de la tour
    std::pair<int, int> m_Position;

    void initTower(ItdTower itd_tower, std::pair<int, int> position, int id_type_tower);
    void loadTower(std::pair<int, int> position, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float _viewSize);
    void drawTower(Tower tower, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float _viewSize);

private:
    // ItdTower ItdTower;
};

// class TowerFactory
// {
// public:
//     TowerFactory();
//     ~TowerFactory(){};

//     Tower createTower(std::string type, std::pair<int, int> position);

// private:
//     std::vector<Tower> m_Towers;
//     std::unordered_map<std::string, Tower> m_TowerTypes;

//     ItdTower ItdTower;
// };