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

#include "Arduino.h"
#include "CmdStatus.h"

CmdStatus::CmdStatus()
{
    clear();
}

void CmdStatus::clear()
{
    level = SL_NONE;
    message = "OK";
    for (int ix = 0; ix < MAX_VALUES; ix++)
    {
        values[ix].valType = VT_NONE;
    }
}

void CmdStatus::info(const char * msg)
{
    level = SL_INFO;
    message = msg;
}

void CmdStatus::error(const char * msg)
{
    level = SL_ERROR;
    message = msg;
}

void CmdStatus::setValueDec(int index, const char * label, long value)
{
    setLongValue(index, label, value, VT_DEC);
}

void CmdStatus::setValueHex(int index, const char * label, long value)
{
    setLongValue(index, label, value, VT_HEX);
}

void CmdStatus::setLongValue(int index, const char * label, long value, ValueType vt)
{
    if ((index >= 0) && (index < MAX_VALUES))
    {
        values[index].label = label;
        values[index].value = value;
        values[index].valType = vt;
    }
}

bool CmdStatus::isClear()
{
    return level == SL_NONE;
}

void CmdStatus::printStatus()
{
    if (level == SL_NONE)
    {
        Serial.println("OK");
        return;
    }
    else if (level == SL_INFO)
    {
        Serial.print("INFO: ");
    }
    else {
        Serial.print("ERROR: ");
    }
    Serial.print(message);
    for (int ix = 0; ix < MAX_VALUES; ix++)
    {
        if (values[ix].valType != VT_NONE)
        {
            Serial.print("  ");
            Serial.print(values[ix].label);
            Serial.print("=");
            if (values[ix].valType == VT_DEC)
            {
                Serial.print(values[ix].value, DEC);
            }
            else
            {
                Serial.print("0x");
                Serial.print(values[ix].value, HEX);
            }
        }
    }
    Serial.println("");
}


