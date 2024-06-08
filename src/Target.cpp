#include "Target.hpp"
#include "Config/ConfigTarget.hpp"
#include "Map.hpp"
// #include <sstream>
// #include <iostream>

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include "GLHelpers.hpp"

Target::Target()
{
    m_Type = "target";
    m_PointsVie = 0;
    m_Speed = 0;
    m_Value = 0;
    m_texture_file = 0;
    m_Position = std::make_pair(0, 0);
};

// void Target::setStartPosition(std::vector<std::pair<int, int>> startPosition)
// {
//     // récupérer une pair d'index aléatoire en fonction des entrées
//     int vectorSize = startPosition.size();
//     Log::Debug("vectorSize: " + std::to_string(vectorSize));
//     int randomIndex = rand() % vectorSize;
//     m_Position = startPosition[randomIndex - 1];
// }

void Target::initTarget()
{
    Map map;
    ItdTarget itdTarget;

    itdTarget.read_itd_target("data/itd_target.itd");

    std::vector<std::pair<int, int>> in_tiles = map.get_in(map.get_Tiles());
    // setStartPosition(in_tiles);
    m_Position = in_tiles[0];

    glPushMatrix();
    glTranslatef(m_Position.first, m_Position.second, 0);
    // draw_quad_with_texture(m_texture_file);
    // draw_quad();
    glPopMatrix();
}

void Target::update()
{
    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - m_previousTime};
    m_previousTime = currentTime;

    m_translate += m_Speed * elapsedTime;
}

void Target::move(int x, int y)
{
    initTarget();
    glPushMatrix();
    glTranslatef(x, y, 0);
    draw_quad();
    glPopMatrix();
}
