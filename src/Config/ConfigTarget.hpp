#pragma once

#include <iostream>
#include <vector>

#include "Target.hpp"

class Target;

class ItdTarget
{
public:
    ItdTarget();
    ~ItdTarget();
    bool read_itd_target(const std::string &filename);
    std::vector<Target> allTargets;

private:
    std::string get_next_line(std::ifstream &myfile);
};
