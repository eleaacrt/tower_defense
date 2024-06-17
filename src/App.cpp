#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"
#include <unordered_map>

#include "App.hpp"
#include "Map.hpp"
#include "Config/ConfigMap.hpp"
#include "Config/ConfigTarget.hpp"
#include "Target.hpp"
#include "UserInterface.hpp"

App::App() : _previousTime(0.0), _viewSize(25)
{
    lifes_max = 5;
    cursor_pos = std::make_pair(0, 0);
    ItdTower.read_itd_tower("data/itd_tower.itd");
    money = 100;
    towers = {};
    nb_towers = ItdTower.allTowers.size();
    selected_tower = -1;
    is_a_tower_selected = false;
    app_current_monster_index = 0;
    nb_targets_arrived_and_dead = waves.Waves[0].size();
    id_current_wave = 0;
    total_number_of_waves = waves.Waves.size();
    pause = false;
    ItdMap.read_itd_map("data/itd_map.itd");
    nb_all_targets_arrived = 0;
    is_game_over = false;
}

void App::Load_Textures()
{
    for (const auto &entry : std::filesystem::directory_iterator(make_absolute_path("images")))
    {
        if (entry.is_regular_file())
        {
            std::string extension = entry.path().extension().string();
            if (extension == ".png" || extension == ".jpg" || extension == ".jpeg" || extension == ".bmp" || extension == ".gif")
            {
                Log::Debug("Loading texture: " + entry.path().string());
                img::Image image{img::load(entry.path().string(), 4, true)};
                GLuint texture_id = loadTexture(image);
                textures.insert({entry.path().filename().string(), texture_id});
            }
            else
            {
                Log::Debug("Skipping non-image file: " + entry.path().string());
            }
        }
        else
        {
            Log::Debug("Skipping non-regular file: " + entry.path().string());
        }
    }
}

void App::setup()
{
    // Set the clear color to a nice blue
    glClearColor((27.f / 255.f), (17.f / 255.f), (44.f / 255.f), 0.0f);

    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, SimpleText::Color::BLUE);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);

    TextRenderer.EnableBlending(true);

    map.tiles = map.get_Tiles();
    Load_Textures();
    map.create_graph();
    Log::Debug("Graph created");
    map.get_shorter_path();
    Wave waves;
    // AllTowers all_towers;
}

void App::update()
{
    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    _angle += 1.0f * elapsedTime;
    // _angle = std::fmod(_angle, 360.0f);

    waves.update(map, app_current_monster_index, id_current_wave);

    render();
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();

    // Log::Debug("lifes " + std::to_string(waves.lifes));
    int nb_targets_arrived = waves.get_number_of_target_arrived(id_current_wave);
    int nb_targets_dead = waves.get_number_of_target_dead(id_current_wave);

    if (pause)
    {
        // map.draw(map.tiles, textures);
        ui.pause(_width, _height);
    }

    else if (nb_targets_dead + nb_targets_arrived == waves.Waves[id_current_wave].size())
    {
        if (id_current_wave == (total_number_of_waves - 1))
        {
            ui.win(_width, _height, textures);
        }
        else
        {
            id_current_wave++;
            waves.currentMonsterIndex = 0;
            app_current_monster_index = 0;
            towers.clear();
            nb_all_targets_arrived += nb_targets_arrived;
        }
    }

    else if (is_game_over)
    {
        ui.game_over(_width, _height, textures);
    }

    else
    {
        map.draw_background(textures);
        map.draw(map.tiles, textures);
        ui.towers_to_select(_width, _height, textures, ItdTower, _viewSize);
        ui.load_life_bar(lifes_max, nb_all_targets_arrived, nb_targets_arrived, textures, is_game_over);
        ui.show_level(id_current_wave + 1);
        ui.controle_text(_width, _height);

        // INITIALISER LES VAGUES

        ui.load_infos_targets(waves.Waves[id_current_wave], app_current_monster_index);

        for (size_t i = 0; i < towers.size(); i++)
        {
            towers[i].check_targets(waves.Waves[id_current_wave], _width, _height, _viewSize, map.m_Width, map.m_Height, glfwGetTime(), money);
        }

        if (towers.size() > 0)
        {
            for (size_t i = 0; i < towers.size(); i++)
            {
                towers[i].loadTower(towers[i].m_Position, textures, _width, _height, _viewSize, map);
            }
        }

        if (selected_tower >= 0 && is_a_tower_selected)
        {
            ItdTower.allTowers[selected_tower].loadTower(cursor_pos, textures, _width, _height, _viewSize, map);
        }

        waves.load(map, textures, _viewSize, app_current_monster_index, id_current_wave);
        ui.load_money(_width, _height, _viewSize, money, textures);
    }
}

void App::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        // pause the game
        pause = !pause;
    }
}

void App::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        const float aspectRatio{windowWidth / static_cast<float>(windowHeight)};
        xpos = ((2 * xpos / windowWidth - 1) * aspectRatio);
        ypos = (1 - 2 * ypos / windowHeight);

        xpos *= (_viewSize) / 2;
        ypos *= (_viewSize) / 2;

        // normalisé sur les 25 px de hauteur
        cursor_pos = std::make_pair(xpos, ypos);

        // Log::Debug("Mouse position: " + std::to_string(xpos) + ", " + std::to_string(ypos));
        if (is_a_tower_selected && selected_tower >= 0)
        {
            money -= ItdTower.allTowers[selected_tower].m_Cost;
            ItdTower.allTowers[selected_tower].m_Position = std::make_pair(xpos, ypos);
            towers.push_back(ItdTower.allTowers[selected_tower]);
            selected_tower = -1;
            is_a_tower_selected = false;
        }

        for (int i = 0; i < nb_towers; i++)
        {
            // Log::Debug("-------------------");
            // Log::Debug("Tower position: " + std::to_string(ui.get_tower_positions[i].first.first) + ", " + std::to_string(ui.get_tower_positions[i].first.second) + ", " + std::to_string(ui.get_tower_positions[i].second.first) + ", " + std::to_string(ui.get_tower_positions[i].second.second));
            // Log::Debug("Mouse position: " + std::to_string(xpos) + ", " + std::to_string(ypos));
            if ((xpos > ui.get_tower_positions[i].first.first && xpos < ui.get_tower_positions[i].second.first && ypos > ui.get_tower_positions[i].first.second && ypos < ui.get_tower_positions[i].second.second))
            {
                if (money >= ItdTower.allTowers[i].m_Cost)
                {
                    // Log::Debug("Tower selected: " + std::to_string(i));
                    selected_tower = i;
                    is_a_tower_selected = true;
                }
            }
        }
    }
}

void App::scroll_callback(double xoffset, double yoffset)
{
}

void App::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    const float aspectRatio{windowWidth / static_cast<float>(windowHeight)};

    xpos = ((2 * xpos / windowWidth - 1) * aspectRatio);
    ypos = (1 - 2 * ypos / windowHeight);

    xpos *= (_viewSize) / 2;
    ypos *= (_viewSize) / 2;

    cursor_pos = std::make_pair(xpos, ypos);

    // Log::Debug("Mouse position: " + std::to_string(xpos) + ", " + std::to_string(ypos));
}

void App::size_callback(GLFWwindow *window, int width, int height)
{
    //(écran rétina) On associe les dimensions de la fenêtre au FrameBuffer
    _width = width;
    _height = height;

    glfwGetFramebufferSize(window, &_width, &_height);
    glViewport(0, 0, _width, _height);

    const float aspectRatio{_width / static_cast<float>(_height)};

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1.0f)
    {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}
