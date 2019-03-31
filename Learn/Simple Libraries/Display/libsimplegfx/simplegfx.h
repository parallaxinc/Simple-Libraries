/*
 * @file simplegfx.h
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

#ifndef _SCREEN_GFX_
#define _SCREEN_GFX_

#if defined(__cplusplus)      // If compiling for C++
extern "C" {                  // Compile for C
#endif


#include "simpletools.h"


// Font size and face
#ifndef SMALL
  #define SMALL   1
#endif

#ifndef MEDIUM
  #define MEDIUM  2
#endif

#ifndef LARGE
  #define LARGE   3
#endif


#ifndef FONT_SANS
  #define FONT_SANS       0
#endif

#ifndef FONT_SERIF
  #define FONT_SERIF      1
#endif

#ifndef FONT_SCRIPT
  #define FONT_SCRIPT     2
#endif

#ifndef FONT_BUBBLE
  #define FONT_BUBBLE     3
#endif


#ifndef INTF_SPI_NO_BUFFER
  #define INTF_SPI_NO_BUFFER       0b00
#endif

#ifndef INTF_SPI_WITH_BUFFER
  #define INTF_SPI_WITH_BUFFER     0b10
#endif

#ifndef INTF_I2C_NO_BUFFER
  #define INTF_I2C_NO_BUFFER       0b01
#endif

#ifndef INTF_I2C_WITH_BUFFER
  #define INTF_I2C_WITH_BUFFER     0b11
#endif


#ifndef gfx_swap
  #define gfx_swap(a, b)  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))    // No-temp-var swap operation
#endif

#ifndef absv
  #define absv(x) ((x)<0 ? -(x) : (x))
#endif


// Radix Constants
#ifndef HEX
  #define HEX    -16
#endif

#ifndef OCT
  #define OCT    -8
#endif

#ifndef BIN
  #define BIN    -2
#endif

#ifndef DEC
  #define DEC    -10
#endif



typedef struct screen_st {
  /** Width of the device's display in pixels (fixed value) */
  int                           width;

  /** Height of the device's display in pixels (fixed value) */
  int                           height;

  /** Current rotation of the dispaly.  Sets top-left origin to different corners of the display */
  int                           rotation;

  /** Current horizontal position of the cursor for drawing characters */
  int                           cursor_x;

  /** Current vertical position of the cursor for drawing characters */
  int                           cursor_y;

  /** EEPROM locations of medium and large font definitions/bitmaps */
  int                           font[5];

  /** String representing color-depth of display in bits/channel */
  char                          color_depth;

  /** Current text size */
  char                          text_size;

  /** Boolean to wrap or not wrap text at the end of the screen */
  char                          text_wrap;

  /** Color to draw text characters in */
  int                           text_color;

  /** Color of the background of text characters.  Set to the same color as the text for transparent */
  int                           bg_color;

  /** Current display modes: bit 0=normal/inverted, bit 1=sleep/wake, bits 8:15=vert scroll, bits 16:23=horiz scroll */
  int                           display_mode;

    
  /** i2c bus pointer for accessing fonts in EEPROM */
  i2c*                          eepromBus;

  
  /** i2c bus pointer for accessing device */
  i2c*                          deviceBus;

  /** interface type (bit 1) (1-i2c/0-SPI) and buffer (bit 0) (0-yes/1-no) */
  char                          deviceInterface;


  /** Device address (I2C) OR Chip Select pin (SPI) */
  unsigned char                 dev_id;

  /** Device serial data out OR busy pin (SPI) */
  char                          status_pin;

  /** Device data pin (SPI) */
  char                          sdi_pin;

  /** Device reset pin (-1 if not used or available) */
  char                          rst_pin;

  /** Device clock pin (SPI) */
  char                          clk_pin;

  /** Device data/command pin (SPI 5-wire) */
  char                          dc_pin;


  /** Size of the image buffer, usually (length * width * color depth in bytes) */
  int                           image_size;

  /** Pointer to the image buffer */
  char*                         image_ptr;


  /** Array for holding small (5x7) custom characters */
  char*                         customCharSmall;

  /** Array for holding medium (11x15) custom characters */
  char*                         customCharMed;

  /** Array for holding large (17x23) custom characters */
  char*                         customCharLarge;

    
  /** Get state of lock to prevent multiple functions from accessing device at once */
  char (*deviceWriteLock)       (void);

  /** Set the device write lock */
  void (*deviceWriteLockSet)    (struct screen_st*);

  /** Clear the device write lock */
  void (*deviceWriteLockClear)  (struct screen_st*);


  /** Device native pixel drawing function */
  void (*deviceDrawPixel)       (struct screen_st*, int  x, int y, int color);

  /** Device native pixel retrieving function */
  int  (*deviceGetPixel)        (struct screen_st*, int  x, int y);

  /** Use if device has accelerated line drawing */
  void (*deviceDrawLine)        (struct screen_st*, int  x, int y, int w, int h, int color);

  /** Device native horizontal line drawing function */
  void (*deviceDrawFastHLine)   (struct screen_st*, int  x, int y, int w, int color);

  /** Device native vertical line drawing function */
  void (*deviceDrawFastVLine)   (struct screen_st*, int  x, int y, int w, int color);

  /** Use if device has accelerated filled rectagle drawing */
  void (*deviceFillRect)        (struct screen_st*, int  x, int y, int w, int h, int color);

  /** Use if device has a native copy function */
  void (*deviceCopyRect)        (struct screen_st*, int  x, int y, int w, int h, int x1, int y1);


  /** Device native function for clearing the display and setting it all to the default blank color */
  void (*deviceClearDisplay)    (struct screen_st*);

  /** Use if display needs to be updated (otherwise 0) */
  void (*deviceUpdateDisplay)   (struct screen_st*);

  /** Device native reset function (Use clear display if not available) */
  void (*deviceResetDisplay)    (struct screen_st*);

  /** Device native color invert function */
  void (*deviceInvertDisplay)   (struct screen_st*, char i);

  /** Device native sleep/wake display, if available */
  void (*deviceSleepWakeDisplay)(struct screen_st*, char i);

  /** Device native solling functions if available */
  void (*deviceScrollDisplay)   (struct screen_st*, int  h, int v);

} screen_t;

