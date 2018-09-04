/**
 * @file lcdParallel.h
 *
 * @author Matthew Matz, Jeff Martin
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2018. All Rights MIT Licensed.
 *
 * @brief Display driver for character LCD screens based on Hitachi HD44780 
 * (or compatible) chipsets, which are found in most text-based LCDs. 
 * The library works with either 4 or 8 data lines in addition
 * to the rs, and enable lines.
 */

#ifndef LCDPARALLEL_H
#define LCDPARALLEL_H

#if defined(__cplusplus)
extern "C" {
#endif


// commands
#define LCDP_CLEARDISPLAY 0x01
#define LCDP_RETURNHOME 0x02
#define LCDP_ENTRYMODESET 0x04
#define LCDP_DISPLAYCONTROL 0x08
#define LCDP_CURSORSHIFT 0x10
#define LCDP_FUNCTIONSET 0x20
#define LCDP_SETCGRAMADDR 0x40
#define LCDP_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCDP_ENTRYRIGHT 0x00
#define LCDP_ENTRYLEFT 0x02
#define LCDP_ENTRYSHIFTINCREMENT 0x01
#define LCDP_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCDP_DISPLAYON 0x04
#define LCDP_DISPLAYOFF 0x00
#define LCDP_CURSORON 0x02
#define LCDP_CURSOROFF 0x00
#define LCDP_BLINKON 0x01
#define LCDP_BLINKOFF 0x00

// flags for display/cursor shift
#define LCDP_DISPLAYMOVE 0x08
#define LCDP_CURSORMOVE 0x00
#define LCDP_MOVERIGHT 0x04
#define LCDP_MOVELEFT 0x00

// flags for function set
#define LCDP_8BITMODE 0x10
#define LCDP_4BITMODE 0x00
#define LCDP_2LINE 0x08
#define LCDP_1LINE 0x00
#define LCDP_5x10DOTS 0x04
#define LCDP_5x8DOTS 0x00

// flag for command or write
#define LCDP_SEND_COMMAND 0x00
#define LCDP_SEND_WRITE 0x01


/**
 * @cond
 * Defines lcdParallel interface and setting masks struct
 */
typedef struct lcdParallel_st {
  int _rs_pin;     // LOW: command.  HIGH: character.
  int _enable_pin; // activated by a HIGH pulse.
  int _data_pins[8];
  
  char _displayfunction;
  char _displaycontrol;
  char _displaymode;
  
  char _numlines;
  char _row_offsets[4];
} lcdParallel_t;  

/**
 * Defines instance of lcdParallel for use with simplelibraries.
 */
typedef lcdParallel_t lcdParallel;


/**
 * @endcond
 */

/**
 * @brief initialize a parallel character LCD display into 4-wire mode.
 *
 * @param cols Number of columns on the character display.
 *
 * @param lines Number of lines on the character display.
 *
 * @param dotsize Number of pixels tall the characters are on the display.  
 * Most displays are 8, a few displays have 10 pixel tall characters.
 *
 * @param rs Register Select pin connect to the display's RS pin.
 *
 * @param enable Enable pin connect to the display's Enable pin.
 *
 * @param d0 Data pin 0 usually connected to the display's fifth data pin (for 4-wire mode).
 *
 * @param d1 Data pin 1 usually connected to the display's sixth data pin (for 4-wire mode).
 *
 * @param d2 Data pin 2 usually connected to the display's seventh data pin (for 4-wire mode).
 *
 * @param d3 Data pin 3 usually connected to the display's eigth data pin (for 4-wire mode).
 *
 * @returns lcdParallel device identifier for use with functions in the lcdParallel library. 
 */
lcdParallel *lcdParallel_init(char cols, char lines, char dotsize, char rs,
	    char enable, char d0, char d1, char d2, char d3);

/**
 * @brief initialize a parallel character LCD display into 8-wire mode.
 *
 * @param cols Number of columns on the character display.
 *
 * @param lines Number of lines on the character display.
 *
 * @param dotsize Number of pixels tall the characters are on the display.  
 * Most displays are 8, a few displays have 10 pixel tall characters.
 *
 * @param rs Register Select pin connect to the display's RS pin.
 *
 * @param enable Enable pin connect to the display's Enable pin.
 *
 * @param d0 Data pin 0 usually connected to the display's first data pin (for 8-wire mode).
 *
 * @param d1 Data pin 1 usually connected to the display's second data pin (for 8-wire mode).
 *
 * @param d2 Data pin 2 usually connected to the display's third data pin (for 8-wire mode).
 *
 * @param d3 Data pin 3 usually connected to the display's fourth data pin (for 8-wire mode).
 *
 * @param d4 Data pin 4 usually connected to the display's fifth data pin (for 8-wire mode).
 *
 * @param d5 Data pin 5 usually connected to the display's sixth data pin (for 8-wire mode).
 *
 * @param d6 Data pin 6 usually connected to the display's seventh data pin (for 8-wire mode).
 *
 * @param d7 Data pin 7 usually connected to the display's eigth data pin (for 8-wire mode).
 *
 * @returns lcdParallel device identifier for use with functions in the lcdParallel library. 
 */
lcdParallel *lcdParallel_init8(char cols, char lines, char dotsize, char rs,
	    char enable, char d0, char d1, char d2, char d3,
	    char d4, char d5, char d6, char d7);

/**
 * @brief Print format "..." args to the display. The output is limited to 128 bytes. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 * @param *fmt String which may contain formatters to be printed to the display.
 *
 */
int lcdParallel_print(lcdParallel *device, const char *fmt, ...);

/**
 * @brief Send a single ASCII character to the display. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 * @param value Character to send to the display.
 *
 */
void lcdParallel_writeChar(lcdParallel *device, char value);

/**
 * @brief Clears the display. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_clear(lcdParallel *device);

/**
 * @brief Sets the cursor to the Home (first column and first line) position. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_home(lcdParallel *device);

/**
 * @brief Turns the display off. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_noDisplay(lcdParallel *device);

/**
 * @brief Turns the display on. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_display(lcdParallel *device);

/**
 * @brief Makes the cursor solid (no blinking). 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_noBlink(lcdParallel *device);

/**
 * @brief Makes the cursor blink. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_blink(lcdParallel *device);

/**
 * @brief Turns the cursor off. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_noCursor(lcdParallel *device);

/**
 * @brief Turns the cursor on. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_cursor(lcdParallel *device);

/**
 * @brief Scrolls the text on the display to the left. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_scrollDisplayLeft(lcdParallel *device);

/**
 * @brief Scrolls the text on the display to the right. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_scrollDisplayRight(lcdParallel *device);

/**
 * @brief Causes the display to add new charaters to the right of the previous ones. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_leftToRight(lcdParallel *device);

/**
 * @brief Causes the display to add new charaters to the left of the previous ones. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_rightToLeft(lcdParallel *device);

/**
 * @brief Causes the display 'right justify' text from the cursor. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_autoscroll(lcdParallel *device);

/**
 * @brief Causes the display 'left justify' text from the cursor. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 */
void lcdParallel_noAutoscroll(lcdParallel *device);

/**
 * @brief Create and store a custom character in the display's CGRAM memory. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 * @param loc Memory location (0-7) to store the custom character.
 *
 * @param charmap[] map of the custom character's pixels.
 *
 */
void lcdParallel_createChar(lcdParallel *device, char loc, char charmap[]);

/**
 * @brief Sets the cursor to the specified location on the disply's screen. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 * @param col Column for the cursor to go to.
 *
 * @param row Line for the cursor to go to.
 *
 */
void lcdParallel_setCursor(lcdParallel *device, char col, char row); 

/**
 * @brief Low-level function used to transmit data to the display. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 * @param value Byte to send to the display.
 *
 * @param mode descibes whether the byte is a command or to be displayed.
 *
 */
void lcdParallel_send(lcdParallel *device, char value, char mode);

/**
 * @brief Low-level function used to transmit data to the display. 
 *
 * @param *device Device pointer returned by the lcdParallel_init or _init8 function.
 *
 * @param value Byte to send to the display.
 *
 * @param bits descibes whether the display is in 4- or 8-wire mode.
 *
 */
void lcdParallel_write(lcdParallel *device, char value, char bits);

#if defined(__cplusplus)
}
#endif
/* __cplusplus */ 
#endif
/* LCDPARALLEL_H */ 

/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
