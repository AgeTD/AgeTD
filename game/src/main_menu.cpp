#include "main_menu.h"
#include "play_button.h"
#include "exit_button.h"
#include "options_button.h"
#include "credits_button.h"
#include <ijengine/engine.h>
#include <ijengine/event.h>
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/canvas.h>
#include <ijengine/game_events_listener.h>
#include <string>
#include <memory>
#include "./player.hpp"
#include <iostream>

SoMTD::MainMenu::MainMenu() : m_done(false)
{
        m_audio = "res/sound_efects/music/somtd-menu.ogg";
        m_next = "map001";
        m_texture = ijengine::resources::get_texture("Menu.png");
        load_buttons();

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
SoMTD::MainMenu::on_event(const ijengine::GameEvent&)
{
        return false;
}

void
SoMTD::MainMenu::draw_self_after(ijengine::Canvas *, unsigned , unsigned )
{
}

void
SoMTD::MainMenu::draw_self(ijengine::Canvas *c, unsigned , unsigned )
{
        c->draw(m_texture.get(), 0, 0);
}

void
SoMTD::MainMenu::update_self(unsigned, unsigned)
{
}

void
SoMTD::MainMenu::load_buttons()
{
        add_child(new PlayButton(this));
        add_child(new ExitButton(this));
        add_child(new CreditsButton(this));
        add_child(new OptionsButton(this));
}

void
SoMTD::MainMenu::finish()
{
        m_done = true;
}

void
SoMTD::MainMenu::update_next_level(std::string next_map)
{
        m_next = next_map;
}
