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

#include "./zeus_tower.hpp"
#include "./tower.h"

namespace SoMTD {
ZeusTower::ZeusTower(int _x, int _y, int _level, Player* _player) : Tower(
    _texture_path()[_level - 1],
    _level,
    _x,
    _y,
    _selected_texture_path()[_level - 1],
    _player,
    static_cast<Animation::StateStyle>(1),
    4,
    1,
    2.0,
    50
  ) { }

std::vector<std::string>
ZeusTower::_texture_path() const {
  // the first texture is for a level 1 zeus tower, etc
  return std::vector<std::string> {
    "towers/tower_0.png",
    "towers/tower_1.png",
    "towers/tower_2.png",
    "towers/tower_3.png"
  };
}

std::vector<std::string>
ZeusTower::_selected_texture_path() const {
  // the first texture is for a level 1 zeus tower, etc
  return std::vector<std::string> {
    "towers/tower_0.png",
    "towers/tower_1.png",
    "towers/tower_2.png",
    "towers/tower_3.png"
  };
}
}  // namespace SoMTD
