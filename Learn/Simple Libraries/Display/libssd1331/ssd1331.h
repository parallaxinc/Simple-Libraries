/*
 * @file libssd1331.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
 * terms of use (MIT License).
 *
 * @brief Waveshare ePaper driver source, see wsc.h for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */



#include "simplegfx.h"
#include "simpletools.h"


#ifndef WHITE
  #define WHITE                     0xFFFF
#endif

#ifndef PINK
  #define PINK                      0xFD59
#endif

#ifndef MAGENTA
  #define MAGENTA                   0xC9D4
#endif

#ifndef RED
  #define RED                       0xC082
#endif

#ifndef DARKRED
  #define DARKRED                   0xA000
#endif

#ifndef REDORANGE
  #define REDORANGE                 0xD261
#endif

#ifndef LIGHTORANGE
  #define LIGHTORANGE               0xDDB2
#endif

#ifndef ORANGE
  #define ORANGE                    0xFC00
#endif

#ifndef YELLOWORANGE
  #define YELLOWORANGE              0xFCE0
#endif

#ifndef GOLD
  #define GOLD                      0xF704
#endif

#ifndef YELLOW
  #define YELLOW                    0xF744
#endif

#ifndef LEMON
  #define LEMON                     0xD6CF
#endif

#ifndef YELLOWGREEN
  #define YELLOWGREEN               0x5600
#endif

#ifndef GREEN
  #define GREEN                     0x1C62
#endif

#ifndef DARKGREEN
  #define DARKGREEN                 0x02C0
#endif

#ifndef GREENBLUE
  #define GREENBLUE                 0x0C75
#endif

#ifndef CYAN
  #define CYAN                      0x5E97
#endif

#ifndef LIGHTBLUE
  #define LIGHTBLUE                 0x857B
#endif

#ifndef SKYBLUE
  #define SKYBLUE                   0x0E3E
#endif

#ifndef BLUE
  #define BLUE                      0x2B16
#endif

#ifndef NAVYBLUE
  #define NAVYBLUE                  0x0009
#endif

#ifndef VIOLET
  #define VIOLET                    0x7817
#endif

#ifndef PURPLE
  #define PURPLE                    0xA017
#endif

#ifndef RASPBERRY
  #define RASPBERRY                 0x902A
#endif

#ifndef TAN
  #define TAN                       0xCC2A
#endif

#ifndef LIGHTBROWN
  #define LIGHTBROWN                0xBB44
#endif

#ifndef BRONZE
  #define BRONZE                    0xA440
#endif

#ifndef BROWN
  #define BROWN                     0x9201
#endif

#ifndef DARKBROWN
  #define DARKBROWN                 0x51E7
#endif

#ifndef LIGHTGRAY
  #define LIGHTGRAY                 0xBDD7
#endif

#ifndef GRAY
  #define GRAY                      0x8410
#endif

#ifndef DARKGRAY
  #define DARKGRAY                  0x3186
#endif

#ifndef BLACK
  #define BLACK                     0x0000
#endif




// SSD1331 Commands
#ifndef SSD1331_CMD_DRAWLINE
  #define SSD1331_CMD_DRAWLINE        0x21
#endif

#ifndef SSD1331_CMD_DRAWRECT
  #define SSD1331_CMD_DRAWRECT        0x22
#endif

#ifndef SSD1331_CMD_COPY
  #define SSD1331_CMD_COPY            0x23
#endif

#ifndef SSD1331_CMD_CLEAR
  #define SSD1331_CMD_CLEAR           0x25
#endif

#ifndef SSD1331_CMD_FILL
  #define SSD1331_CMD_FILL            0x26
#endif

#ifndef SSD1331_CMD_SCROLLSETUP
  #define SSD1331_CMD_SCROLLSETUP     0x27
#endif

#ifndef SSD1331_CMD_SCROLLSTOP
  #define SSD1331_CMD_SCROLLSTOP      0x2E
#endif

