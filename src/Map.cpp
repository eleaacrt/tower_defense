
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

// récupérer les Tuiles

std::vector<Tile> Map::get_Tiles()
{

    ItdMap.read_itd_map("data/itd_map.itd");

    std::vector<Tile> allTiles;
    // ItdMap ItdMap;

    // read image file
    // Log::Debug("Map filename: " + ItdMap.map_filename);
    sil::Image map{"images/" + ItdMap.map_filename};

    for (int i = 0; i < map.width(); i++)
    {
        for (int j = 0; j < map.height(); j++)
        {
            ColorRGB tileColor;
            tileColor.red = map.pixel(i, j).r * 255;
            tileColor.green = map.pixel(i, j).g * 255;
            tileColor.blue = map.pixel(i, j).b * 255;

            std::string tilecolor = std::string(tileColor);

            Tile tile;

            // si la couleur du pixel est la couleur d'entrée
            if (tileColor == ItdMap.in_color)
            {
                tile.m_Type = TypeTile::IN;
                allTiles.push_back(tile);
            }

            // si la couleur du pixel est la couleur de sortie
            else if (tileColor == ItdMap.out_color)
            {
                tile.m_Type = TypeTile::OUT;
                allTiles.push_back(tile);
            }

            // si la couleur du pixel est la couleur du chemin
            else if (tileColor == ItdMap.path_color)
            {
                // récupération des informations de couleur
                // du pixel -i
                ColorRGB tileColorMi = tile.get_LEFT_TyleColor(i, j, map);
                // du pixel +i
                ColorRGB tileColorPi = tile.get_RIGHT_TyleColor(i, j, map);
                // du pixel -j
                ColorRGB tileColorMj = tile.get_UP_TyleColor(i, j, map);
                // du pixel +j
                ColorRGB tileColorPj = tile.get_DOWN_TyleColor(i, j, map);

                // si x == et y ++ : vertical
                if ((tileColorMj == ItdMap.path_color && tileColorPj == ItdMap.path_color) || 
                (tileColorMj == ItdMap.in_color && tileColorPj == ItdMap.path_color) || 
                (tileColorMj == ItdMap.out_color && tileColorPj == ItdMap.path_color))
                {
                    tile.m_Type = TypeTile::VERTICAL;
                    allTiles.push_back(tile);
                }
                // si x ++ et y == : horizontal
                // si x ++ et y ++ : left_up
                else if (tileColorMi == ItdMap.path_color && tileColorPj == ItdMap.path_color)
                {
                    tile.m_Type = TypeTile::LEFT_UP;
                    allTiles.push_back(tile);
                }
                // si x ++ et y -- : left_down
                else if (tileColorMi == ItdMap.path_color && tileColorMj == ItdMap.path_color)
                {
                    tile.m_Type = TypeTile::LEFT_DOWN;
                    allTiles.push_back(tile);
                }
                // si x -- et y ++ : right_up
                else if (tileColorPj == ItdMap.path_color && tileColorPi == ItdMap.path_color)
                {
                    tile.m_Type = TypeTile::RIGHT_UP;
                    allTiles.push_back(tile);
                }
                // si x -- et y -- : right_down
                else if (tileColorPi == ItdMap.path_color && tileColorMj == ItdMap.path_color)
                {
                    tile.m_Type = TypeTile::RIGHT_DOWN;
                    allTiles.push_back(tile);
                }
                else
                {
                    tile.m_Type = TypeTile::HORIZONTAL;
                    allTiles.push_back(tile);
                }
            }

            // sinon la couleur du pixel est un chemin vide
            else
            {
                tile.m_Type = TypeTile::EMPTY;
                allTiles.push_back(tile);
            }
            // Log::Debug("Tile color: " + tilecolor);
        }
    }

    return allTiles;
}

// initaliser la Map
void Map::draw(std::vector<Tile> tiles, std::unordered_map<std::string, GLuint> textures)
{

    float size = 1;

    // dessiner la map
    for (int i = -(m_Width / 2); i < (m_Width / 2); i++)
    {
        for (int j = -(m_Height / 2); j <= (m_Height / 2); j++)
        {
            // size_t index = (i * (m_Width)) + j;
            size_t index = (i + (m_Width / 2)) * m_Height + (j + (m_Height / 2));

            if (index < tiles.size())
            {
                glPushMatrix();
                glScalef(size, size, size);
                glTranslatef(i * size, j * size, 0);
                tiles[index].draw(textures);
                glPopMatrix();
            }
            else
            {
                Log::Error("Index " + std::to_string(index) + " out of range");
            }
        }
    }
}

std::vector<std::pair<int, int>> Map::get_in(std::vector<Tile> tiles)
{
    // ItdTarget.read_itd_target("data/itd_target.itd");

    std::vector<std::pair<int, int>> in;
    for (int i = -(m_Width / 2); i < (m_Width / 2); i++)
    {
        for (int j = -(m_Height / 2); j < (m_Height / 2); j++)
        {
            // size_t index = (i * (m_Width)) + j;
            size_t index = (i + (m_Width / 2)) * m_Width + (j + (m_Height / 2));
            if (tiles[index].m_Type == TypeTile::IN)
            {
                in.push_back(std::make_pair(i, j));
            }
        }
    }
    return in;
}