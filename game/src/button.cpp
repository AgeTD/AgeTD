#include <iostream>

#include "game.hpp"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>
#include <bitset>

#include "./player.hpp"
#include "button.h"
#include "luascript.h"
#include <vector>
#include <cmath>

SoMTD::Button::Button(std::string texture_name, unsigned id, int x, int y, std::string mtexture, int myp, std::vector<int> *args, std::string newdescription) :
    m_texture(ijengine::resources::get_texture(texture_name)),
    m_id(id),
    m_x(x),
    m_y(y),
    m_mouseover_texture(ijengine::resources::get_texture(mtexture))
{
    m_description = newdescription;
    set_priority(myp);
    m_mouseover = false;
    m_infos = args;
    ijengine::event::register_listener(this);
    m_menu_level = nullptr;
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
            if (m_id < 0xF) {
              player::get().state = SoMTD::player::PlayerState::OPENED_TOWER_PANEL;
              player::get().open_tower_panel(m_id);
              return true;
            }
            if (m_menu_level != nullptr && m_menu_level && m_menu_level->m_level_name == "menuoptions") {
                switch (m_id) {
                    case 40:
                        ijengine::audio::set_audio_volume(0.0);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;

                    case 41:
                        ijengine::audio::set_audio_volume(0.25);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;

                    case 42:
                        ijengine::audio::set_audio_volume(0.50);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;
                    case 43:
                        ijengine::audio::set_audio_volume(1.0);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;

                    case 44:
                        ijengine::audio::set_sound_effect_volume(0.0);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;
                    case 45:
                        ijengine::audio::set_sound_effect_volume(0.25);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;
                    case 46:
                        ijengine::audio::set_sound_effect_volume(0.50);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;
                    case 47:
                        ijengine::audio::set_sound_effect_volume(1.0);
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                        break;

                    default:
                        break;
                }
            }

            int last_bit_button;
            int desired_tower;
            bool result1;
            std::bitset<12> upgrade_state;
            switch (m_id) {
                case 0xf:
                    m_menu_level->update_next_level("menuoptions");
                    m_menu_level->finish();
                    return true;
                    break;

                case 1000:
                    m_menu_level->finish();
                    ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                    return true;
                    break;

                case 1001:
                    m_menu_level->update_next_level("menucredits");
                    m_menu_level->finish();
                    return true;
                    break;

                case 1002:
                    m_menu_level->exit_game();
                    ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                  break;

                case 0x2000:
                case 0x2001:
                case 0x2002:
                case 0x2003:
                    if (player::get().state == player::PlayerState::OPENED_TOWER_PANEL) {
                        upgrade_state = (*m_infos)[1];
                        result1 = (*m_infos)[1] & player::get().upgrade_state().to_ulong();
                        if ((player::get().gold() >= (*m_infos)[0]) and result1) {
                          player::get().state = player::PlayerState::HOLDING_BUILD;
                            desired_tower = m_id - 0x2000 + pow(16, player::get().tower_panel_id());
                            if (player::get().tower_panel_id() == 0) { 
                              desired_tower -= 1;
                            }
                            player::get().update_desired_tower(desired_tower, (*m_infos)[0]);
                        } else {
                            printf("not enough gold or not requirements meet..\n");
                            ijengine::audio::play_sound_effect("res/sound_efects/invalidaction.ogg");
                        }
                    }
                    break;

                case 0x3000:
                case 0x3001:
                case 0x3002:
                    last_bit_button = (m_id & 0xF);
                    upgrade_state.reset();
                    upgrade_state.set(1+last_bit_button);
                    if (player::get().gold() >= (*m_infos)[0] && ((*m_infos)[1] & player::get().upgrade_state().to_ulong())) {
                      player::get().research(upgrade_state);
                      player::get().discount_gold((*m_infos)[0]);
                    } else {
                        printf("not enough gold or not met requirements..\n");
                        ijengine::audio::play_sound_effect("res/sound_efects/invalidaction.ogg");
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
        if (player::get().state == SoMTD::player::PlayerState::OPENED_TOWER_PANEL) {
            if (m_mouseover)
                c->draw(m_mouseover_texture.get(), m_x, m_y);
            else
                c->draw(m_texture.get(), m_x, m_y);
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
SoMTD::Button::draw_self_after(ijengine::Canvas *c, unsigned, unsigned) {
  // TODO: rewrite this
  if (m_id >= 0x2000 && m_id < 0x2100 && player::get().state == SoMTD::player::PlayerState::OPENED_TOWER_PANEL) {
    // "it is a tower.."
    auto font = ijengine::resources::get_font("Inconsolata-Regular.ttf", 20);
    c->set_font(font);

    std::string tower_name = "towers/tower_";
    std::ostringstream convert;
    std::string expression;
    expression = "";
    convert << (*m_infos)[0];
    expression.append(convert.str());
    convert.clear();
    convert.str("");
    int panel_id = player::get().tower_panel_id();
    if (panel_id != 0)
      panel_id = 8 << player::get().tower_panel_id();
    panel_id |= (m_id & 0xF);

    if (player::get().tower_panel_id() == 0) {
      convert << m_id - 8192;
    } else {
      convert << pow(16, player::get().tower_panel_id()) - 8192 + m_id;
    }

    tower_name.append(convert.str());
    tower_name.append("_holding");
    tower_name.append(".png");
    c->draw(ijengine::resources::get_texture(tower_name).get(), m_x+15, m_y-10);

    c->draw(expression, m_x+50, m_y+90);
    if (m_mouseover) {
      int last_bit_button = (m_id & 0xF);
      int last_bit_panel = player::get().tower_panel_id() & 0xF;
      last_bit_panel = last_bit_panel << 4;
      int desired_tower = last_bit_panel | last_bit_button;
      LuaScript towers_list("lua-src/Tower.lua");
      std::string affix = "tower_";
      ostringstream convert2;
      convert2 << desired_tower;
      affix.append(convert2.str());

      c->draw(ijengine::resources::get_texture("towers/containertorre.png").get(), m_x - 70, m_y-180);
      c->draw(towers_list.get<std::string>((affix) + ".description").c_str(), m_x-50, m_y-120);
    }
  }
}
