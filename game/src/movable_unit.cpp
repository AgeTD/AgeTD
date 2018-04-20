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


#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/texture.h>

#include <list>
#include <algorithm>
#include <cmath>

#include "./game.h"
#include "./animation.hpp"
#include "./movable_unit.h"

namespace SoMTD {

using std::tie;

MovableUnit::MovableUnit(
    Tile s_pos,
    Tile e_pos,
    std::string t_path,
    std::vector< std::pair<int, int> > best_path,
    Animation::StateStyle entity_state_style,
    int frame_per_state,
    int total_states,
    int unit_hp,
    int unit_reward,
    int unit_time,
    int hp_discount_unit_win,
    std::string newslowed_path,
    std::string newbleed_path,
    std::string poison_path) :
      m_enemy(true),
      m_end_position(e_pos),
      m_start_position(s_pos),
      m_texture(ijengine::resources::get_texture(t_path)),
      m_active(false),
      m_current_instruction(0),
      m_state_style(entity_state_style),
      m_frame_per_state(frame_per_state),
      m_total_states(total_states),
      m_slowed_path(newslowed_path),
      m_bleeding_path(newbleed_path),
      m_poisoned_path(poison_path) {

    m_status_list = new std::list<MovableUnit::Status>();
    m_time_per_tile = unit_time;
    m_initial_hp = unit_hp;
    m_actual_hp = unit_hp;
    m_hp_discount_unit = hp_discount_unit_win;
    m_gold_award = unit_reward;
    m_done = false;
    m_movement_speed = std::make_pair(0.0, 0.0);
    m_labyrinth_path = best_path;
    m_animation = new Animation(
        s_pos.x,
        s_pos.y,
        t_path,
        entity_state_style,
        m_frame_per_state,
        total_states);
    std::pair<int, int> p = SoMTD::tools::grid_to_isometric(
        s_pos.x, s_pos.y, 100, 81, 1024/2, 11);
    m_start_position = s_pos;
    desired_place = std::pair<int, int>(
        m_start_position.x, m_start_position.y);
    m_x = p.first;
    m_y = p.second;
    ijengine::event::register_listener(this);
    texture_name = t_path;
    m_dead = false;
}

MovableUnit::~MovableUnit() {
  delete m_status_list;
  delete m_animation;
  ijengine::event::unregister_listener(this);
}

double
MovableUnit::x() const {
  return m_x;
}

double
MovableUnit::y() const {
  return m_y;
}

void
MovableUnit::update_self(unsigned now, unsigned) {
  // TODO: refactor this
  if (m_next_frame < now) {
    m_next_frame = now + (1000/m_animation->frame_per_state());
    m_animation->next_frame();
  }

  if (m_active) {
    m_animation->update_screen_position(std::make_pair(m_x, m_y));
    double status_coeff = 1;
    double dmg_coeff = 0;
    if (m_moving) {
      if (!status_list()->empty()) {
        for (auto status=status_list()->begin();
            status != status_list()->end(); ++status) {
          switch (static_cast<int>((*status))) {
            case SLOWED:
              if (static_cast<int>(now) > m_slow_penalization) {
                status = status_list()->erase(status);
                m_animation->update_texture(texture_name);
              } else {
                status_coeff = (m_slow_coeff/1000.0);
              }
              break;

            case BLEEDING:
              if (static_cast<int>(now) > m_bleed_penalization) {
                status = status_list()->erase(status);
                m_animation->update_texture(texture_name);
              } else {
                if (m_last_bleeding_tick+1000 < now) {
                  dmg_coeff = (abs((m_bleed_x - m_x)) +
                      abs((m_bleed_y - m_y)))*0.05;
                  suffer(dmg_coeff);
                  m_last_bleeding_tick = now;
                }
              }
              break;

            case POISONED:
              if (static_cast<int>(now) > m_poison_penalization) {
                status = status_list()->erase(status);
                m_animation->update_texture(texture_name);
              } else {
                if (m_last_poison_tick+1000 < now) {
                  suffer(m_poison_coeff);
                  m_last_poison_tick = now;
                }
              }
              break;

            default:
              break;
          }
        }
      }

      m_x = x() + m_movement_speed.first*status_coeff;
      m_y = y() + m_movement_speed.second*status_coeff;

      if (x()+1 > desired_place.first &&
          x()-1 < desired_place.first &&
          y()+1 > desired_place.second && y()-1 < desired_place.second) {
        m_moving = false;
        m_current_instruction++;
        if (m_current_instruction > m_labyrinth_path.size()) {
          m_active = false;
        }
      }
    } else {
      if (m_current_instruction == m_labyrinth_path.size()) {
        player::get().discount_hp(m_hp_discount_unit);
        die();
      } else {
        std::pair<int, int> pos = m_labyrinth_path[m_current_instruction];
        move(pos.first, pos.second, now);
      }
    }
  }
}

void
MovableUnit::die() {
  m_active = false;
  m_done = true;
}

bool
MovableUnit::on_event(const ijengine::GameEvent&) {
  return false;
}

void
MovableUnit::draw_self(ijengine::Canvas *c, unsigned a1, unsigned a2) {
  if (m_active) {
    m_animation->draw(c, a1, a2);
  }
}

void
MovableUnit::draw_self_after(ijengine::Canvas *c, unsigned, unsigned) {
  int width = ijengine::resources::get_texture("lifesheet.png")->w()/20;

  ijengine::Rectangle rect(0, 0, 460/20, 6);
  int total = 100;
  for (int i=0; i < 20; ++i) {
    if (hp_percentage() >= total) {
      rect.set_position(width*i, 0);
      break;
    }
    total -= 5;
  }

  c->draw(
      ijengine::resources::get_texture("lifesheet.png").get(),
      rect, m_x+100/2,
      m_y-20);
}

int
SoMTD::MovableUnit::hp_percentage() const {
  return 100 * m_actual_hp/m_initial_hp;
}

bool
SoMTD::MovableUnit::enemy() const {
  return m_enemy;
}

void
SoMTD::MovableUnit::spawn() {
  m_active = true;
  m_moving = false;
  m_current_instruction = 0;
  tie(m_x, m_y) = SoMTD::tools::grid_to_isometric(
      m_start_position.x, m_start_position.y, 100, 81, 1024/2, 11);
}

bool
SoMTD::MovableUnit::active() const {
  return m_active;
}

void
SoMTD::MovableUnit::move(int new_x, int new_y, unsigned) {
  m_moving = true;
  const int tile_width = 100;
  const int tile_height = 81;
  desired_place = SoMTD::tools::grid_to_isometric(
      new_x, new_y, tile_width, tile_height, 1024/2, 11);
  m_movement_speed.first = desired_place.first - x();
  m_movement_speed.first /= (m_time_per_tile);
  m_movement_speed.second = (desired_place.second - y());
  m_movement_speed.second /= (m_time_per_tile);

  if (m_movement_speed.first > 0) {
    animation()->update_direction(
        Animation::DirectionState::DIRECTION_RIGHT);
  } else if (m_movement_speed.first < 0) {
    animation()->update_direction(
        Animation::DirectionState::DIRECTION_LEFT);
  }
}

bool
MovableUnit::done() const {
  return m_done;
}

Animation*
MovableUnit::animation() const {
  return m_animation;
}

void
MovableUnit::suffer(int dmg) {
  m_actual_hp -= dmg;
  if (m_actual_hp < 1) {
    die();
    m_dead = true;
    player::get().update_gold(player::get().gold()+gold_award());
  }
}

bool
SoMTD::MovableUnit::dead() const {
    return m_dead;
}

int
SoMTD::MovableUnit::gold_award() const {
    return m_gold_award;
}

void
MovableUnit::suffer_slow(
    int slow_coeff, int time_penalization, unsigned now, unsigned) {
  m_slow_coeff = slow_coeff;
  m_status_list->push_back(Status::SLOWED);
  m_slow_penalization = time_penalization + now;
  m_animation->update_texture(m_slowed_path);
}

void
MovableUnit::suffer_bleed(
    double bleed_coeff, int time_penalization, unsigned now, unsigned) {
  m_bleed_coeff = bleed_coeff;
  m_status_list->push_back(Status::BLEEDING);
  m_bleed_penalization = time_penalization + now;
  m_animation->update_texture(m_bleeding_path);
  m_last_bleeding_tick = now;
  m_bleed_x = m_x;
  m_bleed_y = m_y;
}

void
MovableUnit::suffer_poison(
    double poison_coeff, int time_penalization, unsigned now, unsigned) {
  m_poison_coeff = poison_coeff;
  m_status_list->push_back(Status::POISONED);
  m_poison_penalization = time_penalization + now;
  m_animation->update_texture(m_poisoned_path);
  m_last_bleeding_tick = now;
}

Tile
MovableUnit::start_position() const {
  return m_start_position;
}

Tile
MovableUnit::end_position() const {
  return m_end_position;
}

std::list<MovableUnit::Status>*
MovableUnit::status_list() const {
  return m_status_list;
}
}  // namespace SoMTD
