#pragma once

#include "Log.hpp"
#include "Node.hpp"
#include "ColorRGB.hpp"

class ItdMap
{
public:
    ItdMap();
    ~ItdMap();
    bool read_itd_map(std::string const &filename);
    std::string map_filename;
    ColorRGB path_color;
    ColorRGB in_color;
    ColorRGB out_color;
    std::vector<Node> nodes;

private:
    std::string get_next_line(std::ifstream &myfile);
};