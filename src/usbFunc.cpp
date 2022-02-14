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

// USB handle functions.

#include <ATPR.hpp>
#include <string.h>

// see declarations for impl notes
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
  // TODO
  (void)reinterpret_cast<usbRequest_t *>(data);

  // control-in:
  // have `usbMsgPtr` set: return size
  // usbFunctionRead(): return USB_NO_MSG
  //
  // control-out:
  // ignore incoming data: return 0
  // usbFunctionWrite(): return USB_NO_MSG
  return USB_NO_MSG;
}

uint8_t usbFunctionRead(uint8_t *data, uint8_t len) {
  // TODO
  (void)data;
  (void)len;

  // return actual bytes written to `data`
  return 0;
}

uint8_t usbFunctionWrite(uint8_t *data, uint8_t len) {
  // TODO
  (void)data;
  (void)len;

  // received entire payload: return 1
  // expect more data: return 0
  return 1;
}
