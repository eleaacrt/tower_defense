#include "Target.hpp"
#include "Config/ConfigTarget.hpp"
#include "Map.hpp"

#include "GLHelpers.hpp"

Target::Target()
{
    m_Type = "target";
    m_PointsVie = 0;
    m_Speed = 2;
    m_Value = 0;
    m_Position = std::make_pair(0, 0);
};

void Target::initTarget(Map map, std::unordered_map<std::string, GLuint> textures)
{
    map.get_in_out_coordonnees();

    int nb_in = map.in_tiles_ID.size();
    randomIndex = rand() % nb_in;
    m_Position = map.in_tiles_coordonnees[randomIndex];

    currentNodeIndex = map.all_shorter_path[randomIndex].size() - 2;
}

void Target::update()
{
    const double currentTime{glfwGetTime()};
    m_previousTime = currentTime;

    m_translate += m_Speed * 0.01;
}

void Target::move(Map map, std::unordered_map<std::string, GLuint> textures)
{

    std::pair node_pos = {map.all_shorter_path[randomIndex][currentNodeIndex].m_Position.first, (map.m_Height - map.all_shorter_path[randomIndex][currentNodeIndex].m_Position.second - 1)};

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

    glPushMatrix();

    if (currentNodeIndex < 0)
    {
        m_isArrived = true;
        return;
    }

    // on parcourt selon les X
    else if (abs(node_pos.first - m_Position.first) != 0)
    {
        if (m_translate < dist.first)
        {
            glTranslatef(m_translate * step, 0, 0);
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
        }
        else
        {
            m_translate = 0;
            m_Position = node_pos;
            currentNodeIndex--;
        }
    }

    glTranslatef((m_Position.first - map.m_Width / 2), (m_Position.second - map.m_Height / 2), 0);
    // Log::Debug("Position : " + std::to_string(m_Position.first) + " " + std::to_string(m_Position.second));
    draw_quad_with_texture(textures[m_texture_file]);
    // draw_quad();
    glPopMatrix();
}