typedef screen_t screen;






/**
 * @brief Clears (sets to the native background color of the screen, usually black) the entire screen
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void clearDisplay(screen_t *dev);

/**
 * @brief Updates the display by writing the image buffer to it.  Not necessary for screens that have
 * their own image buffers
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void updateDisplay(screen_t *dev);

/**
 * @brief Resets the display.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void resetDisplay(screen_t *dev);

/**
 * @brief Draws a single pixel in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Horizontal coordinate of the pixel, counted from the left side of the screen.
 *
 * @param y Vertical coordinate of the pixel, counted down from the top of the screen.
 *
 * @param color Color of the pixel, in the format native to the display.
 */
void drawPixel(screen_t *dev, int x, int y, int color);

/**
 * @brief Draws a horizontal line in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the line, counted from the left side of the screen.
 *
 * @param y Starting vertical coordinate of the line, counted down from the top of the screen.
 *
 * @param w Length of the line.
 *
 * @param color Color of the line, in the format native to the display.
 */
void drawFastHLine(screen_t *dev, int x, int y, int w, int color);

/**
 * @brief Draws a vertical line in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the line, counted from the left side of the screen.
 *
 * @param y Starting vertical coordinate of the line, counted down from the top of the screen.
 *
 * @param h Length of the line.
 *
 * @param color Color of the line, in the format native to the display.
 */
void drawFastVLine(screen_t *dev, int x, int y, int h, int color);

/**
 * @brief Draws a line in the specified color.
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
 * @param color Color of the shape, in the format native to the display.
 */
void drawLine(screen_t *dev, int x0, int y0, int x1, int y1, int color);

/**
 * @brief Draws a circle in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Horizontal coordinate of the center of the circle, counted from the left side of the screen.
 *
 * @param y0 Vertical coordinate of the center of the circle, counted down from the top of the screen.
 *
 * @param r Radius of the circle.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void drawCircle(screen_t *dev, int x0, int y0, int r, int color);

/**
 * @brief Helper function used to help draw circles and rectangles with rounded corners
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Horizontal coordinate of the center of the arc, counted from the left side of the screen.
 *
 * @param y0 Vertical coordinate of the center of the arc, counted down from the top of the screen.
 *
 * @param r Radius of the arc.

 * @param cornername Which corner (arc) to draw
 *
 * @param color Color of the shape, in the format native to the display.
 */
void drawCircleHelper(screen_t *dev, int x0, int y0, int r, char cornername, int color);

