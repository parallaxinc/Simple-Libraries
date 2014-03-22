/**
 * @file simpletext.h
 * Simple Terminal Library API definition.
 *
 * This library is provided with the following in mind:
 *
 * - Designed for minimum size with generic IO devices.
 * - Designed for any character IO device using rxChar/txChar functions.
 * - Contains 2 built-in device drivers FdSerial and SimpleSerial.
 * - Supports get/print decimal, binary, float, hex, char, and string.
 * - Supports print format values to buffer comparable to sprintf (printBuffFormat).
 * - Supports scan  format values from buffer comparable to sscanf (scanBuffFormat).
 *
 * Copyright (C) 2013, Parallax Inc.
 * Written by Steve Denson
 * See end of file for terms of use.
 */
#ifndef __SimpleTEXT__
#define __SimpleTEXT__

#include <propeller.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__PROPELLER_32BIT_DOUBLES__)
#error "This library requires 32bit doubles"
#endif

#define TERM_NAME_LEN 20
#define TERM_COG_LEN  7

typedef struct text_struct
{
  int  (*rxChar)(struct text_struct *p);            /* required for terminal to work */
  int  (*txChar)(struct text_struct *p, int ch);    /* required for terminal to work */
  int  cogid[TERM_COG_LEN];                         /* pointer to cog(s) used if any */
  volatile void *devst;                             /* pointer to device info struct */
} text_t;

#define getStopCOGID(id) ((id)-(1))
#define setStopCOGID(id) ((id)+(1))

/**
 * By default the terminal will use simple serial for input/output
 * It can be overloaded.
 */
#include "serial.h"

/* Values for use with SimpleIDE Terminal */
#ifndef HOME
#define HOME   (1)
#endif
#ifndef CRSRXY
#define CRSRXY (2)
#endif
#ifndef CRSRLF
#define CRSRLF (3)
#endif
#ifndef CRSRRT
#define CRSRRT (4)
#endif
#ifndef CRSRUP
#define CRSRUP (5)
#endif
#ifndef CRSRDN
#define CRSRDN (6)
#endif
#ifndef BEEP
#define BEEP   (7)
#endif
#ifndef BKSP
#define BKSP   (8)
#endif
#ifndef TAB
#define TAB    (9)
#endif
#ifndef NL
#define NL     (10)
#endif
#ifndef LF
#define LF     (10)
#endif
#ifndef CLREOL
#define CLREOL (11)
#endif
#ifndef CLRDN
#define CLRDN  (12)
#endif
#ifndef CR
#define CR     (13)
#endif
#ifndef CRSRX
#define CRSRX  (14)
#endif
#ifndef CRSRY
#define CRSRY  (15)
#endif
#ifndef CLS
#define CLS    (16)
#endif

typedef text_t terminal;

/**
 * This function is opened by default when the library is used.
 * The port by default transmits on P30 and receives on P31 at 115200 bps.
 * The port is a simple serial driver and does not buffer bytes.
 *
 * Users do not have to call this unless the termial has been closed.
 * @returns 0 if port is already open, else returns term pointer.
 */
terminal *simpleterm_open(void);

/**
 * This function is provided if a different default driver is to be used.
 * The function should be called before opening another driver.
 */
void      simpleterm_close(void);

/**
 * This returns the default debug port device.
 */
terminal *simpleterm_pointer(void);

/**
 * This sets default debug port device to ptr.
 * User should declare and initialize the device before calling the function.
 * @param ptr is a serial, fdserial, or other text_t device.
 */
static inline void simpleterm_reset(text_t *ptr)
{
  extern text_t *dport_ptr;
  simpleterm_close();
  dport_ptr = ptr;
}

/**
 * Get a binary number from the debug port.
 * @returns number received.
 */
int  getBin(void);

/**
 * Get a char from the debug port.
 * @returns character received as an integer.
 */
int  getChar(void);

/**
 * Get a decimal number from the debug port.
 * @returns number received.
 */
int  getDec(void);

/**
 * Get a floating point number from the debug port.
 * @returns number received.
 */
float getFloat(void);

/**
 * Get a hexadecimal number from the debug port.
 * @returns number received.
 */
int  getHex(void);

