/**
 * @file lcdParallel_init.c
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


#include "lcdParallel.h"
#include "simpletools.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Propeller doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).


lcdParallel* lcdParallel_init(char cols, char lines, char dotsize, char rs, char enable,
			 char d0, char d1, char d2, char d3)
{
  return lcdParallel_init8(cols, lines, dotsize, rs, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}  

lcdParallel* lcdParallel_init_i2c(char cols, char lines, char dotsize, char sda, char scl) {
  
}  

lcdParallel* lcdParallel_init8(char cols, char lines, char dotsize, char rs, char enable,
			 char d0, char d1, char d2, char d3,
			 char d4, char d5, char d6, char d7)
{
  lcdParallel* device = (lcdParallel*) malloc(sizeof(lcdParallel));
  memset(device, 0, sizeof(lcdParallel));

  device->_rs_pin = rs;
  device->_enable_pin = enable;
  
  device->_data_pins[0] = d0;
  device->_data_pins[1] = d1;
  device->_data_pins[2] = d2;
  device->_data_pins[3] = d3; 
  device->_data_pins[4] = d4;
  device->_data_pins[5] = d5;
  device->_data_pins[6] = d6;
  device->_data_pins[7] = d7; 

  if (d4 == d5 & d5 == d6 & d6 == d7) {
    device->_displayfunction = LCDP_4BITMODE | LCDP_1LINE | LCDP_5x8DOTS;
  } else { 
    device->_displayfunction = LCDP_8BITMODE | LCDP_1LINE | LCDP_5x8DOTS;
  }
    
  if (dotsize != 10) {
    dotsize = LCDP_5x8DOTS;
  } else {
    dotsize = LCDP_5x10DOTS;
  }    
  if (lines > 1) {
    device->_displayfunction |= LCDP_2LINE;
  }

  device->_numlines = lines;

  device->_row_offsets[0] = 0x00;
  device->_row_offsets[1] = 0x40;
  device->_row_offsets[2] = 0x00 + cols;
  device->_row_offsets[3] = 0x40 + cols;

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCDP_5x8DOTS) && (lines == 1)) {
    device->_displayfunction |= LCDP_5x10DOTS;
  }

  low(device->_rs_pin);
  low(device->_enable_pin);
    
  // Do these once, instead of every time a character is drawn for speed reasons.
  low(device->_data_pins[0]);
  low(device->_data_pins[1]);
  low(device->_data_pins[2]);
  low(device->_data_pins[3]); 
  if (device->_displayfunction & LCDP_8BITMODE) {
    low(device->_data_pins[4]);
    low(device->_data_pins[5]);
    low(device->_data_pins[6]);
    low(device->_data_pins[7]); 
  }    

  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. MCU can turn on earlier so we'll wait 50
  pause(50); 

  // Now we pull both RS and R/W low to begin commands
  low(device->_rs_pin);
  low(device->_enable_pin);

  
  //put the LCD into 4 bit or 8 bit mode
  if (!(device->_displayfunction & LCDP_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    lcdParallel_write(device, 0x03, 4);
    usleep(4500); // wait min 4.1ms

    // second try
    lcdParallel_write(device, 0x03, 4);
    usleep(4500); // wait min 4.1ms
    
    // third go!
    lcdParallel_write(device, 0x03, 4); 
    usleep(150);

    // finally, set to 4-bit interface
    lcdParallel_write(device, 0x02, 4); 
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    lcdParallel_send(device, LCDP_FUNCTIONSET | device->_displayfunction, LCDP_SEND_COMMAND);
    usleep(4500);  // wait more than 4.1ms

    // second try
    lcdParallel_send(device, LCDP_FUNCTIONSET | device->_displayfunction, LCDP_SEND_COMMAND);
    usleep(150);

    // third go
    lcdParallel_send(device, LCDP_FUNCTIONSET | device->_displayfunction, LCDP_SEND_COMMAND);
  }

  // finally, set # lines, font size, etc.
  lcdParallel_send(device, LCDP_FUNCTIONSET | device->_displayfunction, LCDP_SEND_COMMAND);  

  // turn the display on with no cursor or blinking default
  device->_displaycontrol = LCDP_DISPLAYON | LCDP_CURSOROFF | LCDP_BLINKOFF;  
  lcdParallel_display(device);

  // clear it off
  lcdParallel_clear(device);

  // Initialize to default text direction (for romance languages)
  device->_displaymode = LCDP_ENTRYLEFT | LCDP_ENTRYSHIFTDECREMENT;
  // set the entry mode
  lcdParallel_send(device, LCDP_ENTRYMODESET | device->_displaymode, LCDP_SEND_COMMAND);
  
  return device;

}

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
