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

#ifndef GAME_INCLUDE_CENTAUR_HPP_
#define GAME_INCLUDE_CENTAUR_HPP_

#include <utility>
#include <vector>
#include <string>

#include "./movable_unit.h"

namespace SoMTD {
  using ii = std::pair<int, int>;
  using vii = std::vector<ii>;

class Centaur : public MovableUnit {
 public:
  Centaur(
      ii _origin, ii _destination, vii _path, Player* _player);

  Animation::StateStyle _state_style() const;
  int _hp_discount_unit_win() const;
  int _time_per_tile() const;
  int _frame_per_state() const;
  int _total_states() const;
  int _gold_reward() const;
  int _hp() const;
  std::string _texture_path() const;
  std::string _poison_texture_path() const;
  std::string _slow_texture_path() const;
  std::string _bleed_texture_path() const;
};
}  // namespace SoMTD

#endif  // GAME_INCLUDE_CENTAUR_HPP_
