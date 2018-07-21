/* ***********************************************************************
    Shaki firmware
    Copyright (C) 2016-2018 Marco Fagiolini <mfx@amdx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ***********************************************************************/

#ifndef FRAMEDATA_H_
#define FRAMEDATA_H_

#include <stdint.h>
#include <avr/pgmspace.h>

// Persist each frame for 5 shakes
#define SPF    5

// Framebuffer boundaries
#define FRAMES_COUNT  2
#define COLS          8

// Framebuffer
// Each byte represents a column, each array a frame
const uint8_t frames[FRAMES_COUNT][COLS] PROGMEM = {
    {0xfb, 0xfb, 0xdb, 0xdb, 0xdb, 0xdb, 0xff, 0xff},   // AMDX Logo
    {0x1e, 0x21, 0x41, 0x86, 0x86, 0x41, 0x21, 0x1e}    // Heart
};

#endif /* FRAMEDATA_H_ */