/**
 * Get a string of chars from the debug port.
 * @param buffer is a previously declared array of char big enough to hold the input string plus 2 null terminators.
 * @param max is the maximum size to read and should be less or equal buffer size.
 * @returns string received.
 */
char *getStr(char *buffer, int max);

/**
 * Print a string representation of a binary number to the debug port.
 * @param value is number to print. 
 * @param digits is number of characters to print. 
 */
void putBin(int value);
/**
 * Print a string representation of a binary number to debug output
 * @param value is number to print. 
 * @param digits is number of characters to print. 
 */
void putBinDigits(int value, int digits);
/**
 * Send a char on the debug port.
 * @param c is the char to send. 
 */
void putChar(char c);
/**
 * Print a string representation of a decimal number to the debug port.
 * @param value is number to print. 
 */
void putDec(int value);
/**
 * Print a string representation of a decimal number to the debug port.
 * @param value is number to print. 
 * @param width is number of characters to print padded by zeros. 
 */
void putDecDigits(int value, int width);
/**
 * Print a string representation of a 32 bit floating point number to the debug port.
 * @param value is number to print. 
 */
void putFloat(float value);
/**
 * Print a string representation of a hexadecimal number to the debug port.
 * @param value is number to print. 
 * @param digits is number of characters to print. 
 */
void putHex(int value);
/**
 * Print a string representation of a hexadecimal number to the debug port.
 * @param value is number to print. 
 * @param digits is number of hexadecimal characters to print padded by zeros. 
 */
void putHexDigits(int value, int digits);
/**
 * Print a string representation of a 32 bit floating point number to the debug port.
 * @param width is number of characters to print. 
 * @param precision is number of decimal point digits to print. 
 * @param value is number to print. 
 */
void putFloatPrecision(float value, int width, int precision);
/**
 * Send a string + new line on the transmit debug port.
 * @param str is the null terminated string to send. 
 */
int  putln(const char* str);
/**
 * Send a string + new line on the transmit debug port. This is an alias of putln.
 * @param str is the null terminated string to send. 
 */
int  putLine(const char* str);
/**
 * Send a string on the transmit debug port.
 * @param str is the null terminated string to send. 
 */
int  putStr(const char* str);

/**
 * Get a binary number from the receive device.
 * @param device is a previously open/started terminal device.
 * @returns number received.
 */
int  readBin(text_t *device);

/**
 * Get a char from the receive device.
 * @param device is a previously open/started terminal device.
 * @returns character received as an integer.
 */
int  readChar(text_t *device);

/**
 * Get a decimal number from the receive device.
 * @param device is a previously open/started terminal device.
 * @returns number received.
 */
int  readDec(text_t *device);

/**
 * Get a floating point number from the receive device.
 * @param device is a previously open/started terminal device.
 * @returns number received.
 */
float readFloat(text_t *device);

/**
 * Get a hexadecimal number from the receive device.
 * @param device is a previously open/started terminal device.
 * @returns number received.
 */
int  readHex(text_t *device);

/**
 * Get a string of chars from the receive device.
 * @param device is a previously open/started terminal device.
 * @param buffer is a previously declared array of char big enough to hold the input string.
 * @param max is the maximum size to read and should be less or equal buffer size.
 * @returns string received.
 */
char *readStr(text_t *device, char *buffer, int max);

/**
 * Print a string representation of a binary number to the debug port.
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 */
void writeBin(text_t *device, int value);
/**
 * Print a string representation of a binary number to output
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 * @param digits is number of characters to print. 
 */
void writeBinDigits(text_t *device, int value, int digits);
/**
 * Send a char on the transmit device.
 * @param device is a previously open/started terminal device.
 * @param c is the char to send. 
 */
void writeChar(text_t *device, char c);
/**
 * Print a string representation of a decimal number to output
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 */
void writeDec(text_t *device, int value);
/**
 * Print a string representation of a decimal number to output
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 * @param width is number of characters to print padded by spaces. 
 */
