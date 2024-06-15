
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
#include "Graph.hpp"

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

void Map::get_in_out_coordonnees()
{
    // ItdTarget.read_itd_target("data/itd_target.itd");

    // récupérer les coordonnées des points d'entrée et de sortie
    for (int i = -(m_Width / 2); i < (m_Width / 2); i++)
    {
        for (int j = -(m_Height / 2); j < (m_Height / 2); j++)
        {
            // size_t index = (i * (m_Width)) + j;
            size_t index = (i + (m_Width / 2)) * m_Height + (j + (m_Height / 2));
            if (tiles[index].m_Type == TypeTile::IN)
            {
                in_tiles_coordonnees.push_back(std::make_pair(i + (m_Width / 2), j + (m_Height / 2)));
            }
            else if (tiles[index].m_Type == TypeTile::OUT)
            {
                out_tile_coordonnees = std::make_pair(i + m_Width / 2, j + m_Height / 2);
            }
        }
    }
}

void Map::get_in_out_ID()
{
    get_in_out_coordonnees();
    for (Node node : ItdMap.nodes)
    {
        // normalization des coordonnées
        std::pair<int, int> node_coordonnee = {node.m_Position.first, (m_Height - node.m_Position.second - 1)};
        for (std::pair<int, int> coordonnees : in_tiles_coordonnees)
        {
            // Log::Debug("In Coordonnees: " + std::to_string(coordonnees.first) + " " + std::to_string(coordonnees.second));
            // Log::Debug("Node Coordonnees: " + std::to_string(node_coordonnee.first) + " " + std::to_string(node_coordonnee.second));
            // Log::Debug("-----------");
            if (node_coordonnee.first == coordonnees.first && node_coordonnee.second == coordonnees.second)
            {
                Log::Debug("In ID: " + std::to_string(node.m_Id));
                in_tiles_ID.push_back(node.m_Id);
            }
        }
        if (node_coordonnee.first == out_tile_coordonnees.first && node_coordonnee.second == out_tile_coordonnees.second)
        {
            Log::Debug("Out ID: " + std::to_string(node.m_Id));
            out_tile_ID = node.m_Id;
        }
    }
}

void Map::create_graph()
{
    for (Node node : ItdMap.nodes)
    {
        // Log::Debug("Node: " + std::to_string(node.m_Id) + " " + std::to_string(node.m_Position.first) + " " + std::to_string(node.m_Position.second));
        for (int neighbour : node.m_ConnectedNodes)
        {
            // Log::Debug("Neighbour: " + std::to_string(neighbour));
            for (Node neighbourNode : ItdMap.nodes)
            {
                if (neighbourNode.m_Id == neighbour)
                {
                    float weight = sqrt(pow(node.m_Position.first - neighbourNode.m_Position.first, 2) + pow(node.m_Position.second - neighbourNode.m_Position.second, 2));
                    graph.add_directed_edge(node.m_Id, neighbourNode.m_Id, weight);
                    Log::Debug("Edge: " + std::to_string(node.m_Id) + " - " + std::to_string(neighbourNode.m_Id) + " : " + std::to_string(weight));
                }
            }
        }
    }
}

void Map::get_shorter_path()
{
    get_in_out_ID();

    for (int in_tiles : in_tiles_ID)
    {
        std::unordered_map<int, std::pair<float, int>> distances{graph.dijkstra(graph, in_tiles, out_tile_ID)};
        std::vector<int> shorter_path_id;
        std::vector<Node> shorter_path;

        auto final_edge{distances.at(out_tile_ID)};
        // Log::Debug("Distance minimale : " + std::to_string(final_edge.first));
        // Log::Debug("Out ID: " + std::to_string(out_tile_ID));

        shorter_path_id.push_back(out_tile_ID);
        while (final_edge.second != in_tiles)
        {
            shorter_path_id.push_back(final_edge.second);
            final_edge = distances.at(final_edge.second);
        }

        shorter_path_id.push_back(in_tiles);

        for (int shorter_node_id : shorter_path_id)
        {
            for (Node &node : ItdMap.nodes)
                if (node.m_Id == shorter_node_id)
                    shorter_path.push_back(node);
        }

        all_shorter_path.push_back(shorter_path);
    }
}
