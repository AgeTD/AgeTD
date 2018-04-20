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

#ifndef GAME_INCLUDE_MOVABLE_UNIT_H_
#define GAME_INCLUDE_MOVABLE_UNIT_H_

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>

#include <utility>
#include <string>
#include <memory>
#include <queue>
#include <list>
#include <set>
#include <vector>

#include "./player.hpp"
#include "./game.h"
#include "./animation.hpp"

namespace SoMTD {
  using ijengine::GameObject;
  using ijengine::GameEventsListener;

class MovableUnit : public GameObject, public GameEventsListener {
 public:
  enum Status {
    NORMAL = 0x0000,
    SLOWED = 0x0001,
    BLEEDING = 0x0002,
    POISONED = 0x0003,
    TOTAL = 0x0004
  };

  MovableUnit(
      Tile s_pos,
      Tile e_pos,
      std::string texture_path,
      std::vector< std::pair<int, int> >,
      Animation::StateStyle entity_state,
      int frame_per_state,
      int total_states,
      int unit_hp,
      int unit_reward,
      int time_per_tiles,
      int hp_discount_unit_win,
      std::string slowed_path,
      std::string bleeding_path,
      std::string poisoned_path);
  ~MovableUnit();
  bool enemy() const;
  void spawn();
  bool active() const;
  void move(int x, int y, unsigned now);
  virtual MovableUnit* _clone() = 0;
  void draw_self(ijengine::Canvas*, unsigned, unsigned);
  void draw_self_after(ijengine::Canvas*, unsigned, unsigned);
  void update_self(unsigned, unsigned);
  std::vector< std::pair<int, int> > m_labyrinth_path;
  int hp_percentage() const;
  std::string texture_name;
  double x() const;
  double y() const;
  bool done() const;
  Animation* animation() const;
  void suffer(int dmg);
  bool dead() const;
  int gold_award() const;
  int time_per_tile() const;
  void suffer_slow(
      int slow_coeff, int time_penalization, unsigned now, unsigned last);
  void suffer_bleed(
      double bleed_coeff,
      int time_penalization,
      unsigned now,
      unsigned last);
  void suffer_poison(
      double bleed_coeff,
      int time_penalization,
      unsigned now,
      unsigned last);
  std::list<MovableUnit::Status> *status_list() const;
  virtual std::string _texture_path() const = 0;
  Tile start_position() const;
  Tile end_position() const;

 protected:
  bool on_event(const ijengine::GameEvent& event);

 private:
  bool m_enemy;
  Tile m_end_position;
  Tile m_start_position;
  std::shared_ptr<ijengine::Texture> m_texture;
  bool m_active;
  unsigned int m_current_instruction;
  Animation::StateStyle m_state_style;
  int m_frame_per_state = 1;
  int m_total_states = 1;
  std::string m_slowed_path;
  std::string m_bleeding_path;
  std::string m_poisoned_path;
  unsigned m_next_frame = 0;
  void die();
  bool m_done = false;
  std::pair<int, int> grid_position;
  std::pair<int, int> desired_place;
  bool m_moving = false;
  double m_x;
  double m_y;
  std::pair<double, double> m_movement_speed;
  int m_initial_hp = 100;
  int m_actual_hp = 100;
  int m_hp_discount_unit_win;
  Animation *m_animation;
  bool m_dead = false;
  int m_gold_award;
  int m_time_per_tile;
  std::list<MovableUnit::Status>* m_status_list;
  int m_slow_penalization;
  int m_slow_coeff;
  int m_hp_discount_unit;
  double m_bleed_coeff;
  double m_poison_coeff;
  int m_bleed_penalization;
  int m_poison_penalization;
  unsigned m_last_bleeding_tick;
  unsigned m_last_poison_tick;
  double m_bleed_x;
  double m_bleed_y;
};
}  // namespace SoMTD

#endif  // GAME_INCLUDE_MOVABLE_UNIT_H_

