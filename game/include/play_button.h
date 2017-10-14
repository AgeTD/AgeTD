#ifndef SOMTD_PLAY_BUTTON_H
#define SOMTD_PLAY_BUTTON_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/level.h>

#include "player.h"
#include "menu_level.h"

#include <memory>
#include <vector>

namespace SoMTD {
        class PlayButton : public ijengine::GameObject, public ijengine::GameEventsListener {
        public:
                PlayButton(ijengine::Level *current_level);
                ~PlayButton();

                void draw_self(ijengine::Canvas *canvas, unsigned now, unsigned last);
                void draw_self_after(ijengine::Canvas*, unsigned, unsigned);
                bool on_event(const ijengine::GameEvent& event);
                void update_self(unsigned, unsigned);

        private:
                std::shared_ptr<ijengine::Texture> m_texture;
                int m_x;
                int m_y;
                bool m_mouseover;
                std::shared_ptr<ijengine::Texture> m_mouseover_texture;
                Player *m_player;
                int m_w;
                int m_h;
                int m_start;
                bool m_done;
                int m_priority;
                ijengine::Level *m_menu_level;
                std::vector<int> *m_infos;
                std::string m_description;
        };
}

#endif
