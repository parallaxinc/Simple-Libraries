/*
 * @file il3820.h
 *
 * @author Matthew Matz & Roy Eltham
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
 * terms of use (MIT License).
 *
 * @brief This is a driver that allows the Propeller Multicore Microcontroller to
 * draw text, shapes, and bitmap files on the Waveshare ePaper display.
 *
 * @detail TODO This high-speed driver allows the Propeller Multicore Microcontroller to
 * draw pixels, lines, circles, recatngles, rounded rectagles, triangles, formatted text
 * in multiple fonts, bitmap images stored on an SD card on a WaveShare ePaper screen.
 * At Parallax, we would like to thank Adafruit Industries as parts of this library
 * were dervied from the Adafruit GFX library for Arduino.  Please submit bug reports,
 * suggestions, and improvements to this code to editor@parallax.com.
 */

#ifndef IL3820_H                              // Prevents duplicate
#define IL3820_H                              // declarations

#if defined(__cplusplus)                      // If compiling for C++
extern "C" {                                  // Compile for C
#endif


#include "simpletools.h"
#include "simplegfx.h"


// il3820 ePaper colors
#ifndef BLACK
  #define BLACK           0
#endif

#ifndef WHITE
  #define WHITE           1
#endif

#ifndef INVERSE
  #define INVERSE         2
#endif


// il3820 commands
#ifndef IL3820_DRIVER_OUTPUT
  #define IL3820_DRIVER_OUTPUT                               0x01
#endif

#ifndef IL3820_BOOSTER_SOFT_START
  #define IL3820_BOOSTER_SOFT_START                          0x0C
#endif

#ifndef IL3820_GATE_SCAN_START
  #define IL3820_GATE_SCAN_START                             0x0F
#endif

#ifndef IL3820_DEEP_SLEEP_MODE
  #define IL3820_DEEP_SLEEP_MODE                             0x10
#endif

#ifndef IL3820_DATA_ENTRY_MODE
  #define IL3820_DATA_ENTRY_MODE                             0x11
#endif

#ifndef IL3820_SW_RESET
  #define IL3820_SW_RESET                                    0x12
#endif

#ifndef IL3820_TEMPERATURE_SENSOR
  #define IL3820_TEMPERATURE_SENSOR                          0x1A
#endif

#ifndef IL3820_MASTER_ACTIVATION
  #define IL3820_MASTER_ACTIVATION                           0x20
#endif

#ifndef IL3820_DISPLAY_UPDATE_1
  #define IL3820_DISPLAY_UPDATE_1                            0x21
#endif

#ifndef IL3820_DISPLAY_UPDATE_2
  #define IL3820_DISPLAY_UPDATE_2                            0x22
#endif

#ifndef IL3820_WRITE_RAM
  #define IL3820_WRITE_RAM                                   0x24
#endif

#ifndef IL3820_WRITE_VCOM_REGISTER
  #define IL3820_WRITE_VCOM_REGISTER                         0x2C
#endif

#ifndef IL3820_WRITE_LUT_REGISTER
  #define IL3820_WRITE_LUT_REGISTER                          0x32
#endif

#ifndef IL3820_SET_DUMMY_LINE_PERIOD
  #define IL3820_SET_DUMMY_LINE_PERIOD                       0x3A
#endif

#ifndef IL3820_SET_GATE_TIME
  #define IL3820_SET_GATE_TIME                               0x3B
#endif

#ifndef IL3820_BORDER_WAVEFORM_CONTROL
  #define IL3820_BORDER_WAVEFORM_CONTROL                     0x3C
#endif

#ifndef IL3820_SET_RAM_X_ADDRESS_POSITION
  #define IL3820_SET_RAM_X_ADDRESS_POSITION                  0x44
#endif

#ifndef IL3820_SET_RAM_Y_ADDRESS_POSITION
  #define IL3820_SET_RAM_Y_ADDRESS_POSITION                  0x45
#endif

#ifndef IL3820_SET_RAM_X_ADDRESS_COUNTER
  #define IL3820_SET_RAM_X_ADDRESS_COUNTER                   0x4E
#endif

#ifndef IL3820_SET_RAM_Y_ADDRESS_COUNTER
  #define IL3820_SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#endif

#ifndef IL3820_TERMINATE_FRAME_READ_WRITE
  #define IL3820_TERMINATE_FRAME_READ_WRITE                  0xFF
#endif



/**
 * @brief Initializes the ePaper screen by setting up it's SPI and control pins.
 *
 * @param sid which pin is connected to the Serial Data In pin, marked "DIN".
 *
 * @param sclk which pin is connected to the Serial Clock pin, marked "CLK".
 *
 * @param cs which pin is connected to the Chip Select pin, marked "CS".
 *
 * @param rs which pin is connected to the Read Status pin, marked "D/C".
 *
 * @param rst which pin is connected to the Reset pin, marked "RST".
 *
 * @param busy which pin is connected to the Busy pin, marked "BUSY".
 *
 * @param _width TODO
 *
 * @param _height TODO
 */
screen_t *il3820_init(char sid, char sclk, char cs, char rs, char rst, char busy, int _width, int _height);


/**
 * @brief Turn the display off without changing it's contents (make it sleep).
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void il3820_sleepDisplay(screen_t *dev);

/**
 * @brief Turn the display on from a sleep mode.
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void il3820_wakeDisplay(screen_t *dev);



/**
 * @brief Low-level driver for sending a byte to the ePaper screen.
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
void il3820_spiWrite(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, char c, char dc);

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
 * @param data Pointer to buffer of bytes to send
 *
 * @param numBytes The number of bytes in the buffer to send.
 */
void il3820_spiWriteBytes(int mask_cs, int mask_sdi, int mask_clk, const unsigned char* data, int numBytes);


/**
 * @brief Returns the status of the SPI communication lockout so multiple cogs don't try to write to it at the same time
 */
char il3820_writeLock();

/**
 * @brief Sets the SPI communication lockout
 *
 * @param devId TODO
 */
void il3820_writeLockSet(char devId);

/**
 * @brief Clears the SPI communication lockout
 *
 * @param devId TODO
 */
void il3820_writeLockClear(char devId);


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
void il3820_drawPixel(screen_t *dev, int x, int y, int color);

/**
 * @brief Draws a horizontal line on the screen in the specified color. No bounds checking (used by other functions that do the bounds checking first)
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param x0 Starting horizontal coordinate of the line, counted from the left side of the screen.
 *
 * @param x1 Ending horizontal coordinate of the line.
 *
 * @param y Vertical coordinate of the line.
 *
 * @param color Color of the pixel.
 */
void il3820_drawFastHLine(screen_t *dev, int x0, int x1, int y, int color);

/**
 * @brief Draws a vertical line on the screen in the specified color. No bounds checking (used by other functions that do the bounds checking first)
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 *
 * @param y0 Starting vertical coordinate of the line, counted down from the top of the screen.
 *
 * @param y1 Ending vertical coordinate of the line.
 *
 * @param x Horizontal coordinate of the line.
 *
 * @param color Color of the pixel.
 */
void il3820_drawFastVLine(screen_t *dev, int y0, int y1, int x, int color);


/**
 * @brief TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void il3820_clearDisplay(screen_t *dev);


/**
 * @brief: update the display with whatever is in the frame memory.
 *          You need to have updated the frame memory with _image first
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void il3820_updateDisplay(screen_t *dev);

/**
 * @brief TODO
 *
 * @param dev Pointer to the display's device structure returned by the initialization function.
 */
void il3820_resetDisplay(screen_t *dev);



#if defined(__cplusplus)
}                                             // End compile for C block
#endif
/* __cplusplus */

#endif                                        // End prevent duplicate forward
/* IL3820_H */                                   // declarations block



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
