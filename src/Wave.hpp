#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Config/ConfigWave.hpp"

class Wave
{
public:
    Wave();
    ~Wave(){};

    std::vector<std::vector<Target>> Waves;

    void initWave(Map map, std::unordered_map<std::string, GLuint> textures);
    void update(Map map);
    int get_number_of_target_arrived();
    void load(Map map, std::unordered_map<std::string, GLuint> textures);
    size_t currentMonsterIndex;
    size_t id_wave;
    // int lifes;

private:
    double m_time;
    double m_lastSpawnTime;
    double spawnDelay;
    ItdWave ItdWave;

    std::unordered_map<std::string, GLuint> textures;
    Map map;
};