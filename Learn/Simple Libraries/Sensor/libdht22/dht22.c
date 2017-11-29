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

#include <propeller.h>
#include "dht22.h"

static unsigned int dht_timeout[32];

int read_dht22(int dht_pin, char temp_units, int *temp_var, int *humidity_var, char ignore_timeout) {
  
  // Set up a pin mask
  int dhtpm = (1 << dht_pin);
  
  // Has it been less than 0.5 seconds since this function was last called?
  if (CNT - dht_timeout[dht_pin] > CLKFREQ/2 && dht_timeout[dht_pin] != 0 && ignore_timeout == 0) {
    // If so, wait until 0.5 s has elapsed.
    waitcnt(dht_timeout[dht_pin]);
  }
  
  // Set up variables to hold incoming data
  unsigned int dhtp[42];
  int dhtc = 0, dhtk = 0, dhts = 0, dhto = 0, dhth = 0, dhtt = 0, dhte = 0;
  
  // Pull the data pin low
  OUTA &= ~dhtpm;
  DIRA |= dhtpm;
  
  // Wait 18 ms
  waitcnt(CLKFREQ/55 + CNT);  

  // Set the data pin to an input
  DIRA &= ~dhtpm;
  
  // Set a 2 second timer for the pulse measurements to prevent lockup
  dhto = CNT + CLKFREQ * 2;

  // After each full pulse, store the system clock in an 
  // array until 42 measurements are recorded (1 start pulse +
  // 5 bytes of data)
  do {
      waitpne(dhtpm, dhtpm);
      waitpeq(dhtpm, dhtpm);
      dhtp[dhtc] = CNT;
      dhtc++;
  } while (dhtc < 42 && dhto > CNT);

  // Measure the length of each pulse to determine if it's a 0 or 1.
  // Bytes 1 & 2 are % relative humidity
  for (dhtc = 2; dhtc < 18; dhtc++) {
    dhth <<= 1;
    dhth |= (dhtp[dhtc] - dhtp[dhtc-1] > CLKFREQ/9800);
  }
 
  // Bytes 3 & 4 are temperature (Celsius)
  for (dhtc = 18; dhtc < 34; dhtc++) {
    dhtt <<= 1;
    dhtt |= (dhtp[dhtc] - dhtp[dhtc-1] > CLKFREQ/9800);
  }

  // Byte 5 is a additive checksum
  for (dhtc = 34; dhtc < 42; dhtc++) {
    dhtk <<= 1;
    dhtk |= (dhtp[dhtc] - dhtp[dhtc-1] > CLKFREQ/9800);
  }
  
  // The MSB of the temp is a sign bit, but it's not 2's-compliment...
  // So determine it, then remove it
  dhts = dhtt & 32768;
  dhtt &= 32767;
  
  // If the temp is negative, multiply it by -1
  dhtt *= (dhts ? -1 : 1);
  
  // Calculate the checksum
  dhte = (((dhth >> 8) & 255) + (dhth & 255) + ((dhtt >> 8) & 255) + (dhtt & 255)) & 255;
  
  // Save the temp and humidity into the passed in variables
  // Convert to Farenheiht if requested
  *humidity_var = dhth;
  
  if (temp_units == KELVIN)
    dhtt += 2732;
  else if (temp_units == FAHRENHEIT)
    dhtt = dhtt * 9 / 5 + 320;
  *temp_var = dhtt;
  
  // Save the system clock + 0.5 seconds so that the sensor 
  // is not queried again for at least .5 seconds
  dht_timeout[dht_pin] = CNT + CLKFREQ/2;
  
  // Return true if the checksum matches
  return dhte == dhtk;
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