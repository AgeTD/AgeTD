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

#include "./cyclop.hpp"
#include "./movable_unit.h"

namespace SoMTD {
using ii = std::pair<int, int>;
using vii = std::vector<ii>;

Cyclop::Cyclop(
    ii _origin, ii _destination, vii _path, Player *_player) : MovableUnit(
    _origin,
    _destination,
    _texture_path(),
    _path,
    _player,
    _state_style(),
    _frame_per_state(),
    _total_states(),
    _hp(),
    _gold_reward(),
    _time_per_tile(),
    _hp_discount_unit_win(),
    _slow_texture_path(),
    _bleed_texture_path(),
    _poison_texture_path()
  ) { }

std::string
Cyclop::_texture_path() const {
  return "units/ciclope/ciclopsheet.png";
}

Animation::StateStyle
Cyclop::_state_style() const {
  return static_cast<Animation::StateStyle>(2);
}

int
Cyclop::_total_states() const {
  return 2;
}

int
Cyclop::_frame_per_state() const {
  return 12;
}

int
Cyclop::_gold_reward() const {
  return 10;
}

int
Cyclop::_hp() const {
  return 100;
}

int
Cyclop::_time_per_tile() const {
  return 200;
}

int
Cyclop::_hp_discount_unit_win() const {
  return 1;
}

std::string
Cyclop::_slow_texture_path() const {
  return "units/ciclope/ciclopsheet_congelado.png";
}

std::string
Cyclop::_bleed_texture_path() const {
  return "units/ciclope/ciclopsheet_vermelho.png";
}

std::string
Cyclop::_poison_texture_path() const {
  return "units/ciclope/ciclopsheet_verde.png";
}

Cyclop*
Cyclop::_clone() {
  return new Cyclop(
      this->start_position,
      this->end_position,
      this->m_labyrinth_path,
      this->m_player);
}
}  // namespace SoMTD
