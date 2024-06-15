#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <glad/glad.h>
#include <queue>

#include "Config/ConfigTower.hpp"
#include "Target.hpp"

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
    float m_ShotSpeed;
    // coût de la tour
    int m_Cost;
    // texture file
    std::string m_TextureFile;
    // position de la tour
    std::pair<int, int> m_Position;

    void initTower(ItdTower itd_tower, std::pair<int, int> position, int id_type_tower);
    void loadTower(std::pair<int, int> position, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float _viewSize, int map_width, int map_height);
    void drawTower(std::unordered_map<std::string, GLuint> textures, int _width, int _height, float _viewSize, int map_width, int map_height);

    void check_targets(std::vector<Target> &Waves, int _width, int _height, float viewSize, int map_width, int map_height, const double currentTime, int &money);
    void attack();

    // std::queue<Target> targets_to_attack;

    // void getPosAndDraw(std::unordered_map<std::string, GLuint> textures, float x, float y, int _width, int _height, float viewSize, int map_width, int map_height)
private:
    int target_to_attack;
    int shotDelay;
    int lastShotTime;
    // ItdTower ItdTower;
};