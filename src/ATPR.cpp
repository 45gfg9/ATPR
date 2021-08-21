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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <ATPR.h>

static void usbReset() {
  USBDDR |= USBMASK; // SE0 signal
  _delay_ms(10);
  USBDDR = 0;
}

int main() {
  wdt_enable(WDTO_1S);

  usbReset();

  usbInit();
  sei();

  while (true) {
    wdt_reset();
    usbPoll();
  }

  return 0;
}

usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
  (void)reinterpret_cast<usbRequest_t *>(data);

  return USB_NO_MSG;
}
