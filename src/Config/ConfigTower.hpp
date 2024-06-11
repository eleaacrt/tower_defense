#pragma once

#include <iostream>
#include <vector>

#include "Tower.hpp"

class Tower;

class ItdTower
{
public:
    ItdTower();
    ~ItdTower();
    bool read_itd_tower(const std::string &filename);
    std::vector<Tower> allTowers;

private:
    std::string get_next_line(std::ifstream &myfile);
};