#ifndef SSD1331_CMD_SCROLLSTART
  #define SSD1331_CMD_SCROLLSTART     0x2F
#endif

#ifndef SSD1331_CMD_SETCOLUMN
  #define SSD1331_CMD_SETCOLUMN       0x15
#endif

#ifndef SSD1331_CMD_SETROW
  #define SSD1331_CMD_SETROW          0x75
#endif

#ifndef SSD1331_CMD_CONTRASTA
  #define SSD1331_CMD_CONTRASTA       0x81
#endif

#ifndef SSD1331_CMD_CONTRASTB
  #define SSD1331_CMD_CONTRASTB       0x82
#endif

#ifndef SSD1331_CMD_CONTRASTC
  #define SSD1331_CMD_CONTRASTC       0x83
#endif

#ifndef SSD1331_CMD_MASTERCURRENT
  #define SSD1331_CMD_MASTERCURRENT   0x87
#endif

#ifndef SSD1331_CMD_SETREMAP
  #define SSD1331_CMD_SETREMAP        0xA0
#endif

#ifndef SSD1331_CMD_STARTLINE
  #define SSD1331_CMD_STARTLINE       0xA1
#endif

#ifndef SSD1331_CMD_DISPLAYOFFSET
  #define SSD1331_CMD_DISPLAYOFFSET   0xA2
#endif

#ifndef SSD1331_CMD_NORMALDISPLAY
  #define SSD1331_CMD_NORMALDISPLAY   0xA4
#endif

#ifndef SSD1331_CMD_DISPLAYALLON
  #define SSD1331_CMD_DISPLAYALLON    0xA5
#endif

#ifndef SSD1331_CMD_DISPLAYALLOFF
  #define SSD1331_CMD_DISPLAYALLOFF   0xA6
#endif

#ifndef SSD1331_CMD_INVERTDISPLAY
  #define SSD1331_CMD_INVERTDISPLAY   0xA7
#endif

#ifndef SSD1331_CMD_SETMULTIPLEX
  #define SSD1331_CMD_SETMULTIPLEX    0xA8
#endif

#ifndef SSD1331_CMD_SETMASTER
  #define SSD1331_CMD_SETMASTER       0xAD
#endif

#ifndef SSD1331_CMD_DISPLAYOFF
  #define SSD1331_CMD_DISPLAYOFF      0xAE
#endif

#ifndef SSD1331_CMD_DISPLAYON
  #define SSD1331_CMD_DISPLAYON       0xAF
#endif

#ifndef SSD1331_CMD_POWERMODE
  #define SSD1331_CMD_POWERMODE       0xB0
#endif

#ifndef SSD1331_CMD_PRECHARGE
  #define SSD1331_CMD_PRECHARGE       0xB1
#endif

#ifndef SSD1331_CMD_CLOCKDIV
  #define SSD1331_CMD_CLOCKDIV        0xB3
#endif

#ifndef SSD1331_CMD_PRECHARGEA
  #define SSD1331_CMD_PRECHARGEA      0x8A
#endif

#ifndef SSD1331_CMD_PRECHARGEB
  #define SSD1331_CMD_PRECHARGEB      0x8B
#endif

#ifndef SSD1331_CMD_PRECHARGEC
  #define SSD1331_CMD_PRECHARGEC      0x8C
#endif

#ifndef SSD1331_CMD_PRECHARGELEVEL
  #define SSD1331_CMD_PRECHARGELEVEL  0xBB
#endif

#ifndef SSD1331_CMD_VCOMH
  #define SSD1331_CMD_VCOMH           0xBE
#endif









screen_t* ssd1331_init(char sdi, char sclk, char cs, char rs, char rst, int _width, int _height);

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
void ssd1331_drawPixel(screen_t* dev, int x, int y, int color);

