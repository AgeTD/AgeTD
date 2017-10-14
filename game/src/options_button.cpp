#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>
#include <bitset>

#include "options_button.h"
#include "main_menu.h"
#include "luascript.h"
#include <vector>

SoMTD::OptionsButton::OptionsButton(ijengine::Level *l) :
        m_menu_level(l)
{
        m_texture = ijengine::resources::get_texture("menuopcoes.png");
        m_mouseover_texture = ijengine::resources::get_texture("menuopcoes.png");
        m_x = 8;
        m_y = 600;
        ijengine::event::register_listener(this);
}

SoMTD::OptionsButton::~OptionsButton()
{
        ijengine::event::unregister_listener(this);
}

void
SoMTD::OptionsButton::update_self(unsigned, unsigned)
{
}

bool
SoMTD::OptionsButton::on_event(const ijengine::GameEvent& event)
{
        double x_pos = event.get_property<double>("x");
        double y_pos = event.get_property<double>("y");

        if (x_pos >= m_x && x_pos<m_x+m_texture->w() && y_pos>m_y && y_pos<m_y+m_texture->h()) {
                if (event.id() == SoMTD::MOUSEOVER) {
                        m_mouseover = true;
                } else if (event.id() == SoMTD::CLICK) {
                        dynamic_cast<SoMTD::MainMenu*>(m_menu_level)->update_next_level("menuoptions");
                        dynamic_cast<SoMTD::MainMenu*>(m_menu_level)->finish();
                        ijengine::audio::play_sound_effect("res/sound_efects/menu-button.ogg");
                        return true;
                }
        } else {
                m_mouseover = false;
        }
        return false;
}

void
SoMTD::OptionsButton::draw_self(ijengine::Canvas *c, unsigned, unsigned)
{
        if (m_mouseover) {
                c->draw(m_mouseover_texture.get(), m_x, m_y);
        } else  {
                c->draw(m_texture.get(), m_x, m_y);
        }
}

void
SoMTD::OptionsButton::draw_self_after(ijengine::Canvas *c, unsigned, unsigned)
{
}
