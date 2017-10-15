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
        ijengine::event::register_listener(this);
}

SoMTD::CreditsButton::~CreditsButton()
{
        ijengine::event::unregister_listener(this);
}

std::string
SoMTD::CreditsButton::audio() const
{
        return "res/sound_efects/menu-button.ogg";
}

std::string
SoMTD::CreditsButton::next_level() const
{
        return "menucredits";
}

int
SoMTD::CreditsButton::x() const
{
        return 910;
}

int
SoMTD::CreditsButton::y() const
{
        return 450;
}

std::shared_ptr<ijengine::Texture>
SoMTD::CreditsButton::texture() const
{
        return ijengine::resources::get_texture("button/credits_black.png");
}

std::shared_ptr<ijengine::Texture>
SoMTD::CreditsButton::mouseover_texture() const
{
        return ijengine::resources::get_texture("button/credits_white.png");
}

using SoMTD::MainMenu;

void
SoMTD::CreditsButton::transition()
{
        MainMenu* current_level = dynamic_cast<MainMenu*>(m_menu_level);
        current_level->update_next_level(next_level());
        current_level->finish();
        ijengine::audio::play_sound_effect(audio());
}
