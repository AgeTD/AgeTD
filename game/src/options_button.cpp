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
        ijengine::event::register_listener(this);
}

SoMTD::OptionsButton::~OptionsButton()
{
        ijengine::event::unregister_listener(this);
}


std::string
SoMTD::OptionsButton::audio() const
{
        return "res/sound_efects/menu-button.ogg";
}

std::string
SoMTD::OptionsButton::next_level() const
{
        return "menuoptions";
}

int
SoMTD::OptionsButton::x() const
{
        return 8;
}

int
SoMTD::OptionsButton::y() const
{
        return 600;
}

std::shared_ptr<ijengine::Texture>
SoMTD::OptionsButton::texture() const
{
        return ijengine::resources::get_texture("menuopcoes.png");
}

std::shared_ptr<ijengine::Texture>
SoMTD::OptionsButton::mouseover_texture() const
{
        return ijengine::resources::get_texture("menuopcoes.png");
}

using SoMTD::MainMenu;

void
SoMTD::OptionsButton::transition()
{
        MainMenu* current_level = dynamic_cast<MainMenu*>(m_menu_level);
        current_level->update_next_level(next_level());
        current_level->finish();
        ijengine::audio::play_sound_effect(audio());
}
