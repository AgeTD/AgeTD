#ifndef SOMTD_OPTIONS_BUTTON_H
#define SOMTD_OPTIONS_BUTTON_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/level.h>

#include "player.h"
#include "menu_level.h"
#include "level_changer_button.h"

#include <memory>
#include <vector>

namespace SoMTD {
        class OptionsButton : public LevelChangerButton {
        public:
                OptionsButton(ijengine::Level *current_level);
                ~OptionsButton();

                std::string next_level() const;
                std::string audio() const;
                int x() const;
                int y() const;
                std::shared_ptr<ijengine::Texture> texture() const;
                std::shared_ptr<ijengine::Texture> mouseover_texture() const;
                void transition();

        private:
                ijengine::Level *m_menu_level;
        };
}

#endif
