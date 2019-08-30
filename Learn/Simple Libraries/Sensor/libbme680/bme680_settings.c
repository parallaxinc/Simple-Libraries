/**
 * @file bme680_settings.c
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

char bme680_loadSettings(bme680_t *dev) {
  unsigned char reg_data[7];

  if (dev->heater_temp > 400) dev->heater_temp = 400;

  float var1 = ((((float) dev->par_gh2 / (32768.0)) * (0.0005)) + 0.00235);
  float var2 = ((((float) dev->par_gh1 / (16.0)) + 49.0) * 
    (1.0 + (var1 * (float) dev->heater_temp)));  // Heater temp value
  float var3 = (var2 + (((float) dev->par_gh3 / (1024.0)) * 
    (float) dev->amb_temp));         // Ambient temp value

  reg_data[0] = (unsigned char)(3.4 * ((var3 * (4 / (4 + (float) dev->res_heat_range)) * 
    (1 / (1 + ((float) dev->res_heat_val * 0.002)))) - 25));
  reg_data[1] = 0x64;

  if (dev->heater_duration >= 4032) {     // Heater duration value
    reg_data[4] = 255;
  } else {
    while (dev->heater_duration > 63) {
      dev->heater_duration /= 4;
      reg_data[4] += 64;
    }
    reg_data[4] += dev->heater_duration;
  }

  reg_data[2] = reg_data[4];
  
  bme680_write(dev, 0x5a, reg_data, 3);

  do {
    bme680_read(dev, 0x74, reg_data, 1);
    if (reg_data[0] != 0x8c) {
      reg_data[0] = 0x8c; // Set to sleep
      bme680_write(dev, 0x74, reg_data, 1);
      pause(10);
    }
  } while (reg_data[0] != 0x8c);

  reg_data[0] = ((dev->filter_size << 2) & 0x1C); // Set filter size
  reg_data[1] = 0x74;
  reg_data[2] = ((dev->temp_oversample << 5) & 0xE0) | ((dev->pres_oversample << 2) & 0x1C); // Temp | Pressure oversampling
  reg_data[3] = 0x72;
  reg_data[4] = (dev->hum_oversample & 0x07); // Humidity oversampling
  reg_data[5] = 0x71;
  reg_data[6] = 0x10;

  bme680_write(dev, 0x75, reg_data, 7);

  return 0;
}

void bme680_configure(bme680_t *dev, char setting, int value) {
  switch(setting) {
    case BME680_SETTING_AMB_TEMP:
      dev->amb_temp = (char) value;
      break;
    case BME680_SETTING_HEATER_TEMP:
      dev->heater_temp = (unsigned short) value;
      break;
    case BME680_SETTING_HEATER_DURATION:
      dev->heater_duration = (unsigned char) value;
      break;
    case BME680_SETTING_FILTER_SIZE:
      dev->filter_size = (unsigned char) value;
      break;
    case BME680_SETTING_TEMP_SAMPLES:
      dev->temp_oversample = (unsigned char) value;
      break;
    case BME680_SETTING_PRESSURE_SAMPLES:
      dev->pres_oversample = (unsigned char) value;
      break;
    case BME680_SETTING_HUMIDITY_SAMPLES:
      dev->hum_oversample = (unsigned char) value;
      break;
  }    
  int dur_temp = 0;
  dur_temp = (1 << (dev->temp_oversample - 1)) + (1 << (dev->pres_oversample - 1)) + (1 << (dev->hum_oversample - 1));
  dur_temp = 183 + dur_temp / 15;
  dev->sensor_reading_period = dur_temp;
  
  bme680_loadSettings(dev);
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
