/* ATPR - Yet another programmer & debugger for Atmel MCUs
 * Copyright (C) 2021 45gfg9
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __ATPR_PARTS_HPP__
#define __ATPR_PARTS_HPP__

#include <ATPR.hpp>

// THIS FILE IS WIP

enum class MemType : uint8_t {
  FLASH,
  EEPROM,
  FUSE,
  LOCK_BITS,
};

// polymorphic is not out-of-the-box for AVR. oh.
#if 0

class Chip {
public:
  Chip() = default;
  virtual ~Chip() = default;

  // TODO
  virtual void read() = 0;
  virtual void write() = 0;
};

class : public Chip {
public:
  void read() override {}
  void write() override {}
} AT89;

#endif

#endif
