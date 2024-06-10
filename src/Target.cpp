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
    m_Speed = 2;
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

void Target::initTarget(Map map, std::unordered_map<std::string, GLuint> textures)
{
    ItdTarget itdTarget;
    itdTarget.read_itd_target("data/itd_target.itd");

    m_texture_file = textures["ghost.png"];

    map.get_in_out_coordonnees();
    // setStartPosition(map.in_tiles_coordonnees);
    // Log::Debug("in_tiles_coordonnees: " + std::to_string(map.in_tiles_coordonnees.size()));
    m_Position = map.in_tiles_coordonnees[0];
    currentNodeIndex = map.all_shorter_path[0].size() - 2;
    // Log::Debug("m_Position: " + std::to_string(m_Position.first) + " " + std::to_string(m_Position.second));
}

void Target::update()
{
    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - m_previousTime};
    m_previousTime = currentTime;

    m_translate += m_Speed * elapsedTime;
}

void Target::move(Map map)
{

    std::pair node_pos = {map.all_shorter_path[0][currentNodeIndex].m_Position.first, (map.m_Height - map.all_shorter_path[0][currentNodeIndex].m_Position.second - 1)};

    std::pair dist = {
        abs(node_pos.first - m_Position.first),
        abs(node_pos.second - m_Position.second)};

    // step pour savoir si on avance ou on recule
    int step;
    if ((node_pos.first - m_Position.first) > 0 || (node_pos.second - m_Position.second) > 0)
    {
        step = 1;
    }
    else
    {
        step = -1;
    }

    Log::Debug("m_Position: " + std::to_string(m_Position.first) + " " + std::to_string(m_Position.second));
    Log::Debug("node_pos: " + std::to_string(node_pos.first) + " " + std::to_string(node_pos.second));

    glPushMatrix();

    if (currentNodeIndex < 0)
    {
        // Log::Error("currentNodeIndex: " + std::to_string(currentNodeIndex));
        return;
    }

    // on parcourt selon les X
    else if (abs(node_pos.first - m_Position.first) != 0)
    {
        if (m_translate < dist.first)
        {
            glTranslatef(m_translate * step, 0, 0);
            // m_Position.first += m_translate * step;
        }
        else
        {
            m_translate = 0;
            m_Position = node_pos;
            currentNodeIndex--;
        }
    }

    // on parcourt selon les Y
    else if (abs(node_pos.second - m_Position.second) != 0)
    {
        if (m_translate < dist.second)
        {
            glTranslatef(0, m_translate * step, 0);
            // m_Position.second += m_translate * step;
        }
        else
        {
            m_translate = 0;
            m_Position = node_pos;
            currentNodeIndex--;
        }
    }

    // else
    // {
    //     Log::Debug("IM INNNN");
    //     m_translate = 0;
    //     currentNodeIndex = currentNodeIndex - 1;
    //     m_Position = {map.all_shorter_path[0][currentNodeIndex].m_Position.first, (map.m_Height - map.all_shorter_path[0][currentNodeIndex].m_Position.second - 1)};
    // }

    Log::Debug("m_Position: " + std::to_string(m_Position.first) + " " + std::to_string(m_Position.second));
    glTranslatef((m_Position.first - map.m_Width / 2), (m_Position.second - map.m_Height / 2), 0);

    draw_quad_with_texture(m_texture_file);
    // draw_quad();
    glPopMatrix();
}
