#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "simpletext.h"

#include "Map.hpp"
#include "Config/ConfigTower.hpp"

class UserInterface
{
public:
    UserInterface();
    ~UserInterface(){};

    void load_life_bar(int lifes_max, int lifes, std::unordered_map<std::string, GLuint> textures);
    void game_over(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures);
    void towers_to_select(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures, ItdTower ItdTower, float viewSize);
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> get_tower_positions;

private:
    Map map;
    SimpleText TextRenderer{};
};