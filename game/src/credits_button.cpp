#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>
#include <bitset>

#include "credits_button.h"
#include "main_menu.h"
#include "luascript.h"
#include <vector>

SoMTD::CreditsButton::CreditsButton(ijengine::Level *l) :
        m_menu_level(l)
{
        m_texture = ijengine::resources::get_texture("button/credits_black.png");
        m_mouseover_texture = ijengine::resources::get_texture("button/credits_white.png");
        m_x = 910;
        m_y = 450;
        ijengine::event::register_listener(this);
}

SoMTD::CreditsButton::~CreditsButton()
{
        ijengine::event::unregister_listener(this);
}

void
SoMTD::CreditsButton::update_self(unsigned, unsigned)
{
}

bool
SoMTD::CreditsButton::on_event(const ijengine::GameEvent& event)
{
        double x_pos = event.get_property<double>("x");
        double y_pos = event.get_property<double>("y");

        if (x_pos >= m_x && x_pos<m_x+m_texture->w() && y_pos>m_y && y_pos<m_y+m_texture->h()) {
                if (event.id() == SoMTD::MOUSEOVER) {
                        m_mouseover = true;
                } else if (event.id() == SoMTD::CLICK) {
                        dynamic_cast<SoMTD::MainMenu*>(m_menu_level)->update_next_level("menucredits");
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
SoMTD::CreditsButton::draw_self(ijengine::Canvas *c, unsigned, unsigned)
{
        if (m_mouseover) {
                c->draw(m_mouseover_texture.get(), m_x, m_y);
        } else  {
                c->draw(m_texture.get(), m_x, m_y);
        }
}

void
SoMTD::CreditsButton::draw_self_after(ijengine::Canvas *c, unsigned, unsigned)
{
}
