#pragma once

#include <vector>
#include <unordered_map>
#include <utility>

struct Tower
{
    int power;
    int range;
    int shot_speed;
    std::pair<int, int> position;
};