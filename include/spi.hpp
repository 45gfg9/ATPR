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

// SPI related functions.

#ifndef __ATPR_SPI_HPP__
#define __ATPR_SPI_HPP__

#include <stdint.h>

// Pins for ATmega16A
#define SPI_DDR DDRB
#define SPI_IN PINB
#define SPI_OUT PORTB
#define SPI_SS PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK PB7

namespace spi {
  extern uint8_t delayClock;

  uint8_t swTransfer(uint8_t);
  uint8_t hwTransfer(uint8_t);
} // namespace spi

#endif
