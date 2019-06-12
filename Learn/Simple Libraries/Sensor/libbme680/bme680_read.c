/**
 * @file bme680_read.c
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

char bme680_readSensor(bme680_t *dev) {
  char rslt = 0;
  unsigned char buff[15];
  unsigned char tries = 10;
    
  buff[0] = 0x8d;
  bme680_write(dev, 0x74, buff, 1);  // wake up the sensor to take a reading
 
  pause(dev->sensor_reading_period);
    
  while (tries) {
    bme680_read(dev, 0x1d, buff, 15);   //0x9d?

    dev->status = (buff[0] & 0x80) | (buff[14] & 0x20) | (buff[14] & 0x10);

    if (dev->status & 0x80) {
      dev->gas_index = buff[0] & 0x0F;
      dev->meas_index = buff[1];
      
      float var1 = 0;
      float var2 = 0;
      float var3 = 0;
      float var4 = 0;
      const float lookup_k1_range[16] = {0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -0.8, 0.0, 0.0, -0.2, -0.5, 0.0, -1.0, 0.0, 0.0};
      const float lookup_k2_range[16] = {0.0, 0.0, 0.0, 0.0, 0.1, 0.7, 0.0, -0.8, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      unsigned int adc_meas = 0;
      
      // Temperature conversion
      adc_meas = (unsigned int)(((unsigned int) buff[5] << 12) | ((unsigned int) buff[6] << 4) | ((unsigned int) buff[7] >> 4));
      
      var1 = ((((float) adc_meas / 16384.0) - ((float) dev->par_t1 / 1024.0)) * ((float) dev->par_t2));
      var2 = (((((float) adc_meas / 131072.0) - ((float) dev->par_t1 / 8192.0)) *
          (((float) adc_meas / 131072.0) - ((float) dev->par_t1 / 8192.0))) *
        ((float) dev->par_t3 * 16.0));
      dev->t_fine = (var1 + var2);

      dev->temperature = ((dev->t_fine) / 5120.0);
      
      // Pressure conversion
      adc_meas = (unsigned int)(((unsigned int) buff[2] << 12) | ((unsigned int) buff[3] << 4) | ((unsigned int) buff[4] >> 4));

      var1 = (((float) dev->t_fine / 2.0) - 64000.0);
      var2 = var1 * var1 * (((float) dev->par_p6) / (131072.0));
      var2 = var2 + (var1 * ((float) dev->par_p5) * 2.0);
      var2 = (var2 / 4.0) + (((float) dev->par_p4) * 65536.0);
      var1 = (((((float) dev->par_p3 * var1 * var1) / 16384.0) + ((float) dev->par_p2 * var1)) / 524288.0);
      var1 = ((1.0 + (var1 / 32768.0)) * ((float) dev->par_p1));
      var4 = (1048576.0 - ((float) adc_meas));
    
      if ((int) var1 != 0) {          // Avoid exception caused by division by zero
        var4 = (((var4 - (var2 / 4096.0)) * 6250.0) / var1);
        var1 = (((float) dev->par_p9) * var4 * var4) / 2147483648.0;
        var2 = var4 * (((float) dev->par_p8) / 32768.0);
        var3 = ((var4 / 256.0) * (var4 / 256.0) * (var4 / 256.0) *
          (dev->par_p10 / 131072.0));
        var4 = (var4 + (var1 + var2 + var3 + ((float) dev->par_p7 * 128.0)) / 16.0);
      } else {
        var4 = 0;
      }

      dev->pressure = var4;
      
      // Humidity conversion
      adc_meas = (unsigned int)(((unsigned int) buff[8] << 8) | (unsigned int) buff[9]);

      var4 = ((dev->t_fine) / 5120.0);
    
      var1 = (float)((float) adc_meas) - (((float) dev->par_h1 * 16.0) + (((float) dev->par_h3 / 2.0) *
        var4));
      var2 = var1 * ((float)(((float) dev->par_h2 / 262144.0) * (1.0 + (((float) dev->par_h4 / 16384.0) *
        var4) + (((float) dev->par_h5 / 1048576.0) * var4 * var4))));
      var3 = (float) dev->par_h6 / 16384.0;
    
      var1 = var2 + ((var3 + (((float) dev->par_h7 / 2097152.0) * var4)) * var2 * var2);
    
      if (var1 > 100.0) var1 = 100.0;
      if (var1 < 0.0) var1 = 0.0;

      dev->humidity = var1;
      
      // Gas Resistance conversion
      adc_meas = (unsigned int)((unsigned int) buff[13] << 2 | (((unsigned int) buff[14]) >> 6));
      var1 = (1340.0 + (5.0 * dev->range_sw_err));
      var2 = (var1) * (1.0 + lookup_k1_range[(buff[14] & 0x0F)] / 100.0);
      var3 = 1.0 + (lookup_k2_range[(buff[14] & 0x0F)] / 100.0);
      var1 = 1.0 / (float)(var3 * (0.000000125) * (float)(1 << (buff[14] & 0x0F)) * (((((float) adc_meas) -512.0) / var2) + 1.0));

      dev->gas_resistance = var1;
      
      break;
    }    
    pause(10);
    tries--;
  }

  do {
    bme680_read(dev, 0x74, buff, 1);
    if (buff[0] != 0x8c) {
      buff[0] = 0x8c; // Set to sleep
      bme680_write(dev, 0x74, buff, 1);
      pause(10);
    }
  } while (buff[0] != 0x8c);

  if (!tries) {
    rslt = -1;
    dev->temperature = 0.0;
    dev->pressure = 0.0;
    dev->altitude = 0.0;
    dev->humidity = 0.0;
    dev->gas_resistance = 0.0;
  }    

  return rslt;
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
