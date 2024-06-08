#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#include <sstream>
#include <unordered_map>

#include "Map.hpp"
#include "App.hpp"
#include "GLHelpers.hpp"
#include "utils.hpp"
#include "ColorRGB.hpp"

// initaliser les Tuiles

Tile::Tile()
{
    m_Size = 1;
    m_Type = TypeTile::EMPTY;

    // img::Image empty{img::load(make_absolute_path("images/empty.png", true), 3, true)};
    // m_empty_texture = loadTexture(empty);
    // img::Image in{img::load(make_absolute_path("images/in.png", true), 3, true)};
    // m_in_texture = loadTexture(in);
    // img::Image out{img::load(make_absolute_path("images/out.png", true), 3, true)};
    // m_out_texture = loadTexture(out);
    // img::Image path{img::load(make_absolute_path("images/path.png", true), 3, true)};
    // m_path_texture = loadTexture(path);
    // img::Image corner{img::load(make_absolute_path("images/corner.png", true), 3, true)};
    // m_corner_texture = loadTexture(corner);
}

void Tile::draw(std::unordered_map<std::string, GLuint> textures)
{

    if (m_Type == TypeTile::EMPTY)
    {
        // NOIR
        draw_quad_with_texture(textures["empty.png"]);
    }
    if (m_Type == TypeTile::IN)
    {
        // BLEU
        draw_quad_with_texture(textures["in.png"]);
    }
    if (m_Type == TypeTile::OUT)
    {
        // ROUGE
        // glRotatef(180, 0, 0, 1);
        draw_quad_with_texture(textures["out.png"]);
    }
    if (m_Type == TypeTile::LEFT_DOWN)
    {
        // VIOLET
        // draw_quad_with_texture(m_corner_texture);
        draw_quad_with_texture(textures["corner.png"]);
    }
    if (m_Type == TypeTile::LEFT_UP)
    {
        // JAUNE
        glRotatef(270, 0, 0, 1);
        draw_quad_with_texture(textures["corner.png"]);
        // draw_quad_with_texture(m_corner_texture);
    }
    if (m_Type == TypeTile::RIGHT_DOWN)
    {
        // VERT
        glRotatef(90, 0, 0, 1);
        draw_quad_with_texture(textures["corner.png"]);
        // draw_quad_with_texture(m_corner_texture);
    }
    if (m_Type == TypeTile::RIGHT_UP)
    {
        // ORANGE
        glRotatef(180, 0, 0, 1);
        draw_quad_with_texture(textures["corner.png"]);
        // draw_quad_with_texture(m_corner_texture);
    }
    if (m_Type == TypeTile::HORIZONTAL)
    {
        // BLANC
        draw_quad_with_texture(textures["path.png"]);
        // draw_quad_with_texture(m_path_texture);
    }
    if (m_Type == TypeTile::VERTICAL)
    {
        // GRIS
        glRotatef(90, 0, 0, 1);
        draw_quad_with_texture(textures["path.png"]);
        // draw_quad_with_texture(m_path_texture);
    }
    // Log::Debug("Tile drawn");
}

ColorRGB Tile::get_UP_TyleColor(int i, int j, sil::Image map)
{
    ColorRGB tileColorMj;
    if (j >= 1)
    {
        tileColorMj.red = map.pixel(i, j - 1).r * 255;
        tileColorMj.green = map.pixel(i, j - 1).g * 255;
        tileColorMj.blue = map.pixel(i, j - 1).b * 255;
    }
    return tileColorMj;
}

ColorRGB Tile::get_DOWN_TyleColor(int i, int j, sil::Image map)
{
    ColorRGB tileColorPj;
    if (j < map.height() - 1)
    {
        tileColorPj.red = map.pixel(i, j + 1).r * 255;
        tileColorPj.green = map.pixel(i, j + 1).g * 255;
        tileColorPj.blue = map.pixel(i, j + 1).b * 255;
    }
    return tileColorPj;
}

ColorRGB Tile::get_LEFT_TyleColor(int i, int j, sil::Image map)
{
    ColorRGB tileColorMi;
    if (i >= 1)
    {
        tileColorMi.red = map.pixel(i - 1, j).r * 255;
        tileColorMi.green = map.pixel(i - 1, j).g * 255;
        tileColorMi.blue = map.pixel(i - 1, j).b * 255;
    }
    return tileColorMi;
}

ColorRGB Tile::get_RIGHT_TyleColor(int i, int j, sil::Image map)
{
    ColorRGB tileColorPi;
    if (i < map.width() - 1)
    {
        tileColorPi.red = map.pixel(i + 1, j).r * 255;
        tileColorPi.green = map.pixel(i + 1, j).g * 255;
        tileColorPi.blue = map.pixel(i + 1, j).b * 255;
    }
    return tileColorPi;
}