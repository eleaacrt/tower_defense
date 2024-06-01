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
#include "Target.hpp"

// définir un nouveau type NodeId qui reste un entier
// plus compréhensible dans le code

class ItdTarget
{
public:
    ItdTarget();
    ~ItdTarget();
    bool read_itd_target(std::string const &filename);
    // std::string map_filename;
    std::vector<Target> Targets;
    std::vector<std::vector<Target>> Waves;

private:
    std::string get_next_line(std::ifstream &myfile);
};