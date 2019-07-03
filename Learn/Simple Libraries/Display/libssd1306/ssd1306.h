


#ifndef _SSD1306_H_
#define _SSD1306_H_

#if defined(__cplusplus)                      // If compiling for C++
extern "C" {                                  // Compile for C
#endif


#include "simpletools.h"
#include "simplegfx.h"

#ifndef BLACK
  #define BLACK                          0 ///< Draw 'off' pixels
#endif

#ifndef WHITE
  #define WHITE                          1 ///< Draw 'on' pixels
#endif

#ifndef INVERSE
  #define INVERSE                        2 ///< Invert pixels
#endif


#ifndef SSD1306_MEMORYMODE
  #define SSD1306_MEMORYMODE          0x20
#endif

#ifndef SSD1306_COLUMNADDR
  #define SSD1306_COLUMNADDR          0x21
#endif

#ifndef SSD1306_PAGEADDR
  #define SSD1306_PAGEADDR            0x22
#endif

#ifndef SSD1306_SETCONTRAST
  #define SSD1306_SETCONTRAST         0x81
#endif

#ifndef SSD1306_CHARGEPUMP
  #define SSD1306_CHARGEPUMP          0x8D
#endif

#ifndef SSD1306_SEGREMAP
  #define SSD1306_SEGREMAP            0xA0
#endif

#ifndef SSD1306_DISPLAYALLON_RESUME
  #define SSD1306_DISPLAYALLON_RESUME 0xA4
#endif

#ifndef SSD1306_DISPLAYALLON
  #define SSD1306_DISPLAYALLON        0xA5
#endif

#ifndef SSD1306_NORMALDISPLAY
  #define SSD1306_NORMALDISPLAY       0xA6
#endif

#ifndef SSD1306_INVERTDISPLAY
  #define SSD1306_INVERTDISPLAY       0xA7
#endif

#ifndef SSD1306_SETMULTIPLEX
  #define SSD1306_SETMULTIPLEX        0xA8
#endif

#ifndef SSD1306_DISPLAYOFF
  #define SSD1306_DISPLAYOFF          0xAE
#endif

#ifndef SSD1306_DISPLAYON
  #define SSD1306_DISPLAYON           0xAF
#endif

#ifndef SSD1306_COMSCANINC
  #define SSD1306_COMSCANINC          0xC0
#endif

#ifndef SSD1306_COMSCANDEC
  #define SSD1306_COMSCANDEC          0xC8
#endif

#ifndef SSD1306_SETDISPLAYOFFSET
  #define SSD1306_SETDISPLAYOFFSET    0xD3
#endif

#ifndef SSD1306_SETDISPLAYCLOCKDIV
  #define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#endif

#ifndef SSD1306_SETPRECHARGE
  #define SSD1306_SETPRECHARGE        0xD9
#endif

#ifndef SSD1306_SETCOMPINS
  #define SSD1306_SETCOMPINS          0xDA
#endif

#ifndef SSD1306_SETVCOMDETECT
  #define SSD1306_SETVCOMDETECT       0xDB
#endif


#ifndef SSD1306_SETLOWCOLUMN
  #define SSD1306_SETLOWCOLUMN        0x00
#endif

#ifndef SSD1306_SETHIGHCOLUMN
  #define SSD1306_SETHIGHCOLUMN       0x10
#endif

#ifndef SSD1306_SETSTARTLINE
  #define SSD1306_SETSTARTLINE        0x40
#endif


#ifndef SSD1306_EXTERNALVCC
  #define SSD1306_EXTERNALVCC         0x01 // External display voltage source
#endif

#ifndef SSD1306_SWITCHCAPVCC
  #define SSD1306_SWITCHCAPVCC        0x02 // Generic display voltage from 3.3V
#endif


#ifndef SSD1306_RIGHT_HORIZONTAL_SCROLL
  #define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26 ///< Init rt scroll
#endif

#ifndef SSD1306_LEFT_HORIZONTAL_SCROLL
  #define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27 ///< Init left scroll
#endif

#ifndef SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL
  #define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#endif

#ifndef SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL
  #define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A ///< Init diag scroll
#endif

#ifndef SSD1306_DEACTIVATE_SCROLL
  #define SSD1306_DEACTIVATE_SCROLL                    0x2E ///< Stop scroll
#endif

#ifndef SSD1306_ACTIVATE_SCROLL
  #define SSD1306_ACTIVATE_SCROLL                      0x2F ///< Start scroll
#endif

#ifndef SSD1306_SET_VERTICAL_SCROLL_AREA
  #define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 ///< Set scroll range
#endif






/**
 * @brief Initializes the OLED screen by setting up it's SPI and control pins.
 *
 * @param dev_bus TODO
 *
 * @param addr TODO
 *
 * @param vcs TODO
 *
 * @param screenWidth TODO
 *
 * @param screenHeight TODO
 */
screen_t*    ssd1306_openI2C(i2c* dev_bus, unsigned char addr, unsigned char vcs, int screenWidth, int screenHeight);

/**
 * @brief Initializes the OLED screen by setting up it's SPI and control pins.
 *
 * @param SDI which pin is connected to the Serial Data In pin, marked "DIN".
 *
 * @param CLK which pin is connected to the Serial Clock pin, marked "CLK".
 *
 * @param res TODO
 *
 * @param dc TODO
 *
 * @param CS which pin is connected to the Chip Select pin, marked "CS".
 *
 * @param VCS TODO
 *
 * @param _width TODO
 *
 * @param _height TODO
 */
screen_t*    ssd1306_openSPI(char sdi, char clk, char res, char dc, char cs, unsigned char vcs, int _width, int _height);

/**
 * @brief Initializes the OLED screen by setting up it's SPI and control pins.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void         ssd1306_begin(screen_t* dev);

/**
 * @brief: update the display with whatever is in the frame memory.
 *          You need to have updated the frame memory with _image first
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void         ssd1306_updateDisplay(screen_t* dev);

/**
 * @brief Clears (sets to black) a rectangular area of the screen
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void         ssd1306_clearDisplay(screen_t* dev);

/**
 * @brief: TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void         ssd1306_resetDisplay(screen_t* dev);

/**
 * @brief Inverts the screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param i TODO
 */
void         ssd1306_invertDisplay(screen_t* dev, char i);

/**
 * @brief TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param dim TODO
 */
 
void         ssd1306_dim(screen_t* dev, char dim);

/**
 * @brief Draws a single pixel on the screen in the specified color. No checking.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Horizontal coordinate of the pixel, counted from the left side of the screen.
 *
 * @param y Vertical coordinate of the pixel, counted down from the top of the screen.
 *
 * @param color Color of the pixel.
 */
void         ssd1306_drawPixel(screen_t* dev, int x, int y, int color);

/**
 * @brief Draws a horizontal line on the screen in the specified color. No bounds checking (used by other functions that do the bounds checking first)
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the line, counted from the left side of the screen.
 *
 * @param y Vertical coordinate of the line.
 *
 * @param w TODO
 *
 * @param color Color of the pixel.
 */
void         ssd1306_drawFastHLine(screen_t* dev, int x, int y, int w, int color);

/**
 * @brief Draws a vertical line on the screen in the specified color. No bounds checking (used by other functions that do the bounds checking first)
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Horizontal coordinate of the line.
 *
 * @param y Starting vertical coordinate of the line, counted down from the top of the screen.
 *
 * @param h TODO
 *
 * @param color Color of the pixel.
 */
void         ssd1306_drawFastVLine(screen_t* dev, int x, int y, int h, int color);

// TODO scrolling stuff

/**
 * @brief Starts scrolling the entire image on the screen horizontally, vertically, or both.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param start TODO
 *
 * @param stop TODO
 *
 * @param action TODO
 */
void         ssd1306_scroll(screen_t* dev, char start, char stop, char action);

/**
 * @brief TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param dim TODO
 */
 
void         ssd1306_dimDisplay(screen_t* dev, char dim);

/**
 * @brief TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
unsigned char* ssd1306_getImageBuffer(screen_t* dev);

/**
 * @brief TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x TODO
 *
 * @param y TODO
 */
 int          ssd1306_getPixel(screen_t* dev, int x, int y);

/**
 * @brief Low-level driver for sending a byte to the ePaper screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param c TODO
 *
 * @param dc TODO
 */
 void         ssd1306_write(screen_t* dev, unsigned int c, char dc);

/**
 * @brief Transfers bytes to the screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param c TODO
 *
 * @param n TODO
 *
 * @param dc TODO
 */
 void         ssd1306_writeBytes(screen_t* dev, unsigned char *c, int n, char dc);

/**
 * @brief Low-level driver for sending a byte to the ePaper screen.
 *
 * @param mask_cs TODO
 *
 * @param mask_sdi
 *
 * @param mask_clk
 *
 * @param c TODO
 *
 * @param dc TODO
 */
void         ssd1306_spiWrite(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, char c, char dc);

/**
 * @brief Transfers bytes to the screen.
 *
 * @param mask_cs TODO
 *
 * @param mask_sdi TODO
 *
 * @param mask_clk TODO
 *
 * @param mask_dc TODO
 *
 * @param data TODO
 *
 * @param n TODO
 */
void         ssd1306_spiWriteBytes(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, const unsigned char* data, char dc, int n);
  
#if defined(__cplusplus)
}                                             // End compile for C block
#endif
/* __cplusplus */


#endif // _SSD1306_H_
