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

void UserInterface::load_life_bar(int lifes_max, int lifes, std::unordered_map<std::string, GLuint> textures)
{
    glPushMatrix();
    glTranslatef(-(map.m_Width / 2), (map.m_Height / 2) + 2, 0);
    glScalef(1, 1.1, 1);

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
}

void UserInterface::load_money(int &_width, int &_height, float viewSize, int money, std::unordered_map<std::string, GLuint> textures)
{
    glPushMatrix();
    glTranslatef(((map.m_Width / 2) - 3), (map.m_Height / 2) + 2, 0);
    glScalef(1, 1, 1);
    draw_quad_with_texture(textures["piece.png"]);
    glPopMatrix();

    const char *money_str = std::to_string(money).c_str();
    SimpleText TextRenderer{};
    TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.SetTextSize(SimpleText::SIZE_48);
    TextRenderer.Label(money_str, (_width / 2) + (viewSize * map.m_Width / 2), ((_height / 2) - (viewSize * map.m_Height / 2)) - (2 * viewSize), SimpleText::CENTER);
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
    TextRenderer.EnableBlending(true);
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    TextRenderer.Render();
}

void UserInterface::towers_to_select(int &_width, int &_height, std::unordered_map<std::string, GLuint> textures, ItdTower ItdTower, float _viewSize)
{
    // SimpleText TextRenderer{};
    // TextRenderer.SetColor(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    // TextRenderer.SetTextSize(SimpleText::SIZE_64);
    // TextRenderer.Label("Select a tower", 30, (_height / 2) - 200, SimpleText::LEFT);
    // TextRenderer.EnableBlending(true);
    // TextRenderer.SetColor(SimpleText::TEXT_COLOR, 1.f, 0.f, 0.f, 1.f);
    // TextRenderer.Render();

    // on décale de (_width /2) et (_height / 2) (centre de la fenêtre)
    // on décalde de - la largeur de la map (milieu à gauche)
    // pour toutes les tours de (- nbtours / 2) à (nbtours / 2)
    // -> on translate vers en hauteur de 1.5 * nb_tours
    // -> on dessine la tour

    glPushMatrix();
    glTranslatef(-(map.m_Width), 0, 0);

    for (size_t i = 0; i < ItdTower.allTowers.size(); i++)
    {
        glPushMatrix();
        glTranslatef(0, i * 2, 0);
        glScalef(1, 1, 1);
        // Log::Debug("i + nb_tower/2: " + std::to_string(i));
        // Log::Debug("texture : " + ItdTower.allTowers[i].m_TextureFile);
        draw_quad_with_texture(textures[ItdTower.allTowers[i].m_TextureFile]);
        glPopMatrix();

        int pos_x_1 = (_width / 2) - (map.m_Width * (_height / _viewSize)) + (_height / _viewSize);
        // Log::Debug("pos_x_1 : " + std::to_string(pos_x_1));
        // Log::Debug("width : " + std::to_string(_width));
        // Log::Debug("height : " + std::to_string(_height));

        int pos_y_1 = (_height / 2) - (i * 2 * (_height / _viewSize)) + (_height / _viewSize);
        // Log::Debug("pos_y_1 : " + std::to_string(pos_y_1));
        std::pair pos_1 = std::make_pair(pos_x_1, pos_y_1);

        int pos_x_2 = (_width / 2) - (map.m_Width * (_height / _viewSize)) - (_height / _viewSize);
        // Log::Debug("pos_x_2 : " + std::to_string(pos_x_2));
        int pos_y_2 = (_height / 2) - (i * 2 * (_height / _viewSize)) - (_height / _viewSize);
        // Log::Debug("pos_y_2 : " + std::to_string(pos_y_2));
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
