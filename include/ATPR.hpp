/* ATPR - Yet another programmer & debugger for Atmel MCUs
 * Copyright (C) 2021-2022 45gfg9
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

#ifndef __ATPR_HPP__
#define __ATPR_HPP__

#include <stdlib.h>
#include <stdint.h>

#include "debug.hpp"
#include "parts.hpp"
#include "spi.hpp"

#include "isp.hpp"

#define set_bit(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define clear_bit(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

using protocolHandler = uint8_t (*)(uint8_t *, uint8_t);

enum class protocol : uint8_t {
  isp,
  none,
};

extern "C" {
// include v-usb headers
#include "usbdrv.h"
}

#endif
