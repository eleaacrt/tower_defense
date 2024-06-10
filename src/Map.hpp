#pragma once

#include <sil/sil.hpp>
#include <img/img.hpp>

#include <unordered_map>
#include <iostream>

#include "Config/ConfigMap.hpp"
#include "Config/ConfigTarget.hpp"
#include "Node.hpp"
#include "Tile.hpp"
#include "Graph.hpp"
#include "Target.hpp"

class Map
{
public:
    Map()
    {
        ItdMap.read_itd_map("data/itd_map.itd");
        sil::Image map{"images/" + ItdMap.map_filename};
        m_Width = map.width();
        m_Height = map.height();
        // std::vector<Tile> m_tiles = get_Tiles(ItdMap);
    };
    ~Map(){};

    std::vector<Tile> get_Tiles();
    std::vector<Tile> tiles;

    void draw(std::vector<Tile> tiles, std::unordered_map<std::string, GLuint> textures);

    // récupérer les coordonnées des points d'entrée et de sortie
    void get_in_out_coordonnees();
    void get_in_out_ID();
    std::vector<std::pair<int, int>> in_tiles_coordonnees;
    std::pair<int, int> out_tile_coordonnees;
    std::vector<NodeId> in_tiles_ID;
    NodeId out_tile_ID;

    void get_shorter_path();
    std::vector<std::vector<Node>> all_shorter_path;
    void create_graph();

    int m_Width;
    int m_Height;

private:
    ItdMap ItdMap;
    Graph::WeightedGraph graph;
    // ItdTarget ItdTarget;
};