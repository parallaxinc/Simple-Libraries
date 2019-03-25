/*
 * @file il3820_init.c
 *
 * @author Matthew Matz & Roy Eltham
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
 * terms of use (MIT License).
 *
 * @brief Waveshare ePaper display bitmap driver, see il3820_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "il3820.h"
#include "simpletools.h"


char _sdi, _dc, _clk, _rst;


screen_t *il3820_init(char sdi, char sclk, char cs, char rs, char rst, char busy, int _width, int _height) {
  
  screen_t* dev = (screen_t*) malloc(sizeof(screen_t));
  memset(dev, 0, sizeof(screen_t));

  unsigned char* _image = (char*) malloc(_width * ((_height + 7) >> 3));
  memset(_image, 0xff, (_width * ((_height + 7) >> 3)));
  
  strcpy(dev->color_depth, "R0G1B0");  // Set the color depth to monochrome

  dev->image_ptr = _image;
  dev->image_size = (_width * ((_height + 7) >> 3));  

  dev->dc_pin = rs;
  dev->sdi_pin = sdi;
  dev->clk_pin = sclk;
  dev->rst_pin = rst;
  
  dev->dev_id = cs;
  dev->status_pin = busy;
 
  dev->width = _width;
  dev->height = _height;
  dev->text_size = 1;
  dev->text_wrap = 1;
  dev->text_color = BLACK;
  dev->bg_color = BLACK;
  
  dev->deviceDrawPixel = il3820_drawPixel;
  dev->deviceDrawFastHLine = il3820_drawFastHLine;
  dev->deviceDrawFastVLine = il3820_drawFastVLine;

  dev->deviceInterface = INTF_SPI_WITH_BUFFER;     // interface type (bit 1) (1-i2c/0-SPI) and buffer (bit 0) (0-yes/1-no)

  dev->deviceClearDisplay = il3820_clearDisplay;
  dev->deviceUpdateDisplay = il3820_updateDisplay;  // Use if display needs to be updated (otherwise 0)
  dev->deviceResetDisplay = il3820_resetDisplay;
    
  i2c *eeBus = i2c_newbus(28, 29, 0); 
  loadFonts(dev, eeBus);

  // set pin directions
  set_direction(cs, 1);
  set_direction(rst, 1);
  set_direction(rs, 1);
  set_direction(sdi, 1);
  set_direction(sclk, 1);
  set_direction(busy, 0);
  
  il3820_resetDisplay(dev);
  il3820_clearDisplay(dev);
  il3820_updateDisplay(dev);  // Updates the display a second time to eliminate any ghosting from prior drawings

  return dev;
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

