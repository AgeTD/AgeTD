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

#include "./poseidon_tower.hpp"
#include "./tower.h"

namespace SoMTD {
PoseidonTower::PoseidonTower(
    int _x, int _y, int _level) : Tower(
    _texture_path()[_level - 1],
    _level + 0x10 - 1,
    _x,
    _y,
    _selected_texture_path()[_level - 1],
    static_cast<Animation::StateStyle>(1),
    _frame_per_state()[_level - 1],
    _total_states(),
    _attack_speed()[_level - 1],
    _damage()[_level - 1]
  ) { }

std::vector<std::string>
PoseidonTower::_texture_path() const {
  // the first texture is for a level 1 zeus tower, etc
  return std::vector<std::string> {
    "towers/tower_16.png",
    "towers/tower_17.png",
    "towers/tower_18.png",
    "towers/tower_19.png"
  };
}

std::vector<std::string>
PoseidonTower::_selected_texture_path() const {
  // the first texture is for a level 1 zeus tower, etc
  return std::vector<std::string> {
    "towers/tower_16_holding.png",
    "towers/tower_17_holding.png",
    "towers/tower_18_holding.png",
    "towers/tower_19_holding.png"
  };
}

std::vector<double>
PoseidonTower::_attack_speed() const {
  return std::vector<double> {
    3.0, 2.0, 2.0, 1.5
  };
}

std::vector<double>
PoseidonTower::_damage() const {
  return std::vector<double> {
    0, 0, 0, 0
  };
}

std::vector<int>
PoseidonTower::_frame_per_state() const {
  return std::vector<int> {
    4, 4, 1, 1
  };
}

int
PoseidonTower::_total_states() const {
  return 1;
}
}  // namespace SoMTD
