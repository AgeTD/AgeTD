// Copyright (C) 2018 Dylan Guedes
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

#ifndef GAME_INCLUDE_PLAYER_HPP_
#define GAME_INCLUDE_PLAYER_HPP_

#include <ijengine/game_object.h>
#include <list>
#include <bitset>

namespace SoMTD {
class player {
 public:
  static player& get();

  enum PlayerState {
  IDLE = 0,
  HOLDING_BUILD = 1,
  INVALID_BUILD = 3,
  NOT_ENOUGH_GOLD = 4,
  SELECTED_TOWER = 5,
  OPENED_TOWER_PANEL = 6
  };

  int gold() const;
  int hp() const;
  int desired_tower() const;

  int state;
  ijengine::GameObject *selected_object = nullptr;

  void discount_gold(int);
  void update_gold(int new_gold_count);
  void increase_gold(int new_gold_count);
  void discount_hp(int);
  void update_desired_tower(int towerid, int towerprice);
  std::list<int> *units_events() const;
  std::list<int> *event_args() const;
  void open_tower_panel(unsigned tower_id);
  unsigned tower_panel_id() const;
  int m_desired_tower_price;
  std::bitset<12> upgrade_state() const;
  void research(std::bitset<12> upgrade);

 private:
  player();
  ~player();

  int m_gold;
  int m_y;
  int m_x;
  int m_hp = 50;
  int m_desired_tower = 0;
  std::list<int> *m_units_events;
  std::list<int> *m_event_args;
  bool m_buy_tower_panel_opened;
  unsigned m_tower_panel_id;
  std::bitset<12> m_upgrade_state;

 public:
  player(player const&) = delete;
  void operator=(player const&) = delete;
};
}  // namespace SoMTD
#endif  // GAME_INCLUDE_PLAYER_HPP_
