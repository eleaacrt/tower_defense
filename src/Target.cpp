#include "Target.hpp"
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLHelpers.hpp"

Target::Target()
{
    m_Type = "";
    m_PointsVie = 0;
    m_Speed = 0;
    m_Value = 0;
}

void Target::updatePostion(std::pair<int, int> newPosition)
{
    m_Position = newPosition;
}

// void Target::move()
// {
//     std::pair<int, int> pos = m_Position;
//     for (int i = 0; i < m_Speed; i++)
//     {
//         pos.first += 1;
//         glPushMatrix();
//         glTranslatef(pos.first, pos.second, 0);
//         draw_quad();
//         glPopMatrix();
//     }
// }
