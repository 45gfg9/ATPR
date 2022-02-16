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

// ISP protocol.

#ifndef __ATPR_PROTOCOL_ISP_HPP__
#define __ATPR_PROTOCOL_ISP_HPP__

#include <stdint.h>

namespace isp {
  // instructions
  enum inst : uint8_t {
    BEGIN,
    TRANSMIT,
    END,
  };

  // Protocol Handler
  uint8_t handler(uint8_t *, uint8_t);

  // Prepare connection to target device
  void connect();

  // Close connection to target device
  void disconnect();

  // Enter programming mode, true on success
  bool begin();

  // read byte from flash at given address
  uint8_t readFlash(unsigned long address);

  // write byte to flash at given address
  uint8_t writeFlash(unsigned long address, uint8_t data, uint8_t pollmode);

  // flush Flash page
  uint8_t flushPage(unsigned long address, uint8_t pollvalue);

  // read byte from eeprom at given address
  uint8_t readEEPROM(unsigned int address);

  // write byte to eeprom at given address
  uint8_t writeEEPROM(unsigned int address, uint8_t data);

  // pointer to sw or hw transmit function
  extern uint8_t (*transfer)(uint8_t);

  // set SPI option. call before isp::connect!
  void setSpiOpt(uint8_t option);

  // load extended address byte
  void loadExtendedAddressByte(unsigned long address);
} // namespace isp

#endif
