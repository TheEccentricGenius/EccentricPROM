/*
 * MIT License
 *
 * Copyright (c) 2023 TheEccentricGenius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// This controls the shift register that generates the address lines for A0..A15 for most
// chip families.
// Note that this uses direct port control instead of digitalWrite calls so that the code
// can run fast enough to meet the tBLC requirements for SDP and block writes.  This
// sacrifices portability and readability for speed. //
//
// This code will only work on Arduino Uno and Nano hardware.  The ports for other
// Arduinos map to different IO pins.

#include "PromAddressDriver.h"

#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4

void PromAddressDriver::begin()
{
    // The address control pins are always outputs.
    pinMode(SHIFT_DATA, OUTPUT);
    pinMode(SHIFT_CLK, OUTPUT);
    pinMode(SHIFT_LATCH, OUTPUT);
    digitalWrite(SHIFT_DATA, LOW);
    digitalWrite(SHIFT_CLK, LOW);
    digitalWrite(SHIFT_LATCH, LOW);

    // To save time, the setAddress only writes the hi byte if it has changed.
    // The value used to detect the change is initialized to a non-zero value,
    // so set an initial address to avoid the the case where the first address
    // written is the 'magic' initial address.
    setAddress(0x0000, true);
}


// Set a 16 bit address in the two address shift registers.
void PromAddressDriver::setAddress(uint32_t addr, bool outputEnable)
{
    // Set the highest bit as the output enable bit (active low)
    if (outputEnable) {
        addr &= ~0x8000;
    } else {
        addr |= 0x8000;
    }
    byte dataMask = 0x04;
    byte clkMask = 0x08;
    byte latchMask = 0x10;

    // Make sure the clock is low to start.
    PORTD &= ~clkMask;

    // Shift 16 bits in, starting with the MSB.
    for (uint16_t ix = 0; (ix < 16); ix++)
    {
        // Set the data bit
        if (addr & 0x8000)
        {
            PORTD |= dataMask;
        }
        else
        {
            PORTD &= ~dataMask;
        }

        // Toggle the clock high then low
        PORTD |= clkMask;
        delayMicroseconds(3);
        PORTD &= ~clkMask;
        addr <<= 1;
    }

    // Latch the shift register contents into the output register.
    PORTD &= ~latchMask;
    delayMicroseconds(1);
    PORTD |= latchMask;
    delayMicroseconds(1);
    PORTD &= ~latchMask;
}
