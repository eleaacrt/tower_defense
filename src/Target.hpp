#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Map.hpp"
// #include "Config/ConfigTarget.hpp"

class Map;

class Target
{
public:
    Target();
    ~Target(){};

    std::string m_Type;
    int m_PointsVie;
    float m_Speed;
    int m_Value;
    unsigned int m_texture_file;
    std::pair<int, int> m_Position;

    void initTarget(Map map, std::unordered_map<std::string, GLuint> textures);
    void update();
    void move(Map map);
    void setStartPosition(std::vector<std::pair<int, int>> startPosition);

private:
    double m_previousTime{};
    double m_translate{};
    int currentNodeIndex;
    int occurence = 0;
    std::pair<int, int> current_pos;
};
