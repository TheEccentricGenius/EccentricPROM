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

#ifndef INCLUDE_PROM_DEVICE_28C_H
#define INCLUDE_PROM_DEVICE_28C_H

#include "Arduino.h"
#include "PromDevice.h"

/*****************************************************************************/
/*****************************************************************************/
/**
 * PromDevice28C class
 *
 * Provides the device-specific interface to read and write data from a
 * 28C series parallel EEPROM using the Arduino.
 *
 * Block writes are supported on compatible devices by specifying a blockSize
 * in the constructor.  Use zero for byte writes.
 */
class PromDevice28C : public PromDevice
{
  public:
    PromDevice28C(uint32_t size, word blockSize, unsigned maxWriteTime, bool polling);
    void begin();
    const char * getName() { return "28C series EEPROM"; }
    ERET disableSoftwareWriteProtect();
    ERET enableSoftwareWriteProtect();

  protected:
    void setAddress(uint32_t address);
    byte readByte(uint32_t address);
    bool burnByte(byte value, uint32_t address);
    bool burnBlock(byte data[], uint32_t len, uint32_t address);
    bool waitForWriteCycleEnd(byte lastValue);
    void setByte(byte value, uint32_t address);
};

#endif  // #define INCLUDE_PROM_DEVICE_28C_H
