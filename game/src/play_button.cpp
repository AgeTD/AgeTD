#include <iostream>

#include "game.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>

#include "play_button.h"
#include "main_menu.h"

SoMTD::PlayButton::PlayButton(ijengine::Level *l) :
        m_menu_level(l)
{
        ijengine::event::register_listener(this);
}

SoMTD::PlayButton::~PlayButton()
{
        ijengine::event::unregister_listener(this);
}

std::string
SoMTD::PlayButton::audio() const
{
        return "res/sound_efects/menu-button.ogg";
}

std::string
SoMTD::PlayButton::next_level() const
{
        return "map001";
}

int
SoMTD::PlayButton::x() const
{
        return 943;
}

int
SoMTD::PlayButton::y() const
{
        return 380;
}

std::shared_ptr<ijengine::Texture>
SoMTD::PlayButton::texture() const
{
        return ijengine::resources::get_texture("button/play_black.png");
}

std::shared_ptr<ijengine::Texture>
SoMTD::PlayButton::mouseover_texture() const
{
        return ijengine::resources::get_texture("button/play_white.png");
}

using SoMTD::MainMenu;

void
SoMTD::PlayButton::transition()
{
        MainMenu* current_level = dynamic_cast<MainMenu*>(m_menu_level);
        current_level->update_next_level(next_level());
        current_level->finish();
        ijengine::audio::play_sound_effect(audio());
}
