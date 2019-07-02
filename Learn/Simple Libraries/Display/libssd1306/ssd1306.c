/*!
 * @file Adafruit_SSD1306.cpp
 *
 * @mainpage Arduino library for monochrome OLEDs based on SSD1306 drivers.
 *
 * @section intro_sec Introduction
 *
 * This is documentation for Adafruit's SSD1306 library for monochrome
 * OLED displays: http://www.adafruit.com/category/63_98
 *
 * These displays use I2C or SPI to communicate. I2C requires 2 pins
 * (SCL+SDA) and optionally a RESET pin. SPI requires 4 pins (MOSI, SCK,
 * select, data/command) and optionally a reset pin. Hardware SPI or
 * 'bitbang' software SPI are both supported.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section dependencies Dependencies
 *
 * This library depends on <a href="https://github.com/adafruit/Adafruit-GFX-Library">
 * Adafruit_GFX</a> being present on your system. Please make sure you have
 * installed the latest version before using this library.
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries, with
 * contributions from the open source community.
 *
 * @section license License
 *
 * BSD license, all text above, and the splash screen included below,
 * must be included in any redistribution.
 *
 */

#include "ssd1306.h"



screen_t* ssd1306_openI2C(i2c *dev_bus, unsigned char addr, unsigned char vcs, int _width, int _height) {

  screen_t* dev = (screen_t*) malloc(sizeof(screen_t));
  memset(dev, 0, sizeof(screen_t));

  dev->dev_id = addr;
  dev->deviceBus = dev_bus;
  dev->deviceInterface = INTF_I2C_WITH_BUFFER;     // interface type (bit 1) (1-i2c/0-SPI) and buffer (bit 0) (0-yes/1-no)
  dev->status_pin = vcs;
  dev->rst_pin = -1;

  dev->width = _width;
  dev->height = _height;

  ssd1306_begin(dev);
  return dev;
}


screen_t* ssd1306_openSPI(char sdi, char clk, char rst, char dc, char cs, unsigned char vcs, int _width, int _height) {

  screen_t* dev = (screen_t*) malloc(sizeof(screen_t));
  memset(dev, 0, sizeof(screen_t));

  dev->dev_id = cs;
  dev->deviceInterface = INTF_SPI_WITH_BUFFER;

  dev->width = _width;
  dev->height = _height;
  
  dev->status_pin = vcs;
  dev->sdi_pin = sdi;
  dev->clk_pin = clk;
  dev->rst_pin = rst;
  dev->dc_pin = dc;
  
  // set pin directions
  low(clk);
  low(sdi);
  high(cs);
  low(dc);

  ssd1306_begin(dev);
  return dev;
}
  

void ssd1306_begin(screen_t* dev) {
  
  unsigned char* _image = (char*) malloc(dev->width * ((dev->height + 7) >> 3));
  memset(_image, 0x00, (dev->width * ((dev->height + 7) >> 3)));

  dev->image_ptr = _image;
  dev->image_size = (dev->width * ((dev->height + 7) >> 3));  

  i2c *eeBus = i2c_newbus(28, 29, 0);
  loadFonts(dev, eeBus);

  dev->text_size = 1;
  dev->text_wrap = 1;
  dev->text_color = WHITE;
  dev->bg_color = WHITE;
  dev->color_depth = 1;
  
  dev->deviceDrawPixel = ssd1306_drawPixel;
  dev->deviceDrawFastHLine = ssd1306_drawFastHLine;
  dev->deviceDrawFastVLine = ssd1306_drawFastVLine;

  dev->deviceClearDisplay = ssd1306_clearDisplay;
  dev->deviceUpdateDisplay = ssd1306_updateDisplay;
  dev->deviceResetDisplay = ssd1306_resetDisplay;

  // reset SSD1306 if requested and reset pin specified in constructor
  if(dev->rst_pin > -1 && dev->rst_pin < 32) {
    high(dev->rst_pin);
    pause(1);     
    low(dev->rst_pin);  // bring reset low
    pause(10);          
    high(dev->rst_pin); // bring out of reset
  }

  // init sequence for SSD1306 OLED module
  unsigned char ctrst = 0x8F;
  if (dev->height == 64) ctrst = (dev->status_pin == SSD1306_EXTERNALVCC ? 0x9F : 0xCF);
  if (dev->height == 16) ctrst = (dev->status_pin == SSD1306_EXTERNALVCC ? 0x10 : 0xAF);
  
  ssd1306_write(dev, SSD1306_DISPLAYOFF, 0);
  ssd1306_write(dev, SSD1306_SETLOWCOLUMN, 0);        // low col = 0
  ssd1306_write(dev, SSD1306_SETHIGHCOLUMN, 0);       // hi col = 0
  ssd1306_write(dev, SSD1306_SETSTARTLINE, 0);        // line #0
  ssd1306_write(dev, SSD1306_SETCONTRAST, 0);
  ssd1306_write(dev, ctrst, 0);
  ssd1306_write(dev, 161, 0);
  ssd1306_write(dev, SSD1306_NORMALDISPLAY, 0);
  ssd1306_write(dev, SSD1306_DISPLAYALLON_RESUME, 0);
  ssd1306_write(dev, SSD1306_SETMULTIPLEX, 0);
  ssd1306_write(dev, 63, 0);
  ssd1306_write(dev, SSD1306_SETDISPLAYOFFSET, 0);    // No offset                            
  ssd1306_write(dev, 0, 0);
  ssd1306_write(dev, SSD1306_SETDISPLAYCLOCKDIV, 0);
  ssd1306_write(dev, 128, 0);
  ssd1306_write(dev, SSD1306_SETPRECHARGE, 0);
  ssd1306_write(dev, (dev->status_pin == SSD1306_EXTERNALVCC ? 34 : 241), 0);
  ssd1306_write(dev, SSD1306_SETVCOMDETECT, 0);
  ssd1306_write(dev, 64, 0);
  ssd1306_write(dev, SSD1306_SETCOMPINS, 0);
  ssd1306_write(dev, (dev->height == 64 ? 18 : 2), 0);
  ssd1306_write(dev, SSD1306_MEMORYMODE, 0);
  ssd1306_write(dev, 0, 0);
  ssd1306_write(dev, (SSD1306_SEGREMAP | 0x1), 0);
  ssd1306_write(dev, SSD1306_COMSCANDEC, 0);
  ssd1306_write(dev, SSD1306_CHARGEPUMP, 0);
  ssd1306_write(dev, (dev->status_pin == SSD1306_EXTERNALVCC ? 16 : 20), 0);
  ssd1306_write(dev, SSD1306_DISPLAYON, 0);           // turn on oled panel
  ssd1306_write(dev, SSD1306_NORMALDISPLAY, 0);       // Ensure screen is not inverted
}