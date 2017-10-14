#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>
#include <bitset>

#include "exit_button.h"
#include "main_menu.h"
#include "luascript.h"
#include <vector>

SoMTD::ExitButton::ExitButton(ijengine::Level *l) :
        m_menu_level(l)
{
        m_texture = ijengine::resources::get_texture("button/exit_black.png");
        m_mouseover_texture = ijengine::resources::get_texture("button/exit_white.png");
        m_x = 945;
        m_y = 535;
        ijengine::event::register_listener(this);
}

SoMTD::ExitButton::~ExitButton()
{
        ijengine::event::unregister_listener(this);
}

void
SoMTD::ExitButton::update_self(unsigned, unsigned)
{
}

bool
SoMTD::ExitButton::on_event(const ijengine::GameEvent& event)
{
        double x_pos = event.get_property<double>("x");
        double y_pos = event.get_property<double>("y");

        if (x_pos >= m_x && x_pos<m_x+m_texture->w() && y_pos>m_y && y_pos<m_y+m_texture->h()) {
                if (event.id() == SoMTD::MOUSEOVER) {
                        m_mouseover = true;
                } else if (event.id() == SoMTD::CLICK) {
                        dynamic_cast<SoMTD::MainMenu*>(m_menu_level)->update_next_level("");
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
SoMTD::ExitButton::draw_self(ijengine::Canvas *c, unsigned, unsigned)
{
        if (m_mouseover) {
                c->draw(m_mouseover_texture.get(), m_x, m_y);
        } else  {
                c->draw(m_texture.get(), m_x, m_y);
        }
}

void
SoMTD::ExitButton::draw_self_after(ijengine::Canvas *c, unsigned, unsigned)
{
}
