/**
 * @file bme680_adjust_sensor_settings.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Example demonstrating how to adjust the sensor's settings
 * before taking a reading.
 */



#include "simpletools.h"                      // Include simple tools
#include "bme680.h"


bme680 *mySensor;                             // Create a new sensor instance


int main() {

  // Open the sensor using an SPI interface
  // SDO, CLK, SDI, CS
  mySensor = bme680_openSPI(20, 21, 22, 23);
  
  
  
  // Set the ambient temperature used (in deg C) by the gas sensor's calculations.
  // A temperature measurement could be taken and fed back into this setting for increased
  // accuracy.
  bme680_configure(mySensor, BME680_SETTING_AMB_TEMP, 20);
  
  // Set the temperature of the gas sensor's heating element (in deg C).
  bme680_configure(mySensor, BME680_SETTING_HEATER_TEMP, 300);
  
  // Set how long the gas sensor's heating element is turned on
  // during a measurement (in milliseconds).
  bme680_configure(mySensor, BME680_SETTING_HEATER_DURATION, 120);

  // Set the low-pass filter used by the sensor.  Higher values reduce jitter
  // but decrease accuracy.
  // Available settings are: BME680_FILTER_SIZE_1, BME680_FILTER_SIZE_3,
  // BME680_FILTER_SIZE_7, BME680_FILTER_SIZE_15, BME680_FILTER_SIZE_31.
  bme680_configure(mySensor, BME680_SETTING_FILTER_SIZE, BME680_FILTER_SIZE_15);

  // Set the oversample (number of samples taken per measurement) 
  // for the temperature sensor.  
  // Available settings are: BME680_OS_1X, BME680_OS_2X, BME680_OS_4X
  // BME680_OS_8X, BME680_OS_16X.
  bme680_configure(mySensor, BME680_SETTING_TEMP_SAMPLES, BME680_OS_16X);

  // Set the oversample (number of samples taken per measurement) 
  // for the pressure sensor.  
  // Available settings are: BME680_OS_1X, BME680_OS_2X, BME680_OS_4X
  // BME680_OS_8X, BME680_OS_16X.
  bme680_configure(mySensor, BME680_SETTING_PRESSURE_SAMPLES, BME680_OS_8X);

  // Set the oversample (number of samples taken per measurement) 
  // for the humidity sensor.
  // Available settings are: BME680_OS_1X, BME680_OS_2X, BME680_OS_4X
  // BME680_OS_8X, BME680_OS_16X.
  bme680_configure(mySensor, BME680_SETTING_HUMIDITY_SAMPLES, BME680_OS_4X);


    
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
