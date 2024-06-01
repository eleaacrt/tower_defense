#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "Log.hpp"
#include "Node.hpp"
#include "ColorRGB.hpp"

// définir un nouveau type NodeId qui reste un entier
// plus compréhensible dans le code

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