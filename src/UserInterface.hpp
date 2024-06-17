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

    void load_life_bar(int lifes_max, int all_lifes, int lifes, std::unordered_map<std::string, GLuint> textures, bool &is_game_over);
    void load_money(int &_width, int &_height, float viewSize, int money, std::unordered_map<std::string, GLuint> textures);
    void game_over(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures);
    void win(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures);
    void pause(int &_width, int &_height);
    void start(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures);
    void towers_to_select(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures, ItdTower ItdTower, float viewSize);
    void show_level(int level);
    void controle_text(int &_width, int &_height);
    void load_infos_targets(std::vector<Target> targets, int app_current_monster_index);
    std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> get_tower_positions;

private:
    Map map;
    SimpleText TextRenderer{};
};