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
        ijengine::event::register_listener(this);
}

SoMTD::ExitButton::~ExitButton()
{
        ijengine::event::unregister_listener(this);
}

std::string
SoMTD::ExitButton::audio() const
{
        return "res/sound_efects/menu-button.ogg";
}

std::string
SoMTD::ExitButton::next_level() const
{
        return "";
}

int
SoMTD::ExitButton::x() const
{
        return 945;
}

int
SoMTD::ExitButton::y() const
{
        return 535;
}

std::shared_ptr<ijengine::Texture>
SoMTD::ExitButton::texture() const
{
        return ijengine::resources::get_texture("button/exit_black.png");
}

std::shared_ptr<ijengine::Texture>
SoMTD::ExitButton::mouseover_texture() const
{
        return ijengine::resources::get_texture("button/exit_white.png");
}

using SoMTD::MainMenu;

void
SoMTD::ExitButton::transition()
{
        MainMenu* current_level = dynamic_cast<MainMenu*>(m_menu_level);
        current_level->update_next_level(next_level());
        current_level->finish();
        ijengine::audio::play_sound_effect(audio());
}
