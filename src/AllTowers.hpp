#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <glad/glad.h>

#include "Config/ConfigTower.hpp"
#include "Tower.hpp"

class AllTowers
{
public:
    AllTowers();
    ~AllTowers(){};

    std::vector<Tower> towers;
    void select_a_tower(std::pair<int, int> cursor_pos, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height);
    void load_all_towers(std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height);

    void check_targets(std::vector<Target> &Waves, int _width, int _height, float viewSize, int map_width, int map_height);
    void attack();
    // void click_to_add_a_tower(double xpos, double ypos);
    // void click_to_select_a_tower(double xpos, double ypos, UserInterface ui);

    bool is_a_tower_selected;
    int selected_tower;
    int nb_towers;

private:
    ItdTower ItdTower;
};