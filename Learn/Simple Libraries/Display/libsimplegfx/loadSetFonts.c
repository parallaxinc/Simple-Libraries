/*
 * @file loadSetFonts.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2019.  See end of file for
 * terms of use (MIT License).
 *
 * @brief This is a driver that allows the Propeller Multicore Microcontroller to 
 * draw text, shapes, and bitmap files on various screens and displays.
 *
 * @detail This helper-library allows the Propeller Multicore Microcontroller to 
 * draw pixels, lines, circles, recatngles, rounded rectagles, triangles, formatted text 
 * in multiple fonts, bitmap images stored on an SD card on various screens and displays. 
 * At Parallax, we would like to thank Adafruit Industries as parts of this library 
 * were dervied from the Adafruit GFX library for Arduino.  Please submit bug reports, 
 * suggestions, and improvements to this code to editor@parallax.com.
 * 
 * @note If fonts are installed, they occupy EEPROM addresses 40576 to 63359.
 */

#include "simplegfx.h"


void loadFonts(screen_t *dev, i2c *eeBus) {
  dev->eepromBus = eeBus;
  
  //check if fonts are installed in EEPROM, and set the default font if they are
  dev->font[0] = 0;
  char testStr[] = {0,0,0,0,0,0};  
  i2c_in(dev->eepromBus, 0b1010000, 43640, 2, testStr, 6);
  if (testStr[0] == 'f' && 
      testStr[1] == 'o' && 
      testStr[2] == 'n' && 
      testStr[3] == 't' && 
      testStr[4] == 's' && 
      testStr[5] == '!')  {
     
    // Set a default font by setting EEPROM addresses
    dev->font[0] = 1;
    setTextFont(dev, 0);
  }    
}  

void setTextFont(screen_t *dev, char f) {
  
  if( f == 3 )        // Bubble
  {
    dev->font[1] = 44544;	
    dev->font[2] = 44416;	
    dev->font[3] = 43648;	
    dev->font[4] = 40576;	
  }
  else if ( f == 2 )  // Serif
  {      
	 dev->font[1] = 50048;
	 dev->font[2] = 49920;
	 dev->font[3] = 49152;
	 dev->font[4] = 46720;
  }
  else if ( f == 1 )  // Script
  {      
    dev->font[1] = 55552;
    dev->font[2] = 55424;
    dev->font[3] = 54656;
    dev->font[4] = 52224;
  }
  else                // Sans
  {      
    dev->font[1] = 61184;
    dev->font[2] = 61056;
    dev->font[3] = 60288;
    dev->font[4] = 57728;
  }    
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
