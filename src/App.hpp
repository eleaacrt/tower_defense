#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include <unordered_map>

#include "Config/ConfigMap.hpp"
#include "Map.hpp"

class App
{
public:
    App();

    void setup();
    void update();
    void Load_Textures();

    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    void render();

    int _width{};
    int _height{};
    double _previousTime{};
    float _viewSize{};

    // Add your variables here
    // GLuint _texture{};
    float _angle{};
    Map map;
    Target target;

    // map de textures
    std::unordered_map<std::string, GLuint> textures{};

    SimpleText TextRenderer{};
};