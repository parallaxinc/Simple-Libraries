/**
 * @file bme680_begin.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Sensor driver for the Bosch BME680 air quality sensor.
 * This library supports i2c and 4-wire SPI connections, reads
 * temperature, pressure, relative humidity, and VOC levels, and
 * provides limited support for adjusting the sensors settings.
 */

#include "bme680.h"


void bme680_begin(bme680_t *dev) {

  unsigned char tmp[] = {0xb6};
  unsigned char cal[44];
  
  tmp[0] = 0x00;
  
  if (!dev->intf) {
    bme680_write(dev, 0x73, tmp, 1);     // If SPI, change the memory page
  }    

  bme680_write(dev, (dev->intf ? 0xe0 : 0x60), tmp, 1);  // If SPI, read from the correct the memory page
  
  pause(10);
  
  bme680_read(dev, 0x89, cal, 25);
  bme680_read(dev, 0xe1, &cal[25], 16);
  
  tmp[0] = 0x10;
  
  if (!dev->intf) {
    bme680_write(dev, 0x73, tmp, 1);     // If SPI, change the memory page
  }    
  
  bme680_read(dev, 0x02, &cal[41], 1);
  bme680_read(dev, 0x00, &cal[42], 1);
  bme680_read(dev, 0x04, &cal[43], 1);
  
  /* Temperature related coefficients */
  dev->par_t1 = ((unsigned short)((unsigned short) cal[34] << 8) | (unsigned short) cal[33]);
  dev->par_t2 = ((short)((unsigned short) cal[2] << 8) | (unsigned short) cal[1]);
  dev->par_t3 = ((char) cal[3]);
  
  /* Pressure related coefficients */
  dev->par_p1 = ((unsigned short)((unsigned short) cal[6] << 8) | (unsigned short) cal[5]);
  dev->par_p2 = ((short)((unsigned short) cal[8] << 8) | (unsigned short) cal[7]);
  dev->par_p3 = ((char) cal[9]);
  dev->par_p4 = ((short)((unsigned short) cal[12] << 8) | (unsigned short) cal[11]);
  dev->par_p5 = ((short)((unsigned short) cal[14] << 8) | (unsigned short) cal[13]);
  dev->par_p6 = ((char) cal[16]);
  dev->par_p7 = ((char) cal[15]);
  dev->par_p8 = ((short)((unsigned short) cal[20] << 8) | (unsigned short) cal[19]);
  dev->par_p9 = ((short)((unsigned short) cal[22] << 8) | (unsigned short) cal[21]);
  dev->par_p10 = ((unsigned char) cal[23]);
  
  /* Humidity related coefficients */
  dev->par_h1 = ((unsigned short)((unsigned short) cal[27] << 4) | (cal[26] & 0x0F));
  dev->par_h2 = ((unsigned short)((unsigned short) cal[25] << 4) | ((cal[26]) >> 4));
  dev->par_h3 = ((char) cal[28]);
  dev->par_h4 = ((char) cal[29]);
  dev->par_h5 = ((char) cal[30]);
  dev->par_h6 = ((unsigned char) cal[31]);
  dev->par_h7 = ((char) cal[32]);
  
  /* Gas heater related coefficients */
  dev->par_gh1 = ((char) cal[37]);
  dev->par_gh2 = ((short)((unsigned short) cal[36] << 8) | (unsigned short) cal[35]);
  dev->par_gh3 = ((char) cal[38]);
  
  /* Other coefficients */
  dev->res_heat_range = ((cal[41] & 0x30) >> 4);
  dev->res_heat_val = ((char) cal[42]);
  dev->range_sw_err = (((char) cal[43] & (char) 0xF0) >> 4);
  
  /* Configurable Settings */
  dev->amb_temp = 25;                       // Ambient temperature in (C)
  dev->heater_temp = 320;                   // Heater temperature (C)
  dev->heater_duration = 150;               // Heater duration (ms)
  dev->filter_size = BME680_FILTER_SIZE_3;
  dev->temp_oversample = BME680_OS_8X;
  dev->pres_oversample = BME680_OS_4X;
  dev->hum_oversample = BME680_OS_2X;
  dev->sensor_reading_period = 183;

  pause(dev->sensor_reading_period);      // Required time needed for sensor (183 ms for default settings) to take reading (datasheet/example API provides formula...)
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