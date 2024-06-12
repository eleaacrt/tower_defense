
#include <glad/glad.h>
#include "Tower.hpp"
#include "Config/ConfigTarget.hpp"
#include "Config/ConfigTower.hpp"
#include "Map.hpp"
#include "UserInterface.hpp"
#include "AllTowers.hpp"

#include "GLHelpers.hpp"

AllTowers::AllTowers()
{
    ItdTower.read_itd_tower("data/itd_tower.itd");
    towers = {};
    nb_towers = ItdTower.allTowers.size();
    selected_tower = -1;
    is_a_tower_selected = false;
}

void AllTowers::load_all_towers(std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height)
{
    if (towers.size() > 0)
    {
        for (size_t i = 0; i < towers.size(); i++)
        {
            towers[i].loadTower(towers[i].m_Position, textures, _width, _height, viewSize, map_width, map_height);
        }
    }
}

void AllTowers::select_a_tower(std::pair<int, int> cursor_pos, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height)
{
    if (selected_tower >= 0 && is_a_tower_selected)
    {
        // Log::Debug("Cursors pos: " + std::to_string(cursor_pos.first) + ", " + std::to_string(cursor_pos.second));
        ItdTower.allTowers[selected_tower].loadTower(cursor_pos, textures, _width, _height, viewSize, map_width, map_height);
    }
}

void AllTowers::click_to_add_a_tower(double xpos, double ypos)
{
    if (is_a_tower_selected && selected_tower >= 0)
    {
        ItdTower.allTowers[selected_tower].m_Position = std::make_pair(xpos, ypos);
        towers.push_back(ItdTower.allTowers[selected_tower]);
        selected_tower = -1;
        is_a_tower_selected = false;
    }
}

void AllTowers::click_to_select_a_tower(double xpos, double ypos, UserInterface ui)
{
    for (int i = 0; i < nb_towers; i++)
    {
        // Log::Debug("Tower position: " + std::to_string(ui.get_tower_positions[i].first.first) + ", " + std::to_string(ui.get_tower_positions[i].first.second) + ", " + std::to_string(ui.get_tower_positions[i].second.first) + ", " + std::to_string(ui.get_tower_positions[i].second.second));
        if (xpos < ui.get_tower_positions[i].first.first && xpos > ui.get_tower_positions[i].second.first && ypos > ui.get_tower_positions[i].second.second && ypos < ui.get_tower_positions[i].first.second)
        {
            // Log::Debug("Tower selected: " + std::to_string(i));
            selected_tower = i;
            is_a_tower_selected = true;
        }
    }
}
