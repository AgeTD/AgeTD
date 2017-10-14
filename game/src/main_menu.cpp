#include "main_menu.h"
#include <ijengine/engine.h>
#include <ijengine/event.h>
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/canvas.h>
#include <ijengine/game_events_listener.h>
#include <string>
#include <memory>
#include "player.h"

SoMTD::MainMenu::MainMenu() : m_done(false)
{
        m_audio = "res/sound_efects/music/somtd-menu.ogg";
        m_next = "map001";
        m_player = new SoMTD::Player();
        m_texture = ijengine::resources::get_texture("Menu.png");
        ijengine::event::register_listener(this);
}

SoMTD::MainMenu::~MainMenu()
{
        ijengine::event::unregister_listener(this);
}

std::string
SoMTD::MainMenu::next() const
{
        return m_next;
}

std::string
SoMTD::MainMenu::audio() const
{
        return m_audio;
}


bool
SoMTD::MainMenu::done() const
{
        return m_done;
}

bool
SoMTD::MainMenu::on_event(const ijengine::GameEvent& event)
{
        return false;
}

void
SoMTD::MainMenu::draw_self_after(ijengine::Canvas *c, unsigned a1, unsigned a2)
{
}

void
SoMTD::MainMenu::draw_self(ijengine::Canvas *c, unsigned a1, unsigned a2)
{
        c->draw(m_texture.get(), 0, 0);
}

void
SoMTD::MainMenu::update_self(unsigned, unsigned)
{
}
