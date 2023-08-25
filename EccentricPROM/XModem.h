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

/*****************************************************************************/
/*****************************************************************************/
/**
 *
 * XMODEM CRC Communication
 *
 * Simple implementation of read and write using XMODEM CRC.  This is tied
 * directly to the PROM code, so the receive function writes the data to the
 * PROM device as each packet is received.  The complete file is not kept
 * in memory.
 */
#ifndef INCLUDE_CONFIGURE_H
#define INCLUDE_CONFIGURE_H

#include "Arduino.h"
#include "Configure.h"

//class PromDevice;
class CmdStatus;

class XModem
{
  public:
    XModem(PromDevice & pd, CmdStatus & cs) : promDevice(pd), cmdStatus(cs) {}
    uint32_t ReceiveFile(uint32_t address);
    bool SendFile(uint32_t address, uint32_t fileSize);
    void Cancel();

  private:
    PromDevice & promDevice;
    CmdStatus & cmdStatus;

    int GetChar(int msWaitTime = 3000);
    uint16_t UpdateCrc(uint16_t crc, uint8_t data);
    bool StartReceive();
    int ReceivePacket(uint8_t buffer[], unsigned bufferSize, uint8_t seq, uint32_t destAddr);
    void SendPacket(uint32_t address, uint8_t seq);
};

#endif // #define INCLUDE_CONFIGURE_H
