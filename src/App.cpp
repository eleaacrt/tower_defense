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

App::App() : _previousTime(0.0), _viewSize(18)
{
    // load what needs to be loaded here (for example textures)
    // img::Image map{img::load(make_absolute_path("images/map.png", true), 3, true)};
    // _texture = loadTexture(map);
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
                img::Image image{img::load(entry.path().string(), 3, true)};
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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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
    target.initTarget(map, textures);
}

void App::update()
{
    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    _angle += 1.0f * elapsedTime;
    // _angle = std::fmod(_angle, 360.0f);

    target.update();
    render();
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    map.draw(map.tiles, textures);
    target.move(map);

    // glPushMatrix();
    // glTranslatef(_angle, _angle, 0);
    // draw_quad();
    // glPopMatrix();
    // ItdTarget itd_target;
    // itd_target.read_itd_target("data/itd_target.itd");

    // itd_target.Targets[0].move();
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

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)
{
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/)
{
}

void App::size_callback(int width, int height)
{
    _width = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio{_width / (float)_height};

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
