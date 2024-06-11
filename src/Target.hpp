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
    std::string m_texture_file;
    std::pair<int, int> m_Position;
    bool m_isDead = false;
    bool m_isArrived = false;

    void initTarget(Map map, std::unordered_map<std::string, GLuint> textures);
    void update();
    void move(Map map, std::unordered_map<std::string, GLuint> textures);

private:
    int randomIndex;
    double m_previousTime{};
    double m_translate{};
    int currentNodeIndex;
    std::pair<int, int> current_pos;
};
