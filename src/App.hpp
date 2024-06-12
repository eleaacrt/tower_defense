#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include <unordered_map>

#include "Config/ConfigMap.hpp"
#include "Config/ConfigTower.hpp"
#include "Map.hpp"
#include "Wave.hpp"
#include "UserInterface.hpp"
#include "AllTowers.hpp"

class App
{
public:
    App();

    void setup();
    void update();
    void Load_Textures();

    // GLFW callbacks binding
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    void size_callback(GLFWwindow *window, int width, int height);

    int lifes;

    int _width, _height;
    std::pair<int, int> cursor_pos;

private:
    void render();

    double _previousTime{};
    float _viewSize{};

    // Add your variables here
    // GLuint _texture{};
    float _angle{};
    Map map;
    Wave waves;
    ItdTower ItdTower;
    AllTowers all_towers;
    UserInterface ui;
    int lifes_max;

    // map de textures
    std::unordered_map<std::string, GLuint> textures{};

    SimpleText TextRenderer{};
};