/**
 * @brief Draws a filled circle in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Horizontal coordinate of the center of the circle, counted from the left side of the screen.
 *
 * @param y0 Vertical coordinate of the center of the circle, counted down from the top of the screen.
 *
 * @param r Radius of the circle.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void fillCircle(screen_t *dev, int x0, int y0, int r, int color);

/**
 * @brief Helper function used to draw filled circles and rectangles with rounded corners
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Horizontal coordinate of the center of the arc, counted from the left side of the screen.
 *
 * @param y0 Vertical coordinate of the center of the arc, counted down from the top of the screen.
 *
 * @param r Radius of the arc.
 *
 * @param cornername Which corner (arc) to draw
 *
 * @param delta Offest from the center line (space between quarter circles) used for drawing 
 * rounded rectagles
 *
 * @param color Color of the shape, in the format native to the display.
 */
void fillCircleHelper(screen_t *dev, int x0, int y0, int r, char cornername, int delta, int color);

/**
 * @brief Draws a rectangle in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the rectangle, counted from the left side of the screen.
 *
 * @param y Starting vertical coordinate of the rectangle, counted down from the top of the screen.
 *
 * @param w Width of the rectangle.
 *
 * @param h Height of the rectangle.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void drawRect(screen_t *dev, int x, int y, int w, int h, int color);

/**
 * @brief Draws a filled rectangle in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the rectangle, counted from the left side of the screen.
 *
 * @param y Starting vertical coordinate of the rectangle, counted down from the top of the screen.
 *
 * @param w Width of the rectangle.
 *
 * @param h Height of the rectangle.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void fillRect(screen_t *dev, int x, int y, int w, int h, int color);

/**
 * @brief Draws a rectangle with rounded corners in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the rectangle, counted from the left side of the screen.
 *
 * @param y Starting vertical coordinate of the rectangle, counted down from the top of the screen.
 *
 * @param w Width of the rectangle.
 *
 * @param h Height of the rectangle.
 *
 * @param r Radius of the rounded corners.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void drawRoundRect(screen_t *dev, int x, int y, int w, int h, int r, int color);

/**
 * @brief Draws a filled rectangle with rounded corners in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Starting horizontal coordinate of the rectangle, counted from the left side of the screen.
 *
 * @param y Starting vertical coordinate of the rectangle, counted down from the top of the screen.
 *
 * @param w Width of the rectangle.
 *
 * @param h Height of the rectangle.
 *
 * @param r Radius of the rounded corners.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void fillRoundRect(screen_t *dev, int x, int y, int w, int h, int r, int color);

/**
 * @brief Draws a triangle with in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Horizontal coordinate of the first vertex (corner) of the triangle, counted from the left side of the screen.
 *
 * @param y0 Vertical coordinate of the first vertex (corner) of the triangle, counted down from the top of the screen.
 *
 * @param x1 Horizontal coordinate of the second vertex of the triangle.
 *
 * @param y1 Vertical coordinate of the first vertex of the triangle.
 *
 * @param x2 Horizontal coordinate of the third vertex of the triangle.
 *
 * @param y2 Vertical coordinate of the third vertex of the triangle.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void drawTriangle(screen_t *dev, int x0, int y0, int x1, int y1, int x2, int y2, int color);

/**
 * @brief Draws a filled triangle with in the specified color.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Horizontal coordinate of the first vertex (corner) of the triangle, counted from the left side of the screen.
 *
 * @param y0 Vertical coordinate of the first vertex (corner) of the triangle, counted down from the top of the screen.
 *
 * @param x1 Horizontal coordinate of the second vertex of the triangle.
 *
 * @param y1 Vertical coordinate of the first vertex of the triangle.
 *
 * @param x2 Horizontal coordinate of the third vertex of the triangle.
 *
 * @param y2 Vertical coordinate of the third vertex of the triangle.
 *
 * @param color Color of the shape, in the format native to the display.
 */
void fillTriangle(screen_t *dev, int x0, int y0, int x1, int y1, int x2, int y2, int color);

/**
 * @brief Copies a rectagle and draws it at another location on the screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Horizontal coordinate of the top-left corner of the rectangle to be copied.
 *
 * @param y Vertical coordinate of the top-left corner of the rectagle to be copied.
 *
 * @param w Width of the rectagle to be copied.
 *
 * @param h Height of the rectagle to be copied.
 *
 * @param x1 Horizontal coordinate of the location to paste the copied rectagle to.
 *
 * @param y1 Vertical coordinate of the location to paste the copied rectagle to.
 */
void drawCopy(screen_t *dev, int x, int y, int w, int h, int x1, int y1);

