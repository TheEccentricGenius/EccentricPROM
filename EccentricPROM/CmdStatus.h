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

/**
 * Command Status class
 *
 * Creates an object that holds an error message and a number of
 * optional numeric values.  Each value has a format (hex,
 * decimal) and a label.  The printStatus call formats all of
 * the data in the command status and prints it out to the
 * serial port.
 */
class CmdStatus
{
  public:
    CmdStatus();
    void clear();
    void info(const char * msg);
    void error(const char * msg);
    void setValueDec(int index, const char * label, long value);
    void setValueHex(int index, const char * label, long value);

    bool isClear();
    void printStatus();

private:
    enum
    {
        MAX_VALUES = 5
    };
    enum StatusLevel { SL_NONE, SL_INFO, SL_ERROR };
    enum ValueType { VT_NONE, VT_DEC, VT_HEX };

    struct StatusValue
    {
        const char * label;
        ValueType valType;
        long      value;
    };

    StatusLevel level;
    const char * message;
    StatusValue values[MAX_VALUES];

    void setLongValue(int index, const char * label, long value, ValueType vt);
};
