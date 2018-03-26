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

#ifndef GAME_INCLUDE_GAME_HPP_
#define GAME_INCLUDE_GAME_HPP_

#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/events_translator.h>

#include <string>
#include <utility>

#include "./level_factory.h"
#include "./translator.h"

namespace SoMTD {
struct Point {
  double x;
  double y;
};

struct Tile {
  int x;
  int y;
};

enum {
  MOUSEOVER = 4,
  CLICK = 5,
  BUILD_TOWER = 6,
  SELECT_TOWER = 11,
  UPGRADE_TOWER = 12,
  SPAWN_UNIT = 14
};

namespace tools {
Point grid_to_isometric(int x_grid, int y_grid);

std::pair<int, int> grid_to_isometric(
    int _x, int _y, int tile_width, int tile_height, int x0, int offset);
std::pair<int, int> isometric_to_grid(
    int _x, int _y, int tile_width, int tile_height, int x0, int offset);
}

class Game {
 public:
  Game(const string& title, int w, int h);
  ~Game();
  int run(const string& level_id);

 private:
  ijengine::Game m_game;
  ijengine::Engine m_engine;
  Translator m_translator;
  LevelFactory m_level_factory;
};
}  // namespace SoMTD
#endif  // GAME_INCLUDE_GAME_HPP_

