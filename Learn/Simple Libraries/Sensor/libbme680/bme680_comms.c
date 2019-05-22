/**
 * @file bme680_comms.c
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

void bme680_read(bme680_t *dev, unsigned char reg_addr, unsigned char *reg_data, unsigned short len) {
  if (dev->intf) {
    while (i2c_busy(dev->i2c_ptr, dev->dev_id)); // Start and Wait for bus to be ready
    i2c_in(dev->i2c_ptr, (unsigned char) dev->dev_id, reg_addr, 1, (unsigned char *) reg_data, len);
    i2c_stop(dev->i2c_ptr);
  } else {    
    low(dev->dev_id);
    shift_out(dev->sdi_pin, dev->clk_pin, MSBFIRST, 8, (reg_addr | 0x80));
    int bytesIn = 0;
    while (len--)
      reg_data[bytesIn++] = shift_in(dev->sdo_pin, dev->clk_pin, MSBPRE, 8);
    high(dev->dev_id);
  }  
}

void bme680_write(bme680_t *dev, unsigned char reg_addr, unsigned char *reg_data, unsigned short len) {
  if (dev->intf) {
    while (i2c_busy(dev->i2c_ptr, dev->dev_id)); // Start and Wait for bus to be ready
    i2c_out(dev->i2c_ptr, (unsigned char) dev->dev_id, reg_addr, 1, (unsigned char *) reg_data, len);
    i2c_stop(dev->i2c_ptr);
  } else {    
    low(dev->dev_id);
    shift_out(dev->sdi_pin, dev->clk_pin, MSBFIRST, 8, reg_addr);
    int bytesIn = 0;
    while (len--)
      shift_out(dev->sdi_pin, dev->clk_pin, MSBFIRST, 8, reg_data[bytesIn++]);
    high(dev->dev_id);
  }  
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
