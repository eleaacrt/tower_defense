#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Node.hpp"

// #include "Config/ConfigTarget.hpp"

class Target
{
public:
    Target();

    std::string m_Type;
    int m_PointsVie;
    float m_Speed;
    int m_Value;
    unsigned int m_texture_file;
    std::pair<int, int> m_Position;

    void initTarget();
    void update();
    void move(int x, int y);

private:
    double m_previousTime{};
    double m_translate{};
};
