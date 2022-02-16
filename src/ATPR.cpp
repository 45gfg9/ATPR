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

// ATPR main file.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <ATPR.hpp>

static void usbReset() {
  usbDeviceDisconnect();
  wdt_reset();
  _delay_ms(50);
  usbDeviceConnect();
}

// PD3 Idle LED
// PD5 Operate LED

int main() {
  wdt_enable(WDTO_1S);

  DDRD = _BV(PD3);

  // Port C all output
  DDRC = 0xFF;

  // Timer 0 prescaler: 256 (16MHz / 256 = 62.5KHz)
  TCCR0 |= _BV(CS02);

  // ADC setup
  // Internal 2.56V ref, PA7 channel
  // ADC prescaler: 128 (16MHz / 128 = 125KHz)
  ADMUX = 0b11000111;
  ADCSRA = 0b00000111;

  usbReset();

  usbInit();
  sei();

  while (true) {
    wdt_reset();
    usbPoll();
  }
}