/**
 * @brief Sets the size of the font to be used. Range is from 1 to 3.
 * Size (1) is 5x7 (6x8 spacing) pixels, size (2) is 11x15 (12x16 spacing)
 * pixels and size (3) is 15x23 (16x24 spacing) pixels.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param s Size of text to draw.  1 = small (5x7) font, 2 = medium (11x15) font, 
 * 3 = large (17x23) font.
 */
void setTextSize(screen_t *dev, char s);

/**
 * @brief Sets the font face to be used. Range is from 0 to 3.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param f Font face to use. Font face (0) is a sans-serif (console) font, face (1) is 
 * serif (typewriter) font, face (2) is a script (handwriting) font and face (3) is a
 * bubble (outline/cartoon) font.
 */
void setTextFont(screen_t *dev, char f);

/**
 * @brief Sets the color of the font and the color of the background
 * (highlighting) to be used. Setting the text color and text
 * background to the same color will make the background color transparent.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param color Color of the font, in the format native to the display.
 */
void setTextColor(screen_t *dev, int color);

/**
 * @brief Sets the color of the font and the color of the background
 * (highlighting) to be used. Setting the text color and text
 * background to the same color will make the background color transparent.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param color Color of the font, in the format native to the display.
 */
void setBgColor(screen_t *dev, int color);

/**
 * @brief Toggles automatic wrapping of text printed to the screen.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param w Wrapping (0) off -OR- (1) on.
 */
void setTextWrap(screen_t *dev, char w);

/**
 * @brief Sets the cursor position based on the size parameter.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x Horizontal position of the cursor, counted from the left side of the screen.
 *
 * @param y Vertical position of the cursor, counted down from the top of the screen.
 *
 * @param size The size of the cursor.  Correlated to font size:
 * (0) moves the cursor in 1 pixel increments, (1) moves the cursor in font
 * size 1 character increments, (2) moves the cursor in font size 2
 * increments and (3) moves the cursor in font size 3 increments
 */
void setCursor(screen_t *dev, int x, int y, char size);

/**
 * @brief Print format "..." args to the screen. The output is limited to 128 bytes.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param fmt Formatted string to be printed to the display.
 */
int  drawPrint(screen_t *dev, const char *fmt, ...);

/**
 * @brief Prints a number to the screen starting at the cursor position. Output is limited to 64 bytes.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param d Number to be printed to the screen.  The number can be either a floating point decimal or an integer.
 *
 * @param r The number base to display the number in (for integers); HEX, BIN, OCT, and DEC are acceptable values.
 * or the number of decimals to display following the decimal point (for floating point numbers).
 * Negative numbers in bases other than DEC will display "Err".
 */
void drawNumber(screen_t *dev, float d, int r);

/**
 * @brief Prints a string of text to the screen starting at the cursor position. Output is limited to 64 bytes.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param *myString Text to display on the screen.
 */
void drawText(screen_t *dev, char *myString);

/**
 * @brief Prints single ASCII-encoded characters to the screen. Characters 32 (space) to 126 (~) are rendered.  All other characters are rendered as a box.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param c ASCII-encoded character to draw.
 */
void drawChar(screen_t *dev, char c);

/**
 * @brief Returns the current horizontal position of the cursor, measured from the left side of the screen in pixels.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 * 
 * @returns the horizontal position of the cursor in pixels.
 */
int  getCursorX(screen_t *dev);

/**
 * @brief Returns the current vertical position of the cursor, measured from the top of the screen in pixels.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 * 
 * @returns the vertical position of the cursor in pixels.
 */
int  getCursorY(screen_t *dev);

/**
 * @brief Sets the screen's orientation. 
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param r Number representing the orientation to set the display to. (0) means pixels are drawn 
 * to the screen is at it's native orientation, (1) means pixels are drawn rotated 
 * 90 degrees clockwise, (2) means pixels are drawn upside-down - 180 degrees rotated, and 
 * (3) means pixels are drawn rotated 270 degrees clockwise.
 */
void setDisplayRotation(screen_t *dev, char r);

/**
 * @brief Returns the screen's orientation. 
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @returns A number representing the screen's orientation.  (0) means pixels are drawn to the screen is at
 * it's native orientation, (1) means pixels are drawn rotated 90 degrees clockwise, (2) means 
 * pixels are drawn upside-down - 180 degrees rotated, and (3) means pixels are drawn 
 * rotated 270 degrees clockwise.
 */
char getDisplayRotation(screen_t *dev);

