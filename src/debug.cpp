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

// ATPR debug utility.

#ifdef ATPR_DBGEN

#include <ATPR.hpp>
#include "debug.hpp"

#define BAUD 76800
#include <util/setbaud.h>
#include "util/delay.h"

static FILE serr;

static int uart_putchar(char c, FILE *) {
  loop_until_bit_is_set(UCSRA, UDRE);
  UDR = c;
  return 0;
}

void debugInit() {
  asm volatile("wdr");

  UCSRA |= USE_2X << U2X;
  UCSRB |= _BV(TXEN);
  UBRRL = UBRRL_VALUE;

  stderr = &serr;
  fdev_setup_stream(stderr, uart_putchar, nullptr, _FDEV_SETUP_WRITE);

  ATPRDBG("Hi from ATPR\n");
}

#endif
