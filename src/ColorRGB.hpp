#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "Log.hpp"

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

    bool operator==(const ColorRGB &c) const
    {
        return red == c.red && green == c.green && blue == c.blue;
    }

    int red;
    int green;
    int blue;
};
