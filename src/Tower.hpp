#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>

#include "Config/ConfigTower.hpp"

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

private:
    // ItdTower ItdTower;
};