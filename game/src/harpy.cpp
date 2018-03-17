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

#include "./harpy.hpp"
#include "./movable_unit.h"

namespace SoMTD {
using ii = std::pair<int, int>;
using vii = std::vector<ii>;

Harpy::Harpy(
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
Harpy::_texture_path() const {
  return "units/harpia/harpiasheet.png";
}

Animation::StateStyle
Harpy::_state_style() const {
  return static_cast<Animation::StateStyle>(2);
}

int
Harpy::_total_states() const {
  return 2;
}

int
Harpy::_frame_per_state() const {
  return 16;
}

int
Harpy::_gold_reward() const {
  return 8;
}

int
Harpy::_hp() const {
  return 150;
}

int
Harpy::_time_per_tile() const {
  return 100;
}

int
Harpy::_hp_discount_unit_win() const {
  return 4;
}

std::string
Harpy::_slow_texture_path() const {
  return "units/harpia/harpiasheet_congelado.png";
}

std::string
Harpy::_bleed_texture_path() const {
  return "units/harpia/harpiasheet_vermelho.png";
}

std::string
Harpy::_poison_texture_path() const {
  return "units/harpia/harpiasheet_verde.png";
}

Harpy*
Harpy::_clone() {
  return new Harpy(
      this->start_position,
      this->end_position,
      this->m_labyrinth_path,
      this->m_player);
}
}  // namespace SoMTD
