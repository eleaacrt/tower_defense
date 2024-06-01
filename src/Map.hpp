#pragma once

#include <sil/sil.hpp>
#include <img/img.hpp>

#include "Config/ConfigMap.hpp"
#include "Node.hpp"
#include "Tile.hpp"

#include <iostream>

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
    std::vector<Tile> get_Tiles();
    std::vector<Tile> tiles;
    void draw(std::vector<Tile> tiles);

private:
    int m_Width;
    int m_Height;
    ItdMap ItdMap;
};