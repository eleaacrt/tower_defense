#pragma once

#include <sil/sil.hpp>
#include <img/img.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>

#include <iostream>

#include "Node.hpp"
#include "ColorRGB.hpp"
#include "Config/ConfigMap.hpp"

enum class TypeTile
{
    EMPTY,
    IN,
    OUT,
    LEFT_DOWN,
    LEFT_UP,
    RIGHT_DOWN,
    RIGHT_UP,
    HORIZONTAL,
    VERTICAL
};

class Tile
{
public:
    Tile();
    void draw(std::unordered_map<std::string, GLuint> textures);
    TypeTile m_Type;
    ColorRGB get_UP_TyleColor(int i, int j, sil::Image map);
    ColorRGB get_DOWN_TyleColor(int i, int j, sil::Image map);
    ColorRGB get_LEFT_TyleColor(int i, int j, sil::Image map);
    ColorRGB get_RIGHT_TyleColor(int i, int j, sil::Image map);
    float m_Size;
    // std::pair<int, int> m_Position;
private:
    // GLuint m_in_texture;
    // GLuint m_out_texture;
    // GLuint m_empty_texture;
    // GLuint m_path_texture;
    // GLuint m_corner_texture;
};