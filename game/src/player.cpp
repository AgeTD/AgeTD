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

#include <ijengine/engine.h>

#include <iostream>

#include "./player.hpp"

namespace SoMTD {
player::player() : m_y(0), m_x(0) {
  state = 0x0000;
  m_gold = 60600;
  m_units_events = new std::list<int>();
  m_event_args = new std::list<int>();
  m_buy_tower_panel_opened = false;
  m_upgrade_state.reset();
  m_upgrade_state.set(0);
}

player::~player() {
  delete m_units_events;
  delete m_event_args;
}

int
player::gold() const {
  return m_gold;
}

int
player::hp() const {
  return m_hp;
}

int
player::desired_tower() const {
  return m_desired_tower;
}

void
player::update_desired_tower(int m_id, int price) {
  m_desired_tower = m_id;
  m_desired_tower_price = price;
}

void
player::update_gold(int new_gold_count) {
  m_gold = new_gold_count;
}

void
player::discount_gold(int value) {
  m_gold -= value;
  ijengine::audio::play_sound_effect("res/sound_efects/gold.ogg");
}

void
player::increase_gold(int value) {
  m_gold += value;
}

void
player::discount_hp(int value) {
  m_hp -= value;
  ijengine::audio::play_sound_effect("res/sound_efects/hp_baixo.ogg");
}

std::list<int>*
player::units_events() const {
  return m_units_events;
}

std::list<int>*
player::event_args() const {
  return m_event_args;
}

void
player::open_tower_panel(unsigned id) {
  m_buy_tower_panel_opened = true;
  m_tower_panel_id = id;
}

unsigned
player::tower_panel_id() const {
  return m_tower_panel_id;
}

std::bitset<12>
player::upgrade_state() const {
  return m_upgrade_state;
}

void
player::research(std::bitset<12> upgrade) {
  m_upgrade_state |= upgrade;
  ijengine::audio::play_sound_effect("res/sound_efects/Level_up.ogg");
}

player&
player::get() {
  static player _instance;
  return _instance;
}
}  // namespace SoMTD