/**
 * @brief Returns the width of the display in pixels with screen rotation taken into account.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
int  getDisplayWidth(screen_t *dev);

/**
 * @brief Returns the height of the display in pixels with screen rotation taken into account.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
int  getDisplayHeight(screen_t *dev);

/**
 * @brief Internal function used to load the EEPROM addresses of the bitmapped fonts to the device's
 * structure.  This function is called by the init function in the display's library.  It can be 
 * called at any time to point to fonts stored in an EEPROM attached to a different i2c bus.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param eeBus Pointer to the i2c bus where the EEPROM containing the font bitmaps is connected.
 */
void loadFonts(screen_t *dev, i2c *eeBus);

/**
 * @brief Low-level helper function for printing single characters to the screen in the small (5x7) font.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param c ASCII-encoded character to draw.
 */
void drawCharSmall(screen_t *dev, unsigned char c);

/**
 * @brief Low-level helper function for printing single characters to the screen in the medium (11x15) font.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param c ASCII-encoded character to draw.
 */
void drawCharMedium(screen_t *dev, unsigned char c);

/**
 * @brief Low-level helper function for printing single characters to the screen in the large (17x23) font.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param c ASCII-encoded character to draw.
 */
void drawCharLarge(screen_t *dev, unsigned char c);

/**
 * @brief Toggles the invert/normal display modes for the display.  Depending on the display
 * type it may only invert existing drawings, or it may invert both existing and colors 
 * drawn when inversion is set.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param i Set to 0 for normal and 1 for inverted.
 */
void invertDisplay(screen_t *dev, char i);                           

/**
 * @brief Toggle the display's sleep/wake mode.  Not supported by all displays
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param i Set to 0 for awake and 1 for asleep.
 */
void sleepWakeDisplay(struct screen_st*, char i);

/**
 * @brief Set the display's vertical or hrizontal scrolling functions.  
 * Not supported by all displays, and different display types behave differently.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param h Sets the horizontal display velocity, or for displays with only on/off modes,
 * any non-zero value will trigger a horizontal scroll.  Enter zero to stop 
 * horizontal scrolling.
 *
 * @param v Sets the vertical display velocity, or for displays with only on/off modes,
 * any non-zero value will trigger a vertical scroll.  Enter zero to stop 
 * vertical scrolling.
 */
void scrollDisplay(struct screen_st*, int  h, int v);

/**
 * @brief Returns the status of the screen's colors - normal or inverted
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @returns A value of 1 if the screen's colors are inverted, and 0 if the screen's
 * colors are normal (not-inverted).
 */
char isInverted(screen_t *dev);

/**
 * @brief Returns whether the screen is currently in a sleep mode or awake
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @returns A value of 1 if the screenis asleep, and 0 if the screen is awake
 */
char isAsleep(screen_t *dev);

/**
 * @brief Returns a value representing the status or speed of the display's vertical scroll.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @returns A value representing the vertical scrolling velocity (or 1 if the screen
 * only supports a single scrolling speed). 
 */
unsigned char  getScrollVertical(screen_t *dev);

/**
 * @brief Returns a value representing the status or speed of the display's horizontal scroll.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @returns A value representing the horizontal scrolling velocity (or 1 if the screen
 * only supports a single scrolling speed). 
 */
unsigned char  getScrollHorizontal(screen_t *dev);

/**
 * @brief Draw an image (bitmap) at the specified (x,y) position.  
 * Requires an SD card to be mounted.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param imgdir String of the filename of the bitmap stored on the SD card.
 *
 * @param x Horizontal coordinate of the top-left corner of where to draw the image.
 *
 * @param y Vertical coordinate of the top-left corner of where to draw the image.
 */
void drawBitmap(screen_t *dev, char *imgdir, int x, int y);

  
#if defined(__cplusplus)
}     // End compile for C block
#endif
/* __cplusplus */


#endif // _SCREEN_GFX_


/*
 * Because this library is bsed in part on the Adafruit GFX library, this 
 * notice must be included with this distribution:
 * --------------------------------------------------------------------------
 * This is the core graphics library for all our displays, providing a common
 * set of graphics primitives (points, lines, circles, etc.).  It needs to be
 * paired with a hardware-specific library for each display device we carry
 * (to handle the lower-level functions).
 * 
 * Adafruit invests time and resources providing this open source code, please
 * support Adafruit & open-source hardware by purchasing products from Adafruit!
 * 
 * Copyright (c) 2013 Adafruit Industries.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------
 */

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
