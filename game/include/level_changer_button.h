#ifndef SOMTD_LEVEL_CHANGER_BUTTON_H
#define SOMTD_LEVEL_CHANGER_BUTTON_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/level.h>

#include "menu_level.h"

#include <memory>
#include <vector>

namespace SoMTD {
        class LevelChangerButton : public ijengine::GameObject, public ijengine::GameEventsListener {
        public:
                virtual ~LevelChangerButton() = default;
                virtual std::string next_level() const = 0;
                virtual std::string audio() const = 0;
                virtual int x() const = 0;
                virtual int y() const = 0;
                virtual std::shared_ptr<ijengine::Texture> texture() const = 0;
                virtual std::shared_ptr<ijengine::Texture> mouseover_texture() const = 0;
                virtual void transition() = 0;

                void draw_self(ijengine::Canvas *canvas, unsigned now, unsigned last);
                void draw_self_after(ijengine::Canvas*, unsigned, unsigned);
                bool on_event(const ijengine::GameEvent& event);
                void update_self(unsigned, unsigned);

        private:
                int m_x;
                int m_y;
                bool m_mouseover;
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
