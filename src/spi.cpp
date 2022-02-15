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

// SPI implementations, heavily based on USBasp code

#include <ATPR.hpp>

#include <avr/io.h>
#include <util/delay.h>

uint8_t spi::delayClock;

uint8_t resetTarget() {
  return 0;
}

void spi::delay() {
  const uint8_t start = TCNT0;
  while (TCNT0 - start < delayClock)
    ;
}

uint8_t spi::swTransfer(uint8_t send_byte) {
  uint8_t recv_byte = 0;
  for (uint8_t i = 8; i; i--) {
    // MSBFIRST
    if (send_byte & 0x80) {
      set_bit(SPI_OUT, SPI_MOSI);
    } else {
      clear_bit(SPI_OUT, SPI_MOSI);
    }
    // shift to next bit
    send_byte <<= 1;

    // receive data
    recv_byte <<= 1;
    if (bit_is_set(SPI_IN, SPI_MISO)) {
      recv_byte++;
    }

    // pulse SCK
    set_bit(SPI_OUT, SPI_SCK);
    delay();
    clear_bit(SPI_OUT, SPI_SCK);
    delay();
  }

  return recv_byte;
}

uint8_t spi::hwTransfer(uint8_t send_byte) {
  SPDR = send_byte;
  loop_until_bit_is_set(SPSR, SPIF);
  return SPDR; // SPIF is auto cleared after this
}
