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
  usbDeviceDisconnect();
  wdt_reset();
  _delay_ms(50);
  usbDeviceConnect();
}

int main() {
  wdt_enable(WDTO_1S);

  odDebugInit();

  usbReset();

  usbInit();
  sei();

  while (true) {
    wdt_reset();
    usbPoll();
  }
}

usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
  // TODO
  (void)reinterpret_cast<usbRequest_t *>(data);

  odDebug(0x10, data, 8);

  return USB_NO_MSG;
}

uint8_t usbFunctionRead(uint8_t *data, uint8_t len) {
  // TODO
  (void)data;
  (void)len;

  odDebug(0x11, data, len);

  // return actual bytes written
  return 0;
}

uint8_t usbFunctionWrite(uint8_t *data, uint8_t len) {
  // TODO
  (void)data;
  (void)len;

  odDebug(0x12, data, len);

  // received entire payload successfully: return 1
  // expect more data: return 0
  return 1;
}
