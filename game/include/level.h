#ifndef SOMTD_LEVEL_H
#define SOMTD_LEVEL_H

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/game_events_listener.h>

#include <string>

#include <memory>

namespace SoMTD {
        class Level : public ijengine::Level, public ijengine::GameEventsListener {
        public:
                Level(std::string current_map_name, std::string next_map_name, std::string p_audio) {
                        m_level_name = current_map_name;
                        m_next = next_map_name;
                        m_audio = p_audio;
                }
                virtual ~Level() = default;
                void finish();
                void exit_game();
                void update_next_level(std::string next_map);
                std::string m_level_name="";

        protected:
                void draw_self(ijengine::Canvas *, unsigned, unsigned);
                void draw_self_after(ijengine::Canvas *, unsigned, unsigned);
                void update_self(unsigned now, unsigned last);
                bool on_event(const ijengine::GameEvent&);
                std::string audio() const;
                std::string next() const;
                Player *player() const;

        private:
                std::string m_next;
                std::string m_audio="";
                std::shared_ptr<ijengine::Texture> m_texture;
                void load_buttons();
        };
}

#endif
