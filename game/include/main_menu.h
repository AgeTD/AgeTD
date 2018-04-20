#ifndef SOMTD_MAIN_MENU_H
#define SOMTD_MAIN_MENU_H

#include <memory>

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/game_object.h>

using ijengine::Canvas;
using std::string;

namespace SoMTD {
        class MainMenu : public ijengine::Level , public ijengine::GameEventsListener {
        public:
                MainMenu();
                ~MainMenu();
                bool done() const;
                string next() const;
                string audio() const;
                bool on_event(const ijengine::GameEvent& event);
                void load_buttons();
                bool m_done;
                void finish();
                void update_next_level(std::string next_map);

        protected:
                void update_self(unsigned now, unsigned last);
                void draw_self(Canvas *canvas, unsigned now, unsigned last);
                void draw_self_after(Canvas *, unsigned, unsigned);

        private:
                string m_next;
                string m_audio;
                std::shared_ptr<ijengine::Texture> m_texture;
        };
}

#endif
