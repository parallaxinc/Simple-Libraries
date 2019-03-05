/**
 * @file libbme680.c
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



#include "simpletools.h"                      // Include simple tools
#include "bme680.h"


// Declare i2c bus pointer
bme680 *mySensor; 
//i2c *myI2cBus;

int main() {

  /* SPI interface */
  // PIN_SDO = 20
  // PIN_CLK = 21
  // PIN_SDI = 22
  // PIN_CS  = 23
  mySensor = bme680_openSPI(20, 21, 22, 23);
  
  /* i2c interface */
  // PIN_CLK = 21
  // PIN_SDA = 22
  // i2c_ADDR = 0x77
  //myI2cBus = i2c_newbus(21, 22, 0); 
  //mySensor = bme680_openI2C(myI2cBus, 0x77);
  
  
  while(1) {

    char rslt = bme680_readSensor(mySensor);
    
    if (rslt >= 0) {
      print("Temperature: %.2f deg C\r", bme680_temperature(mySensor, CELSIUS));
      print("Pressure: %.2f hPa\r", bme680_pressure(mySensor, PASCALS) / 100.0);
      print("Humidity: %.2f%%\r", bme680_humidity(mySensor));
      print("Gas Resistance: %.2f kOhms\r\r", bme680_gasResistance(mySensor) / 1000.0);
    } else {
      print("No reading available\r\r");
    }
              
    pause(3000);
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
