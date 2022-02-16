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

#include <ATPR.hpp>
#include <util/delay.h>

// ISP protocol implementations
// TODO: replace _delay_us() usage?

#define _wrappedSetPin()

#define resetHigh()      \
  do {                   \
    set_bit(PORTD, PD0); \
  } while (0)

#define resetLow()         \
  do {                     \
    clear_bit(PORTD, PD0); \
  } while (0)

uint8_t (*isp::transfer)(uint8_t);

void isp::connect() {
  SPI_DDR |= _BV(SPI_MOSI) | _BV(SPI_SCK);
  set_bit(DDRD, PD0);       // Reset pin out
  set_bit(SPI_OUT, SPI_SS); // SS pullup

  // SCK and RST low
  clear_bit(SPI_OUT, SPI_SCK);
  resetLow();

  // Enable SPI, Master mode
  SPCR |= _BV(SPE) | _BV(MSTR);

  // Positive pulse
  _delay_us(4);
  resetHigh();
  _delay_us(4);
  resetLow();

  _delay_ms(25);
}

void isp::close() {
  SPI_DDR &= ~(_BV(SPI_MOSI) | _BV(SPI_SCK));
  resetHigh();

  // Disable SPI, reset settings
  SPSR = 0;
  SPCR = 0;
}

bool isp::begin() {
  for (uint8_t tries = 8; tries; --tries) {
    transfer(0xAC);
    transfer(0x53);
    uint8_t echo = transfer(0x00);
    transfer(0x00);

    if (echo == 0x53) {
      return true;
    }

    // Failed attempt, retrying
    resetHigh();
    _delay_us(4);
    resetLow();
    _delay_us(4);
  }
  return false;
}

void isp::setSpiOpt(uint8_t option) {
  // Bits:
  // 0  0  0  0  HSPI  SPI2X  SPR1  SPR0
  if (option & _BV(3)) {
    // use hardware SPI

    if (option & _BV(2))
      set_bit(SPSR, SPI2X);
    if (option & _BV(1))
      set_bit(SPCR, SPR1);
    if (option & _BV(0))
      set_bit(SPCR, SPR0);

    transfer = spi::hwTransfer;
  } else {
    // use software SPI

    uint8_t exp = option & 0x7;
    spi::delayClock = 1 << exp;

    transfer = spi::swTransfer;
  }
}

// ---

uint8_t isp::handler(uint8_t *data, uint8_t len) {
  if (len == 0xFF) {
    // called in usbFunctionSetup, data size 8
    const uint8_t &op = data[1];
    if (op == BEGIN) {
      setSpiOpt(data[2]);

      connect();
      data[1] = begin();

      usbMsgPtr = data + 1;
      return 1;
    } else if (op == TRANSMIT) {
      data[2] = transfer(data[2]);
      data[3] = transfer(data[3]);
      data[4] = transfer(data[4]);
      data[5] = transfer(data[5]);

      usbMsgPtr = data + 2;
      return 4;
    } else if (op == END) {
      close();

      usbMsgPtr = data + 1;
      return 1;
    }

    // TODO
    return 0;
  } else {
    // called in usbFunctionRead / usbFunctionWrite
    // TODO
    return 0;
  }
}
