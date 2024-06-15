
// #include <glad/glad.h>
// #include "Tower.hpp"
// #include "Config/ConfigTarget.hpp"
// #include "Config/ConfigTower.hpp"
// #include "Map.hpp"
// #include "UserInterface.hpp"
// #include "AllTowers.hpp"

// #include "GLHelpers.hpp"

// AllTowers::AllTowers()
// {
//     ItdTower.read_itd_tower("data/itd_tower.itd");
//     towers = {};
//     nb_towers = ItdTower.allTowers.size();
//     selected_tower = -1;
//     is_a_tower_selected = false;
// }

// void AllTowers::load_all_towers(std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height)
// {
//     if (towers.size() > 0)
//     {
//         for (size_t i = 0; i < towers.size(); i++)
//         {
//             towers[i].loadTower(towers[i].m_Position, textures, _width, _height, viewSize, map_width, map_height);
//         }
//     }
// }

// void AllTowers::select_a_tower(std::pair<int, int> cursor_pos, std::unordered_map<std::string, GLuint> textures, int _width, int _height, float viewSize, int map_width, int map_height)
// {
//     if (selected_tower >= 0 && is_a_tower_selected)
//     {
//         ItdTower.allTowers[selected_tower].loadTower(cursor_pos, textures, _width, _height, viewSize, map_width, map_height);
//     }
// }

// // void AllTowers::check_targets(std::vector<Target> Waves, int _width, int _height, float viewSize, int map_width, int map_height)
// // {
// //     for (size_t i = 0; i < towers.size(); i++)
// //     {
// //         towers[i].check_targets(Waves, _width, _height, viewSize, map_width, map_height);
// //     }
// // }