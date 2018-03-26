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

#include <iostream>

#include "animation.hpp"
#include "./game.hpp"

/*
 * Class that handles sprite animation logic
 */

namespace SoMTD {
Animation::Animation(
    int _x,
    int _y,
    std::string _texture_path,
    StateStyle _state_style,
    int _frame_per_state,
    int _total_states) :
      m_coords(Tile { _x, _y }),
      m_display(tools::grid_to_isometric(_x, _y)),
      m_file_path(_texture_path),
      m_frame_per_state(_frame_per_state),
      m_actual_state(DIRECTION_RIGHT),
      m_actual_frame(0),
      m_total_states(_total_states),
      m_state_style(_state_style),
      m_texture(ijengine::resources::get_texture(_texture_path)) {

  if (_state_style == STATE_PER_COLUMN) {
    m_width = m_texture->w()/m_total_states;
    m_height = m_texture->h()/m_frame_per_state;
  } else if (_state_style == STATE_PER_LINE) {
    m_width = m_texture->w()/m_frame_per_state;
    m_height = m_texture->h()/m_total_states;
  } else if (_state_style == EVERYTHING_PER_LINE) {
    m_width = m_texture->w()/(m_total_states);
    m_width /= m_frame_per_state;
    m_height = m_texture->h();
  }
}

Animation::~Animation() { }

void
Animation::update_tile(int _x, int _y) {
  m_coords = Tile { _x, _y };
}

void
Animation::update_display(double _x, double _y) {
  m_display = Point { _x, _y };
}

int
Animation::actual_frame() const {
  return m_actual_frame;
}

void
Animation::update_frame(int now) {
  m_actual_frame = now;
}

void
Animation::next_frame() {
  update_frame(actual_frame() % frame_per_state() + 1);
}

int
Animation::actual_state() const {
  return m_actual_state;
}

void
Animation::draw(ijengine::Canvas *c, unsigned, unsigned) {
  ijengine::Rectangle rect(0, 0, m_width, m_height);
  if (m_state_style ==  STATE_PER_COLUMN) {
    // decrease one in actual_frame because the first index is 0
    rect.set_position(
        width()*actual_state(),
        height()*(actual_frame()-1));
  } else if (m_state_style == STATE_PER_LINE) {
    rect.set_position(
        width()*(actual_frame()-1),
        height()*actual_state());
  } else if (m_state_style == EVERYTHING_PER_LINE) {
    rect.set_position(
        ((m_actual_frame-1)*m_width)+(m_width*m_frame_per_state*m_actual_state),
        0);
  }

  m_texture = ijengine::resources::get_texture(m_file_path);

  if (
      // TODO: projectiles are not isometric - isolate this
      m_file_path == "projectiles/projetil_poseidon.png" ||
      m_file_path == "projectiles/projetil_caveira.png" ||
      m_file_path == "projectiles/projetil_zeus2.png") {
    c->draw(m_texture.get(), screen_position().x, screen_position().y);
  } else {
    c->draw(
        m_texture.get(),
        rect,
        screen_position().x+(100-m_width)/2,
        screen_position().y+81/2-m_height);
  }
}

[[deprecated]]
Point
Animation::screen_position() const {
  return m_display;
}

void
Animation::draw_self_after(ijengine::Canvas*, unsigned, unsigned) { }

void
Animation::update_texture(std::string new_path) {
  m_file_path = new_path;
  m_texture = ijengine::resources::get_texture(m_file_path);
}

std::shared_ptr<ijengine::Texture>
Animation::texture() const {
  return m_texture;
}

int
Animation::width() const {
  return m_width;
}

int
Animation::height() const {
  return m_height;
}

int
Animation::frame_per_state() const {
  return m_frame_per_state;
}

void
Animation::update_direction(SoMTD::Animation::DirectionState ds) {
  if (m_total_states >= static_cast<int>(ds)) {
    m_actual_state = static_cast<int>(ds);
  }
}

Point
Animation::display() const {
  return m_display; 
}

Tile
Animation::coords() const {
  return m_coords;
}

void
Animation::update_screen_position(std::pair<int, int> new_pos) {
  m_display = Point { static_cast<double>(new_pos.first), static_cast<double>(new_pos.second) };
}
}
