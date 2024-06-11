#pragma once

#include <iostream>
#include <vector>

#include "Target.hpp"

class ItdWave
{
public:
    ItdWave();
    ~ItdWave();
    bool read_itd_wave(const std::string &filename);
    std::vector<std::vector<Target>> Waves;

private:
    ItdTarget ItdTarget;
    std::vector<Target> allTargets;
    std::string get_next_line(std::ifstream &myfile);
};