void writeDecDigits(text_t *device, int value, int width);
/**
 * Print a string representation of a 32 bit floating point number to device
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 */
void writeFloat(text_t *device, float value);
/**
 * Print a string representation of a hexadecimal number to output
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 */
void writeHex(text_t *device, int value);
/**
 * Print a string representation of a hexadecimal number to output
 * @param device is a previously open/started terminal device.
 * @param value is number to print. 
 * @param digits is number of hexadecimal characters to print. 
 */
void writeHexDigits(text_t *device, int value, int digits);
/**
 * Print a string representation of a 32 bit floating point number to device
 * @param device is a previously open/started terminal device.
 * @param width is number of characters to print. 
 * @param precision is number of decimal point digits to print. 
 * @param value is number to print. 
 */
void writeFloatPrecision(text_t *device, float value, int width, int precision);
/**
 * Send a string + new line on the transmit device.
 * @param device is a previously open/started terminal device.
 * @param str is the null terminated string to send. 
 */
int  writeLine(text_t *device, char* str);
/**
 * Send a string on the transmit device.
 * @param device is a previously open/started terminal device.
 * @param str is the null terminated string to send. 
 */
int  writeStr(text_t *device, char* str);
/**
 * Send a string on the transmit device.
 * @param device is a previously open/started terminal device.
 * @param str is the null terminated string to send. 
 * @param width is number of characters to print padded by spaces. 
 */
int  writeStrDigits(text_t *device, char* str, int width);

/**
 * Print format "..." args to the default simple terminal device.
 * The output is limited to 256 bytes.
 *
 * Format specifiers for print dprint, and sprint:
 *
 * - %%
 * Prints the % sign to the output.
 *
 * - %b
 * Prints the binary representation of the int parameter.
 * Note that %b is not an ANSI standard format specifier.
 *
 * - %c
 * Prints the char representation of the int parameter.
 *
 * - %d
 * Prints the integer representation of the int parameter.
 *
 * - %f
 * Prints the floating point representation of the float parameter.
 *
 * - %s
 * Prints the string representation of the char* parameter.
 *
 * - %u
 * Prints the unsigned integer representation of the int parameter.
 *
 * - %x
 * Prints the hexadecimal integer representation of the int parameter.
 *
 * Width and precision %n.p cause n digits of the integer to print, and
 * p digits of the decimal to print.
 *
 * @param format is a C printf comparable format string.
 * @param ... is the arguments to use with the format string.
 * returns the number of bytes placed into the buffer.
 */
int print(const char *format, ...) __attribute__((format (printf, 1, 2)));

/**
 * Print integer and char only format "..." args to the default simple terminal device.
 * This version does not support floating point.
 * The output is limited to 256 bytes.
 *
 * @note See print for format specifiers except %f.
 *
 * @param format is a C printf comparable format string.
 * @param ... is the arguments to use with the format string.
 * returns the number of bytes placed into the buffer.
 */
int printi(const char *format, ...) __attribute__((format (printf, 1, 2)));

/**
 * Convert formatted simple terminal input to the "..." args.
 * The input is limited to 256 bytes.
 *
 * Format specifiers for scan, dscan, and sscan:
 *
 * - %%
 * Scan the % sign to the input.
 *
 * - %b
 * Scans the binary representation to the int parameter.
 * Note that %b is not an ANSI standard format specifier.
 *
 * - %c
 * Scans the char representation to the int parameter.
 *
 * - %d
 * Scans the integer representation to the int parameter.
 *
 * - %f
 * Scans the floating point representation to the float parameter.
 *
 * - %s
 * Scans the string representation to the char* parameter.
 *
 * - %u
 * Scans the unsigned integer representation to the int parameter.
 *
 * - %x
 * Scans the hexadecimal integer representation to the int parameter.
 *
 * Width and precision %n.p cause n digits to the integer to print, and
 * p digits to the decimal to print.
 *
 * @param format is a C printf comparable format string.
 * @param ... is the arguments where output will go and must be pointers.
 * returns the number of bytes placed into the buffer.
 */
int scan(const char *fmt, ...) __attribute__((format (printf, 1, 2)));

/**
 * Convert formatted simple terminal input to the "..." args.
 * This version does not provide floating point conversions.
 * The input is limited to 256 bytes.
 *
 * @note See scan for format specifiers.
 *
 * @param format is a C printf comparable format string.
 * @param ... is the arguments where output will go and must be pointers.
 * returns the number of bytes placed into the buffer.
 */
