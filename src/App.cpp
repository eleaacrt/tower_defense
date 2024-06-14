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
    money = 25;
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
    glClearColor((182.f / 255.f), (213.f / 255.f), (60.f / 255.f), 0.0f);

    // Setup the text renderer with blending enabled and white text color
    // TextRenderer.ResetFont();
    // TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    // TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    // TextRenderer.EnableBlending(true);

    map.tiles = map.get_Tiles();
    Load_Textures();
    map.create_graph();
    Log::Debug("Graph created");
    map.get_shorter_path();
    Wave waves;
    AllTowers all_towers;
}

void App::update()
{
    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    _angle += 1.0f * elapsedTime;
    // _angle = std::fmod(_angle, 360.0f);

    all_towers.check_targets(waves.Waves[0], _width, _height, _viewSize, map.m_Width, map.m_Height);
    waves.update(map);

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
    int nb_targets_arrived = waves.get_number_of_target_arrived();

    if ((lifes_max - nb_targets_arrived) <= 0)
    {
        // glClearColor((132.f / 255.f), (163.f / 255.f), (10.f / 255.f), 0.0f);
        // game over
        // afficher game over
        // afficher score
        // afficher bouton pour rejouer
        // afficher bouton pour quitter
        glClearColor((82.f / 255.f), (113.f / 255.f), (0.f / 255.f), 0.0f);
        ui.game_over(_width, _height, textures);
    }
    else
    {
        map.draw(map.tiles, textures);
        ui.towers_to_select(_width, _height, textures, ItdTower, _viewSize);
        ui.load_life_bar(lifes_max, nb_targets_arrived, textures);
        all_towers.load_all_towers(textures, _width, _height, _viewSize, map.m_Width, map.m_Height);
        all_towers.select_a_tower(cursor_pos, textures, _width, _height, _viewSize, map.m_Width, map.m_Height);
        waves.load(map, textures);

        // ui.load_money(_width, _height, _viewSize, money, textures);

        // all_towers.attack();

        // Log::Debug(std::to_string(towers.size()));
        // if (towers.size() > 0)
        // {
        //     for (size_t i = 0; i < towers.size(); i++)
        //     {
        //         towers[i].loadTower(towers[i].m_Position, textures, _width, _height, _viewSize, map.m_Width, map.m_Width);
        //     }
        // }
        // Log::Debug("Selected tower: " + std::to_string(selected_tower));
    }
}

// TextRenderer.Label("Example of using SimpleText library", _width / 2, 20, SimpleText::CENTER);

// Without set precision
// const std::string angle_label_text { "Angle: " + std::to_string(_angle) };
// With c++20 you can use std::format
// const std::string angle_label_text { std::format("Angle: {:.2f}", _angle) };

// Using stringstream to format the string with fixed precision
// std::string angle_label_text {};
// std::stringstream stream {};
// stream << std::fixed << "Angle: " << std::setprecision(2) << _angle;
// angle_label_text = stream.str();

// TextRenderer.Label(angle_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

// TextRenderer.Render();

void App::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        // stopper le jeu
    }
}

void App::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (all_towers.is_a_tower_selected && all_towers.selected_tower >= 0)
        {
            ItdTower.allTowers[all_towers.selected_tower].m_Position = std::make_pair(xpos, ypos);
            all_towers.towers.push_back(ItdTower.allTowers[all_towers.selected_tower]);
            all_towers.selected_tower = -1;
            all_towers.is_a_tower_selected = false;
        }

        for (int i = 0; i < all_towers.nb_towers; i++)
        {
            // Log::Debug("Tower position: " + std::to_string(ui.get_tower_positions[i].first.first) + ", " + std::to_string(ui.get_tower_positions[i].first.second) + ", " + std::to_string(ui.get_tower_positions[i].second.first) + ", " + std::to_string(ui.get_tower_positions[i].second.second));
            if (xpos < ui.get_tower_positions[i].first.first && xpos > ui.get_tower_positions[i].second.first && ypos > ui.get_tower_positions[i].second.second && ypos < ui.get_tower_positions[i].first.second)
            {
                // Log::Debug("Tower selected: " + std::to_string(i));
                all_towers.selected_tower = i;
                all_towers.is_a_tower_selected = true;
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
    cursor_pos = std::make_pair(xpos, ypos);
    // Log::Debug("Mouse position: " + std::to_string(xpos) + ", " + std::to_string(ypos));
}

void App::size_callback(GLFWwindow *window, int width, int height)
{
    // DEUX FOIS PLUS GRAND QUE SOUS WINDOWS
    _width = width;
    _height = height;

    // Log::Debug("Width: " + std::to_string(_width) + " Height: " + std::to_string(_height));

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio{_width / (float)_height};

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1.0f)
    {
        glOrtho(
            -_viewSize / 2. * aspectRatio, _viewSize / 2. * aspectRatio,
            -_viewSize / 2., _viewSize / 2., -1.0, 1.0);
    }
    else
    {
        glOrtho(
            -_viewSize / 2., _viewSize / 2.,
            -_viewSize / 2. / aspectRatio, _viewSize / 2. / aspectRatio, -1.0, 1.0);
    }
}
