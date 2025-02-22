/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * HAL/shared/Marduino.h
 */

#undef DISABLED       // Redefined by ESP32
#undef M_PI           // Redefined by all
#undef _BV            // Redefined by some
#undef SBI            // Redefined by arduino/const_functions.h
#undef CBI            // Redefined by arduino/const_functions.h
#undef sq             // Redefined by teensy3/wiring.h
#undef UNUSED         // Redefined by stm32f4xx_hal_def.h

#include <Arduino.h>  // NOTE: If included earlier then this line is a NOOP

#undef DISABLED
#define DISABLED(V...) DO(DIS,&&,V)

#undef _BV
#define _BV(b) (1UL << (b))
#ifndef SBI
  #define SBI(A,B) (A |= _BV(B))
#endif
#ifndef CBI
  #define CBI(A,B) (A &= ~_BV(B))
#endif

#undef sq
#define sq(x) ((x)*(x))

#ifndef __AVR__
  #ifndef strchr_P // Some platforms define a macro (DUE, teensy35)
    inline const char* strchr_P(const char *s, int c) { return strchr(s,c); }
    //#define strchr_P(s,c) strchr(s,c)
  #endif

  #ifndef snprintf_P
    #define snprintf_P snprintf
  #endif
  #ifndef vsnprintf_P
    #define vsnprintf_P vsnprintf
  #endif
#endif

// Restart causes
#define RST_POWER_ON    1
#define RST_EXTERNAL    2
#define RST_BROWN_OUT   4
#define RST_WATCHDOG    8
#define RST_JTAG       16
#define RST_SOFTWARE   32
#define RST_BACKUP     64

#ifndef M_PI
  #define M_PI 3.14159265358979323846f
#endif

// Remove compiler warning on an unused variable
#ifndef UNUSED
  #define UNUSED(x) ((void)(x))
#endif

#ifndef FORCE_INLINE
  #define FORCE_INLINE inline __attribute__((always_inline))
#endif

#include "progmem.h"

class __FlashStringHelper;
typedef const __FlashStringHelper* FSTR_P;
#ifndef FPSTR
  #define FPSTR(S) (reinterpret_cast<FSTR_P>(S))
#endif
#define FTOP(S) (reinterpret_cast<const char*>(S))
