#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>

#include "level_changer_button.h"
#include "main_menu.h"

void
SoMTD::LevelChangerButton::update_self(unsigned, unsigned)
{
}

bool
SoMTD::LevelChangerButton::on_event(const ijengine::GameEvent& event)
{
        double x_pos = event.get_property<double>("x");
        double y_pos = event.get_property<double>("y");

        if (x_pos >= x() && x_pos<x()+texture()->w() && y_pos>y() && y_pos<y()+texture()->h()) {
                if (event.id() == SoMTD::MOUSEOVER) {
                        m_mouseover = true;
                } else if (event.id() == SoMTD::CLICK) {
                        transition();
                        return true;
                }
        } else {
                m_mouseover = false;
        }
        return false;
}

void
SoMTD::LevelChangerButton::draw_self(ijengine::Canvas *c, unsigned, unsigned)
{
        if (m_mouseover) {
                c->draw(mouseover_texture().get(), x(), y());
        } else  {
                c->draw(texture().get(), x(), y());
        }
}

void
SoMTD::LevelChangerButton::draw_self_after(ijengine::Canvas *c, unsigned, unsigned)
{
}
