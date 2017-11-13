/**
 * @file dht22.h
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2017. All Rights MIT Licensed.
 *
 * @brief This Propeller C library was created for the DHT22 temperature 
 * and humidity sensor module.
 */


#ifndef  __DHT22_SENSOR_H__                                  // Prevents duplicate
#define  __DHT22_SENSOR_H__                                  // declarations

#if defined(__cplusplus)                                     // If compiling for C++
extern "C" {                                                 // Compile for C
#endif


// Units of temperature
#ifndef  CELSIUS 
#define  CELSIUS            0
#endif

#ifndef  FAHRENHEIT 
#define  FAHRENHEIT         1
#endif

#ifndef  KELVIN 
#define  KELVIN             2
#endif


/**
 * @brief Retrieves the temperature and humidity reading from the sensor module.
 *
 * @details This function retrieves the temperature and humidity reading from the 
 * sensor module.  
 *
 * @note The sensor can be read every 500ms.  If this function is called
 * before 500ms from the previous call has elapsed, the function waits if the
 * ignore_timeout parameter is false (0).
 * 
 * @param dht_pin defines which pin the sensor is attached to.  Requires a 10 kOhm
 * pullup resistor to 3.3V when connecting to the Propeller MCU.
 *
 * @param temp_units allows the temperature unit to be specified in (0) Celsius,
 * (1) Fahrenheit, or (2) Kelvin.
 *
 * @param *temp_var variable to store the temperature in degree-tenths into.
 *
 * @param *humidity_var variable to store the relative humidity in tenths of a percent into.
 *
 * @param ignore_timeout when true (1), the function ignores the protective timeout that
 * prevents the sensor from being read before it is ready.  This parameter should be
 * set to false (0) unless the sensor is being read at intervals > 10 seconds
 * apart, in which case it is recommended that this is set to true (1).
 *
 * @returns 1 if a valid checksum was recieved, 0 if the checksum is invalid.
 */

int read_dht22(int dht_pin, char temp_units, int *temp_var, int *humidity_var, char ignore_timeout);


#if defined(__cplusplus)                     
}                                             // End compile for C block
#endif
/* __cplusplus */

#endif                                        // End prevent duplicate forward
/* __DHT22_SENSOR_H__ */                      // declarations block 


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