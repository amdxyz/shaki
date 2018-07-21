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

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "lis3dh.h"
#include "frame_data.h"


// Direction inversion threshold
#define THRESHOLD_ABS_ACCEL     60
// Column timer sync
// 8ms rollover at 16bit = 122ns step. 20000 is about 2.44ms
#define TIMER_PERIOD            20000

#define DEBUG_PIN               PIND0
#define DEBUG_DDR               DDRD
#define SET_DEBUG_PIN()         PORTD |= DEBUG_PIN
#define UNSET_DEBUG_PIN()       PORTD &= ~DEBUG_PIN


typedef enum Error {
    ERROR_NONE = 0,
    ERROR_ACCELEROMETER = 1
} Error;

typedef enum Direction {
    DIR_UNKNOWN,
    DIR_LEFT_TO_RIGHT,
    DIR_RIGHT_TO_LEFT
} Direction;

Direction direction = DIR_UNKNOWN;

// Index of the column within the frame being painted
volatile uint8_t col_index = 0;
// A flag set by the ISR upon the accelerometer's interrupt trigger
volatile uint8_t rdy_flag = 1;
// Index of the current frame being painted
uint8_t frame_index = 0;


// FORWARD PROTOTYPES

void paint_column();


// INTERRUPT SERVICE ROUTINES

ISR(TIMER1_COMPA_vect)
{
#ifdef TEST_PATTERN
    // Clear the LEDs (the test pattern sets a solid column at the motion's extremes)
    PORTB = 0;
#else
    // Use the frames buffer to set the LEDs pattern
    paint_column();
#endif
}

ISR(INT0_vect)
{
    // Mark the availability of new accelerometer data
    rdy_flag = 1;
}


void paint_column()
{
#ifdef DEBUG_ON_COLUMN
    SET_DEBUG_PIN();
#endif

    if (col_index < COLS && direction == DIR_LEFT_TO_RIGHT) {
        // Fetch a column from the frames stack and copy it to the PORTB register
        // The post-increment forwards the column index
        PORTB = pgm_read_byte(&(frames[frame_index][col_index++]));
    } else {
        // When moving from right to left keep the led bar off
        PORTB = 0;
    }

#ifdef DEBUG_ON_COLUMN
    UNSET_DEBUG_PIN();
#endif

    // Reset the timer
    TCNT1 = 0;
}

void report_error(Error error)
{
    // Endless loop reporting errors using the LEDs bar
    while (1) {
        PORTB = (uint8_t)error;
        _delay_ms(200);
        PORTB = 0;
        _delay_ms(200);
    }
}

void init()
{
    // Configure timer1 no prescaler, CTC (max ~8ms rollover)
    // this timer is used to clock in the columns
    // Notice that he scan rate is not adaptive
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10);
    OCR1A = TIMER_PERIOD;

    // Enable INT0 on rising edge (connected to LIS3 INT1)
    EICRA = (1 << ISC00) | (1 << ISC01);
    EIMSK = (1 << INT0);

    // All outputs on port B
    DDRB = 0xff;

#if defined(DEBUG_ON_SHAKE) || defined(DEBUG_ON_COLUMN)
    // Enable output on debug pin
    DEBUG_DDR |= DEBUG_PIN;
#endif

    // Initialize the accelerometer and report error in case of failure
    if (lis3dh_init() != 0) {
        report_error(ERROR_ACCELEROMETER);
    }

    // Enable timer1 interrupts
    TIMSK1 = (1 << OCIE1A);

    sei();
}

void eval_motion(AccelVec *accel_vec)
{
    static int8_t extreme_val = 0;

#if SPF > 1
    static uint8_t frame_decimator = 0;
#endif

    if (accel_vec->y > THRESHOLD_ABS_ACCEL && direction != DIR_LEFT_TO_RIGHT) {
        if (accel_vec->y > extreme_val) {
            // Find the maximum
            extreme_val = accel_vec->y;
        } else {
            // Maximum found (the acceleration module gradient is now negative)
            // The leftmost position of the shake is reached
#ifdef DEBUG_ON_SHAKE
            SET_DEBUG_PIN();
#endif
            // Reset column index to the first one
            // The enqueued frame is primed and ready to paint from its first column
            direction = DIR_LEFT_TO_RIGHT;
            col_index = 0;

#ifdef TEST_PATTERN
            // Paint a single, filled column at the leftmost extreme of the motion
            // This will be then cleared at next timer1 overflow
            TCNT1 = 0;
            PORTB = 0xff;
#else
            paint_column();
#endif
        }
    } else if (accel_vec->y < -THRESHOLD_ABS_ACCEL && direction != DIR_RIGHT_TO_LEFT) {
        if (accel_vec->y < extreme_val) {
            // Find the minimum
            extreme_val = accel_vec->y;
        } else {
            // Minimum found (the acceleration module gradient is now positive)
            // The rightmost position of the shake is reached
#ifdef DEBUG_ON_SHAKE
            UNSET_DEBUG_PIN();
#endif

#ifdef TEST_PATTERN
            // Paint a single, filled column at the rightmost extreme of the motion
            // This will be then cleared at next timer1 overflow
            TCNT1 = 0;
            PORTB = 0xff;
#endif
            // Update the direction
            direction = DIR_RIGHT_TO_LEFT;

#if SPF > 1
            // If the decimator is used, do not advance the frame count until
            // SPF frames are persisted
            ++frame_decimator;
            if (frame_decimator == SPF) {
                frame_index = (frame_index + 1) % FRAMES_COUNT;
                frame_decimator = 0;
            }
#else
            // When not using the decimator, advance the frame at each shake
            frame_index = (frame_index + 1) % FRAMES_COUNT;
#endif
        }
    }
}


int main(void)
{
    AccelVec accel_vec;

    init();

    while(1) {
        // Wait until the accelerometer asserts its INT1 line
        while (rdy_flag == 0);

        // Pull acceleration data from the accelerometer's registers
        lis3dh_update(&accel_vec);

        // Process the acceleration vector
        eval_motion(&accel_vec);
    }
}
