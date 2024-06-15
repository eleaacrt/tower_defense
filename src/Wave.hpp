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

    void initWave(Map map, std::unordered_map<std::string, GLuint> textures, int id_current_wave);
    void update(Map map, int &app_current_monster_index, int id_current_wave);
    int get_number_of_target_arrived(int id_current_wave);
    int get_number_of_target_dead(int id_current_wave);
    void load(Map map, std::unordered_map<std::string, GLuint> textures, float _viewSize, int &app_current_monster_index, int id_current_wave);
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