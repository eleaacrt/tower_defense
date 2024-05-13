#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "Log.hpp"
#include "Node.hpp"

class ColorRGB
{
public:
    ColorRGB(int r = 0, int g = 0, int b = 0)
    {
        red = r;
        green = g;
        blue = b;
    }
    ColorRGB(std::string colors)
    {
        std::istringstream f(colors);
        std::string s;
        try
        {
            std::getline(f, s, ' ');
            red = std::stoi(s);
            std::getline(f, s, ' ');
            green = std::stoi(s);
            std::getline(f, s, ' ');
            blue = std::stoi(s);
        }
        catch (std::exception const &ex)
        {
            Log::Error("Invalid color format: " + colors);
        }
    }
    operator std::string() const
    {
        return "[" + std::to_string(red) + ", " + std::to_string(green) + ", " + std::to_string(blue) + "]";
    }

    int red;
    int green;
    int blue;
};

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