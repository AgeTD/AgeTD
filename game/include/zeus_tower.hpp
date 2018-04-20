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

#ifndef GAME_INCLUDE_ZEUS_TOWER_HPP_
#define GAME_INCLUDE_ZEUS_TOWER_HPP_

#include <string>
#include <vector>

#include "./tower.h"

namespace SoMTD {
class ZeusTower : public Tower {
 public:
  ZeusTower(int _x, int _y, int _level);

  std::vector<std::string> _texture_path() const;
  std::vector<std::string> _selected_texture_path() const;

 private:
};
}  // namespace SoMTD

#endif  // GAME_INCLUDE_ZEUS_TOWER_HPP_

