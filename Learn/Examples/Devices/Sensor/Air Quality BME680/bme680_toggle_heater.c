/**
 * @file bme680_toggle_heater.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Example demonstrating how to turn the internal heater for
 * the BME680's gas sensor on and off.  The heater can affect
 * temperature and humidity readings, but when it is off, the
 * sensor cannot provide gas/VOC readings.
 */



#include "simpletools.h"                      // Include simple tools
#include "bme680.h"


bme680 *mySensor;                             // Create a new sensor instance


int main() {

  // Open the sensor using an SPI interface
  // CLK, SDI, SDO, CS
  mySensor = bme680_openSPI(20, 21, 22, 23);
  
  // Turn the heating element off
  bme680_heaterDisable(mySensor);
  
  // Take 120 readings
  for (int i = 0; i < 120; i++) {  
    char rslt = bme680_readSensor(mySensor);
    
    // Make sure the reading is available and valid
    if (rslt >= 0) {
      // Print the last read temaperature in CELSIUS (FAHRENHEIT and KELVIN are also options)
      print("Temperature: %.2f deg C\t\t", bme680_temperature(mySensor, CELSIUS));
      
      // Print the last read relative humidity
      print("Humidity: %.2f%%\r", bme680_humidity(mySensor));
    }
    
    pause(200);   // wait 0.2 seconds.     
  }    
  
  // Turn the heating element back on
  bme680_heaterEnable(mySensor);
    
  while(1) {

    // Read the sensor
    char rslt = bme680_readSensor(mySensor);
    
    // Make sure the reading is available and valid
    if (rslt >= 0) {
      // Print the last read temaperature in CELSIUS (FAHRENHEIT and KELVIN are also options)
      print("Temperature: %.2f deg C\r", bme680_temperature(mySensor, CELSIUS));
      
      // Print the last read pressure in hPa (PASCALS divided by 100), (INHG, MMHG, and PSI are also options)
      print("Pressure: %.2f hPa\r", bme680_pressure(mySensor, PASCALS) / 100.0);
      
      // Print an estimate of the altitude, based on the last read pressure 
      // in METERS, (FEET are also options)
      print("Altitude: %.2f m\r", bme680_altitude(mySensor, METERS));

      // Print the last read relative humidity
      print("Humidity: %.2f%%\r", bme680_humidity(mySensor));
      
      // Print the last read gas sensor resistance value in kOhm (returns Ohms, then divide by 100)
      print("Gas Resistance: %.2f kOhms\r\r", bme680_gasResistance(mySensor) / 1000.0);
      
    } else {
      print("No reading available\r\r");
    }
    
    // Wait 3 seconds before taking another reading.
    // Reading the sensor more frequently with the gas
    // sensor's heating element ON can cause the
    // temperature and humidity readings to be skewed.
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