int scani(const char *fmt, ...) __attribute__((format (printf, 1, 2)));

/**
 * Print format "..." args to the device
 * The output is limited to 256 bytes.
 *
 * @note See print for format specifiers.
 *
 * @param device is where to put the formatted output.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments to use with the format string.
 * returns the number of bytes placed into the buffer.
 */
int dprint(text_t* device, const char *format, ...) __attribute__((format (printf, 2, 3)));

/**
 * Print integer and char only format "..." args to the default simple terminal device.
 * This version does not support floating point.
 * The output is limited to 256 bytes.
 *
 * @note See print for format specifiers except %f.
 *
 * @param device is where to put the formatted output.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments to use with the format string.
 * returns the number of bytes placed into the buffer.
 */
int dprinti(text_t* device, const char *format, ...) __attribute__((format (printf, 2, 3)));


/**
 * Convert formatted device input to the "..." args.
 * The input is limited to 256 bytes.
 *
 * @note See scan for format specifiers.
 *
 * @param device is where to get the formatted input.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments where output will go and must be pointers.
 * returns the number of bytes placed into the buffer.
 */
int dscan(text_t* device, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

/**
 * Convert formatted device input to the "..." args.
 * This version does not provide floating point conversions.
 * The input is limited to 256 bytes.
 *
 * @note See scan for format specifiers.
 *
 * @param device is where to get the formatted input.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments where output will go and must be pointers.
 * returns the number of bytes placed into the buffer.
 */
int dscani(text_t* device, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

/**
 * Print format "..." args to the output buffer.
 * The output buffer *must be* big enough for the output.
 *
 * @note See print for format specifiers.
 *
 * @param buffer is where to put the formatted output.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments to use with the format string.
 * returns the number of bytes placed into the buffer.
 */
int sprint(char *buffer, const char *format, ...) __attribute__((format (printf, 2, 3)));

/**
 * Print integer and char only format "..." args to the default simple terminal device.
 * This version does not support floating point.
 * The output is limited to 256 bytes.
 *
 * @note See print for format specifiers except %f.
 *
 * @param buffer is where to put the formatted output.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments to use with the format string.
 * returns the number of bytes placed into the buffer.
 */
int sprinti(char *buffer, const char *format, ...) __attribute__((format (printf, 2, 3)));


/**
 * Convert formatted buffer to the "..." args.
 *
 * @note See scan for format specifiers.
 *
 * @param buffer is where to put the formatted output.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments where output will go and must be pointers.
 * returns the number of bytes placed into the buffer.
 */
int sscan(const char *buffer, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

/**
 * Convert formatted buffer to the "..." args.
 * This version does not provide floating point conversions.
 *
 * @note See scan for format specifiers.
 *
 * @param buffer is where to put the formatted output.
 * @param format is a C printf comparable format string.
 * @param ... is the arguments where output will go and must be pointers.
 * returns the number of bytes placed into the buffer.
 */
int sscani(const char *buffer, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

/*  API not intended for public use */
int   printNumber(text_t *p, unsigned long u, int base, int width, int fill_char);
char* _safe_gets(text_t *term, char* origBuf, int count);
const char* _scanf_getf(const char *str, float* dst);
const char* _scanf_getl(const char *str, int* dst, int base, unsigned width, int isSigned);

int SPUTC(int c, char *buf);
int SPUTS(char *s, char *obuf);
int SPUTL(unsigned long u, int base, int width, int fill_char, char *obuf);

#include <stdarg.h>
int   _doscanf(const char* str, const char *fmt, va_list args);
int   _intscanf(const char* str, const char *fmt, va_list args);
int   _dosprnt(const char *fmt, va_list args, char *obuf);
int   _intsprnt(const char *fmt, va_list args, char *obuf);

char* float2string(float f, char *s, int width, int precision);
float string2float(char *s, char **end);

#ifdef __cplusplus
}
#endif

#endif
/* __SimpleTEXT__ */

/*
+--------------------------------------------------------------------
| TERMS OF USE: MIT License
+--------------------------------------------------------------------
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
+--------------------------------------------------------------------
*/
