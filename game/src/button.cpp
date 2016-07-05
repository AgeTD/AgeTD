#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>
#include <bitset>

#include "button.h"
#include <vector>

SoMTD::Button::Button(std::string texture_name, unsigned id, int x, int y, std::string mtexture, std::string button_tower_texture, Player *m, int myp, std::vector<int> *args) :
    m_texture(ijengine::resources::get_texture(texture_name)),
    m_id(id),
    m_x(x),
    m_y(y),
    m_mouseover_texture(ijengine::resources::get_texture(mtexture)),
    m_button_tower_texture(ijengine::resources::get_texture(button_tower_texture)),
    m_player(m)
{
    set_priority(myp);
    m_mouseover = false;
    m_menu_level = nullptr;
    m_infos = args;
    ijengine::event::register_listener(this);
}

SoMTD::Button::~Button()
{
    delete m_infos;
    ijengine::event::unregister_listener(this);
}

void
SoMTD::Button::update_self(unsigned, unsigned)
{
}


bool
SoMTD::Button::on_event(const ijengine::GameEvent& event)
{
    if (event.id() == SoMTD::MOUSEOVER) {
        double x_pos = event.get_property<double>("x");
        double y_pos = event.get_property<double>("y");

        if (x_pos >= m_x && x_pos<m_x+m_texture->w() && y_pos>m_y && y_pos<m_y+m_texture->h()) {
            m_mouseover = true;
        } else {
            m_mouseover = false;
        }
    } else if (event.id() == SoMTD::CLICK) {
        double x_pos = event.get_property<double>("x");
        double y_pos = event.get_property<double>("y");

        if (x_pos >= m_x && x_pos<m_x+m_texture->w() && y_pos>m_y && y_pos<m_y+m_texture->h()) {
            //m_id 0 Zeus, m_id 1 poseidon, m_id 2 hades
            if (m_id < 0xF) {
                printf("Ta aqui -- m_id %d\n", m_id);
                m_player->state = SoMTD::Player::PlayerState::OPENED_TOWER_PANEL;
                m_player->open_tower_panel(m_id);

                return true;
            }

            int last_bit_button;
            int last_bit_panel;
            int desired_tower;
            bool result1;
            std::bitset<12> upgrade_state;
            switch (m_id) {
                case 1000:
                    m_menu_level->finish();
                    return true;
                    break;

                case 1002:
                    m_menu_level->exit_game();
                  break;

                case 0x2000:
                case 0x2001:
                case 0x2002:
                case 0x2003:
                    if (m_player->state == Player::PlayerState::OPENED_TOWER_PANEL) {
                        printf("Ta criando\n");
                        upgrade_state = (*m_infos)[1];
                        result1 = (*m_infos)[1] & m_player->upgrade_state().to_ulong();
                        if ((m_player->gold() >= (*m_infos)[0]) and result1) {
                            m_player->state = Player::PlayerState::HOLDING_BUILD;
                            last_bit_button = (m_id & 0xF);
                            last_bit_panel = m_player->tower_panel_id() & 0xF;
                            if (last_bit_panel) {
                                last_bit_panel = last_bit_panel << 4;
                            }
                            desired_tower = last_bit_panel | last_bit_button;
                            m_player->update_desired_tower(desired_tower, (*m_infos)[0]);
                        } else {
                            printf("not enough gold or not requirements meet..\n");
                        }
                    }
                    break;

                case 0x3000:
                case 0x3001:
                case 0x3002:
                    last_bit_button = (m_id & 0xF);
                    upgrade_state.reset();
                    upgrade_state.set(1+last_bit_button);
                    if (m_player->gold() >= (*m_infos)[0] && ((*m_infos)[1] & m_player->upgrade_state().to_ulong())) {
                        m_player->research(upgrade_state);
                        m_player->discount_gold((*m_infos)[0]);
                    } else {
                        printf("not enough gold or not met requirements..\n");
                    }
                    break;

                default:
                    break;
            }
        }
    }
    return false;
}

void
SoMTD::Button::draw_self(ijengine::Canvas *c, unsigned, unsigned)
{
    if (m_id >= 0x2000 && m_id < 0x2100) {
        if (m_player->state == SoMTD::Player::PlayerState::OPENED_TOWER_PANEL) {
            if (m_mouseover) {
                    c->draw(m_mouseover_texture.get(), m_x, m_y);

            }
            else{
                c->draw(m_texture.get(), m_x, m_y);
            }
            /*switch (m_id) {
                printf("IIIIDTa aqui -- m_id %d\n", m_id);
                case 2:
                    
                     break;
            }
            */
            c->draw(m_button_tower_texture.get(), m_x+30, m_y+15);
        }
    } else {
        if (m_mouseover) {
            c->draw(m_mouseover_texture.get(), m_x, m_y);
        } else  {
            c->draw(m_texture.get(), m_x, m_y);
        }
    }
}

void
SoMTD::Button::set_menu_level(SoMTD::MenuLevel* ml)
{
    m_menu_level = ml;
}

void
SoMTD::Button::draw_self_after(ijengine::Canvas *c, unsigned, unsigned)
{
    if (m_id >= 0x2000 && m_id < 0x2100 && m_player->state == SoMTD::Player::PlayerState::OPENED_TOWER_PANEL) {
        auto font = ijengine::resources::get_font("Inconsolata-Regular.ttf", 20);
        c->set_font(font);
        std::ostringstream convert;
        std::string expression;
        expression = "";
        convert << (*m_infos)[0];
        expression.append(convert.str());
        c->draw(expression, m_x+50, m_y+90);
    }
}
