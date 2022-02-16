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

// USB handler functions.

#include <ATPR.hpp>
#include <string.h>
#include <avr/pgmspace.h>

const protocolHandler handlers[] PROGMEM = {
    isp::handler,
};

protocol currentProtocol = protocol::none;

#define readHandlerPtr(xProtocol) \
  reinterpret_cast<protocolHandler>(pgm_read_ptr(handlers + (uint8_t)xProtocol))

// control-in:
// have `usbMsgPtr` set: return size
// usbFunctionRead(): return USB_NO_MSG
//
// control-out:
// ignore incoming data: return 0
// usbFunctionWrite(): return USB_NO_MSG
//
// see declarations for impl notes
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
  if (currentProtocol == protocol::none) {
    uint8_t nextProtocol = data[1];
    if (nextProtocol == 0xFF) {
      // info check
      data[1] = data[2];
      data[2] = 0; // version
      data[3] = 1;
      data[4] = 0;

      usbMsgPtr = data + 1;
      return 4;
    } else {
      // setup packet
      // TODO
      currentProtocol = (protocol)nextProtocol;

      clear_bit(DDRD, PD3); // clear Idling
      set_bit(DDRD, PD5);   // set Operating

      return 0;
    }
  } else if (*reinterpret_cast<const uint32_t *>(data + 2) == 0x469C9140) {
    // terminate packet
    currentProtocol = protocol::none;

    clear_bit(DDRD, PD5); // clear Operating
    set_bit(DDRD, PD3);   // set Idling

    usbMsgPtr = data + 2;
    return sizeof(uint32_t);
  } else {
    auto handler = readHandlerPtr(currentProtocol);
    return handler(data, 0xFF);
  }
}

// return actual bytes written to `data`
uint8_t usbFunctionRead(uint8_t *data, uint8_t len) {
  auto handler = readHandlerPtr(currentProtocol);
  return handler(data, len);
}

// received entire payload: return 1
// expect more data: return 0
uint8_t usbFunctionWrite(uint8_t *data, uint8_t len) {
  auto handler = readHandlerPtr(currentProtocol);
  return handler(data, len);
}
