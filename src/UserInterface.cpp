#include "Config/ConfigTarget.hpp"

#include "UserInterface.hpp"
#include "GLHelpers.hpp"
#include "Map.hpp"
#include <iostream>
#include <string>

UserInterface::UserInterface()
{
    get_tower_positions = {};
}

void UserInterface::load_life_bar(int lifes_max, int all_lifes, int lifes, std::unordered_map<std::string, GLuint> textures, bool &is_game_over)
{
    glPushMatrix();
    glTranslatef(-(map.m_Width / 2), (map.m_Height / 2) + 2, 0);
    glScalef(1, 1.1, 1);

    lifes = all_lifes + lifes;

    for (int i = 0; i < lifes_max; i++)
    {
        if (i < (lifes_max - lifes))
        {
            draw_quad_with_texture(textures["life_color.png"]);
        }
        else
        {
            draw_quad_with_texture(textures["life_bw.png"]);
        }
        glTranslatef(1.2, 0, 0);
    }
    glPopMatrix();

    if (lifes == lifes_max)
    {
        is_game_over = true;
    }
}

void UserInterface::load_money(int &_width, int &_height, float viewSize, int money, std::unordered_map<std::string, GLuint> textures)
{
    // glPushMatrix();
    // glTranslatef(((map.m_Width / 2) - 3), (map.m_Height / 2) + 2, 0);
    // glScalef(1, 1, 1);
    // draw_quad_with_texture(textures["piece.png"]);
    // glPopMatrix();

    std::string money_str = "Money : " + std::to_string(money) + " $";
    const char *money_c_str = money_str.c_str();
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_32);
    TextRenderer.Label(money_c_str, 100, 150, SimpleText::LEFT);
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::game_over(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures)
{
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_160);
    TextRenderer.Label("Game Over :(", _width / 2, (_height / 2), SimpleText::CENTER);
    TextRenderer.SetTextSize(SimpleText::SIZE_32);
    TextRenderer.Label("click on [esc] to quit", _width / 2, (_height / 2) + 50, SimpleText::CENTER);
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::pause(int &_width, int &_height)
{
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_160);
    TextRenderer.Label("Pause", _width / 2, (_height / 2), SimpleText::CENTER);
    TextRenderer.SetTextSize(SimpleText::SIZE_32);
    TextRenderer.Label("click on [esc] to quit", _width / 2, (_height / 2) + 50, SimpleText::CENTER);
    TextRenderer.Label("click on [space] to restart", _width / 2, (_height / 2) + 100, SimpleText::CENTER);
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::win(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures)
{
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_160);
    TextRenderer.Label("Victory !", _width / 2, (_height / 2), SimpleText::CENTER);
    TextRenderer.SetTextSize(SimpleText::SIZE_32);
    TextRenderer.Label("click on [esc] to quit", _width / 2, (_height / 2) + 50, SimpleText::CENTER);
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::towers_to_select(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures, ItdTower ItdTower, float _viewSize)
{
    glPushMatrix();
    glTranslatef(-(map.m_Width), 0, 0);

    for (size_t i = 0; i < ItdTower.allTowers.size(); i++)
    {
        glPushMatrix();
        glTranslatef(0, (i * 2), 0);
        glScalef(1, 1, 1);

        draw_quad_with_texture(textures[ItdTower.allTowers[i].m_TextureFile]);
        glPopMatrix();

        float pos_x_1 = (-(map.m_Width)) - 0.5;
        float pos_y_1 = (i * 2) - 0.5;
        // Log::Debug("Position : x1 : " + std::to_string(pos_x_1) + ", x2 : " + std::to_string(pos_y_1));
        std::pair pos_1 = std::make_pair(pos_x_1, pos_y_1);

        float pos_x_2 = (-(map.m_Width)) + 0.5;
        float pos_y_2 = (i * 2) + 0.5;
        // Log::Debug("Position : x1 : " + std::to_string(pos_x_2) + ", x2 : " + std::to_string(pos_y_2));
        std::pair pos_2 = std::make_pair(pos_x_2, pos_y_2);

        get_tower_positions.push_back(std::make_pair(pos_1, pos_2));
    }

    glPopMatrix();

    // glPushMatrix();
    // glTranslatef(-(map.m_Width), -1.5, 0);
    // glScalef(2, 2, 2);

    // draw_quad_with_texture(textures["tower1.png"]);
    // glTranslatef(0, 1.5, 0);
    // draw_quad_with_texture(textures["tower2.png"]);
    // glPopMatrix();
}

void UserInterface::load_infos_targets(std::vector<Target> targets, int app_current_monster_index)
{
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_16);
    for (int i = 0; i < app_current_monster_index; i++)
    {
        std::string pv_str = "pv : " + std::to_string(targets[i].m_PointsVie);
        const char *pv = pv_str.c_str();
        // Log::Debug("Target : " + targets[i].m_Type + " " + std::to_string(targets[i].m_Position.first) + " " + std::to_string(targets[i].m_Position.second) + " PV : " + std::to_string(targets[i].m_PointsVie));
        TextRenderer.Label(pv, 100, 200 + (i * 20), SimpleText::LEFT);
    }
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::show_level(int level)
{
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_32);
    std::string level_str = "Level : " + std::to_string(level);
    const char *level_c_str = level_str.c_str();
    TextRenderer.Label(level_c_str, 100, 100, SimpleText::LEFT);
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::controle_text(int &_width, int &_height)
{
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_16);
    TextRenderer.Label("click on [esc] to quit", _width / 2, _height - 200, SimpleText::CENTER);
    TextRenderer.Label("click on [space] to pause", _width / 2, _height - 175, SimpleText::CENTER);
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}