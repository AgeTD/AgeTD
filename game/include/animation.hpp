// Copyright (C) 2016 Dylan Guedes
//
// This file is part of SoMTD.
//
// SoMTD is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SoMTD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SoMTD. If not, see <http://www.gnu.org/licenses/>.

#ifndef GAME_INCLUDE_ANIMATION_HPP_
#define GAME_INCLUDE_ANIMATION_HPP_

#include <ijengine/canvas.h>
#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/rectangle.h>

#include <string>
#include <utility>
#include <memory>

#include "./game.h"

namespace SoMTD {
class Animation {
 public:
  enum StateStyle {
    STATE_PER_COLUMN = 0x00,
    STATE_PER_LINE = 0x01,
    EVERYTHING_PER_LINE = 0x02,
    TOTAL = 0x03
  };

  enum DirectionState {
    DIRECTION_RIGHT = 0x00,
    DIRECTION_LEFT = 0x01
  };

  Animation(int new_grid_x, int new_grid_y,
      std::string new_file_path,
      StateStyle new_state_style,
      int new_frame_per_state, int new_total_states);

  ~Animation();
  void draw(ijengine::Canvas *c, unsigned, unsigned);
  void draw_self_after(ijengine::Canvas *c, unsigned, unsigned);
  void next_frame();
  void update_texture(std::string new_path);
  void update_screen_position(std::pair<int, int> new_pos);
  void update_frame(int now);
  void update_tile(int _x, int _y);
  void update_display(double _x, double _y);

  Point screen_position() const;
  std::shared_ptr<ijengine::Texture> texture() const;
  int width() const;
  int actual_state() const;
  int height() const;
  int actual_frame() const;
  int frame_per_state() const;
  void update_direction(SoMTD::Animation::DirectionState newstate);
  Tile coords() const;
  Point display() const;

 private:
  Tile m_coords;
  Point m_display;
  std::string m_file_path;
  int m_frame_per_state;
  int m_actual_state;
  int m_actual_frame;
  int m_total_states;
  StateStyle m_state_style;
  std::shared_ptr<ijengine::Texture> m_texture;
  ijengine::Rectangle *m_frame; // TODO: needed?
  SoMTD::Animation::DirectionState m_actual_direction; // TODO: needed?
  int m_width;
  int m_height;
};
}  // namespace SoMTD

#endif  // GAME_INCLUDE_ANIMATION_HPP_
