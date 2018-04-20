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

#include "./medusa.hpp"
#include "./movable_unit.h"

namespace SoMTD {
using ii = std::pair<int, int>;
using vii = std::vector<ii>;

Medusa::Medusa(
    Tile _origin, Tile _destination, vii _path) : MovableUnit(
    _origin,
    _destination,
    _texture_path(),
    _path,
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
Medusa::_texture_path() const {
  return "units/medusa/medusasheet.png";
}

Animation::StateStyle
Medusa::_state_style() const {
  return static_cast<Animation::StateStyle>(2);
}

int
Medusa::_total_states() const {
  return 2;
}

int
Medusa::_frame_per_state() const {
  return 12;
}

int
Medusa::_gold_reward() const {
  return 15;
}

int
Medusa::_hp() const {
  return 80;
}

int
Medusa::_time_per_tile() const {
  return 80;
}

int
Medusa::_hp_discount_unit_win() const {
  return 2;
}

std::string
Medusa::_slow_texture_path() const {
  return "units/medusa/medusasheet_congelada.png";
}

std::string
Medusa::_bleed_texture_path() const {
  return "units/medusa/medusasheet_vermelho.png";
}

std::string
Medusa::_poison_texture_path() const {
  return "units/medusa/medusasheet_verde.png";
}

Medusa*
Medusa::_clone() {
  return new Medusa(
      start_position(),
      end_position(),
      this->m_labyrinth_path);
}
}  // namespace SoMTD
