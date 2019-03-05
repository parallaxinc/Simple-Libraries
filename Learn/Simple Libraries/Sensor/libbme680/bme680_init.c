/**
 * @file bme680_init.c
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

bme680_t *bme680_openI2C(i2c *i2c_bus, char i2c_addr) {

  bme680_t* dev = (bme680_t*) malloc(sizeof(bme680_t));
  memset(dev, 0, sizeof(bme680_t));

  dev->i2c_ptr = i2c_bus;
  dev->dev_id = i2c_addr;
  dev->intf = 1;    // i2c interface

  bme680_begin(dev);
  bme680_loadSettings(dev);
  
  return dev;
}

bme680_t *bme680_openSPI(char pin_sdo, char pin_clk, char pin_sdi, char pin_cs) {

  bme680_t* dev = (bme680_t*) malloc(sizeof(bme680_t));
  memset(dev, 0, sizeof(bme680_t));

  dev->sdi_pin = pin_sdi;
  dev->sdo_pin = pin_sdo;
  dev->clk_pin = pin_clk;
  dev->dev_id = pin_cs;
  dev->intf = 0;    // spi interface

  bme680_begin(dev);
  bme680_loadSettings(dev);
  
  return dev;
}

void bme680_close(bme680_t *dev) {
  free(dev);
  dev = 0;
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