/**
 * @brief Draws a line on the screen in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Starting horizontal coordinate of the line, counted from the left side of the screen.
 *
 * @param y0 Starting vertical coordinate of the line, counted down from the top of the screen.
 *
 * @param x1 Ending horizontal coordinate of the line.
 *
 * @param y1 Ending vertical coordinate of the line.
 *
 * @param color Color of the pixel, in r5g6b5 format.
 */
void ssd1331_drawLine(screen_t* dev, int x0, int y0, int x1, int y1, int color);

/**
 * @brief Draws a vertical line on the screen in the specified color. No bounds checking (used by other functions that do the bounds checking first)
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Horizontal coordinate of the line.
 *
 * @param y vertical coordinate of the line, counted down from the top of the screen.
 *
 * @param w TODO
 *
 * @param color Color of the pixel.
 */
void ssd1331_drawFastVLine(screen_t* dev, int x, int y, int w, int color);

/**
 * @brief Draws a horizontal line on the screen in the specified color. No bounds checking (used by other functions that do the bounds checking first)
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x horizontal coordinate of the line, counted from the left side of the screen.
 *
 * @param y Vertical coordinate of the line.
 *
 * @param h TODO
 *
 * @param color Color of the pixel.
 */
void ssd1331_drawFastHLine(screen_t* dev, int x, int y, int h, int color);

/**
 * @brief Draws a filled rectangle on the screen in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Starting horizontal coordinate of the rectangle, counted from the left side of the screen.
 *
 * @param y0 Starting vertical coordinate of the rectangle, counted down from the top of the screen.
 *
 * @param x1 TODO
 *
 * @param y1 TODO
 *
 * @param color Color of the rectangle, in r5g6b5 format.
 */
void ssd1331_fillRect(screen_t* dev, int x0, int y0, int x1, int y1, int color);

/**
 * @brief TODO
 *
 * @param dev TODO
 */
void ssd1331_clearDisplay(screen_t* dev);

/**
 * @brief TODO
 *
 * @param dev TODO
 */
void ssd1331_resetDisplay(screen_t* dev);

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
 * @param c TODO
 *
 * @param dc TODO
 */
void ssd1331_writeByte(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, char c, char dc);

/**
 * @brief Returns the status of the SPI communication lockout so multiple cogs don't try to write to it at the same time
 */
char ssd1331_writeLock();

/**
 * @brief Sets the SPI communication lockout
 *
 * @param devId TODO
 */
void ssd1331_writeLockSet(char devId);

/**
 * @brief Clears the SPI communication lockout
 *
 * @param devId TODO
 */
void ssd1331_writeLockClear(char devId);

/**
 * @brief Creates a copy a rectangular area of the screen at another position on the screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Starting horizontal coordinate of the box to be copied, counted from the left side of the screen.
 *
 * @param y0 Starting vertical coordinate of the box to be copied, counted down from the top of the screen.
 *
 * @param w Width of the box to be copied.
 *
 * @param h height of the box to be copied.
 *
 * @param x2 Horizontal coordinate where the copied box is to be pasted.
 *
 * @param y2 Vertical coordinate where the copied box is to be pasted.
 */
void ssd1331_copy(screen_t* dev, int x0, int y0, int w, int h, int x2, int y2);

/**
 * @brief Starts scrolling the entire image on the screen horizontally, vertically, or both.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @note the screen's horizontal displacement will persist after scrolling has stopped, but its vertical displacement will not.
 *
 * @param h Horizontal scrolling in rows per interval.
 * (0) turns off horizontal scrolling, negative integers scroll
 * to the left and positive integers scroll to the right.
 *
 * @param v Vertical scrolling columns per interval.
 * (0) turns off vertical scrolling, negative integers scroll
 * down and positive integers scroll up.
 */
void ssd1331_scrollStart(screen_t* dev, char h, char v);

/**
 * @brief Inverts the screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void ssd1331_invertDisplay(screen_t *dev, char i);

/**
 * @brief Sleeps or Wakes the display.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void ssd1331_sleepWakeDisplay(screen_t *dev, char i);