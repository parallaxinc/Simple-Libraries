/**
 * @file bme680.h
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




#ifndef BME680_H
#define BME680_H

#if defined(__cplusplus)
extern "C" {
#endif

/** Measurement Unit for bme680_temperature() */
#ifndef  CELSIUS 
  #define  CELSIUS                          (0)
#endif

/** Measurement Unit for bme680_temperature() */
#ifndef  FAHRENHEIT 
  #define  FAHRENHEIT                       (1)
#endif

/** Measurement Unit for bme680_temperature() */
#ifndef  KELVIN 
  #define  KELVIN                           (2)
#endif

/** Measurement Unit for bme680_pressure() */
#ifndef  PASCALS 
  #define  PASCALS                          (0)
#endif

/** Measurement Unit for bme680_pressure() */
#ifndef  MMHG 
  #define  MMHG                             (1)
#endif

/** Measurement Unit for bme680_pressure() */
#ifndef  INHG 
  #define  INHG                             (2)
#endif

/** Measurement Unit for bme680_pressure() */
#ifndef  PSI 
  #define  PSI                              (3)
#endif

/** Measurement Unit for bme680_altitude() */
#ifndef  METERS 
  #define  METERS                           (0)
#endif

/** Measurement Unit for bme680_altitude() */
#ifndef  FEET 
  #define  FEET                             (1)
#endif


/** Over-sampling setting (None) used in bme680_configure() */
#ifndef BME680_OS_NONE
  #define BME680_OS_NONE                    (0)
#endif

/** Over-sampling setting (1x) used in bme680_configure() */
#ifndef BME680_OS_1X
  #define BME680_OS_1X                      (1)
#endif

/** Over-sampling setting (2x) used in bme680_configure() */
#ifndef BME680_OS_2X
  #define BME680_OS_2X                      (2)
#endif

/** Over-sampling setting (4x) used in bme680_configure() */
#ifndef BME680_OS_4X
  #define BME680_OS_4X                      (3)
#endif

/** Over-sampling setting (8x) used in bme680_configure() */
#ifndef BME680_OS_8X
  #define BME680_OS_8X                      (4)
#endif

/** Over-sampling setting (16x) used in bme680_configure() */
#ifndef BME680_OS_16X
  #define BME680_OS_16X                     (5)
#endif


/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_0
  #define BME680_FILTER_SIZE_0              (0)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_1
  #define BME680_FILTER_SIZE_1              (1)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_3
  #define BME680_FILTER_SIZE_3              (2)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_7
  #define BME680_FILTER_SIZE_7              (3)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_15
  #define BME680_FILTER_SIZE_15             (4)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_31
  #define BME680_FILTER_SIZE_31             (5)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_63
  #define BME680_FILTER_SIZE_63             (6)
#endif

/** IIR (Low-pass) filter setting used in bme680_configure() */
#ifndef BME680_FILTER_SIZE_127
  #define BME680_FILTER_SIZE_127            (7)
#endif


/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_AMB_TEMP
  #define BME680_SETTING_AMB_TEMP           (0)
#endif

/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_HEATER_TEMP
  #define BME680_SETTING_HEATER_TEMP        (1)
#endif

/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_HEATER_DURATION
  #define BME680_SETTING_HEATER_DURATION    (2)
#endif

/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_FILTER_SIZE
  #define BME680_SETTING_FILTER_SIZE        (3)
#endif

/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_TEMP_SAMPLES
  #define BME680_SETTING_TEMP_SAMPLES       (4)
#endif

/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_PRESSURE_SAMPLES
  #define BME680_SETTING_PRESSURE_SAMPLES   (5)
#endif

/** Setting constant used in bme680_configure() */
#ifndef BME680_SETTING_HUMIDITY_SAMPLES
  #define BME680_SETTING_HUMIDITY_SAMPLES   (6)
#endif


typedef struct bme680_st {
  // Setup
  unsigned char dev_id;             // Device ID
  char intf;                        // SPI/i2c interface
  i2c *i2c_ptr;                     // i2c bus
  char sdi_pin;                     // SPI pins
  char sdo_pin;
  char clk_pin;
  char amb_temp;                    // Ambient temperature in (C)
  unsigned short heater_temp;       // Heater temperature (C)
  unsigned char heater_duration;    // Heater duration (ms)
  unsigned char filter_size;
  unsigned char temp_oversample;
  unsigned char pres_oversample;
  unsigned char hum_oversample;
  short sensor_reading_period;
  
  // Calibration Data
  unsigned short par_h1;            // Variables to store calibrated humidity data
  unsigned short par_h2;
  char par_h3;
  char par_h4;
  char par_h5;
  unsigned char par_h6;
  char par_h7;
  char par_gh1;                     // Variables to store calibrated gas data
  short par_gh2; 
  char par_gh3;
  unsigned short par_t1;            // Variables to store calibrated temperature data
  short par_t2;
  char par_t3;                      // Variables to store calibrated pressure data
  unsigned short par_p1;
  short par_p2;
  char par_p3;
  short par_p4;
  short par_p5;
  char par_p6;
  char par_p7;
  short par_p8;
  short par_p9;
  unsigned char par_p10;
  float t_fine;                     // Variable to store t_fine size
  unsigned char res_heat_range;     // Variable to store heater resistance range
  char res_heat_val;                // Variable to store heater resistance value
  char range_sw_err;                // Variable to store error range

  // Readings
  unsigned char status;             // Contains new_data, gasm_valid & heat_stab
  unsigned char gas_index;          // The index of the heater profile used
  unsigned char meas_index;         // Measurement index to track order
  float temperature;                // Temperature in degree celsius
  float pressure;                   // Pressure in Pascal
  float altitude;
  float humidity;                   // Humidity in % relative humidity x1000
  float gas_resistance;             // Gas resistance in Ohms
} bme680_t;


typedef bme680_t bme680;

/**
 * @brief Initialize a BME680 sensor into i2c mode.
 *
 * @param *i2c_bus pointer to an i2c bus that has already been opened with i2c_open();.
 *
 * @param i2c_addr the i2c address of the device, usualy 0x76 or 0x77.
 *
 * @returns bme680_t device identifier for use with functions in bme680 library. 
 */
bme680_t *bme680_openI2C(i2c *i2c_bus, char i2c_addr);

/**
 * @brief Initialize a BME680 sensor into 4-wire SPI mode.
 *
 * @param pin_sdo the BME680's SDO (MISO) pin.
 *
 * @param pin_clk the BME680's CLK (clock) pin.
 *
 * @param pin_sdi the BME680's SDI (MOSI) pin.
 *
 * @param pin_cs the BME680's CS (select) pin.
 *
 * @returns bme680_t device identifier for use with functions in bme680 library. 
 */
bme680_t *bme680_openSPI(char pin_sdo, char pin_clk, char pin_sdi, char pin_cs);

/**
 * @brief Internal function used to set the values in the bme680_t structure
 * to their default values.
 *
 * @param *dev pointer to the bme680 device.
 */
void bme680_begin(bme680_t *dev);

/**
 * @brief Loads settings values that have been
 * saved in the bme680_t structure into the BME680 sensor.
 * 
 * @note Must be called after calling bem680_init...() and before calling
 * bme_readSensor().
 *
 * @param *dev pointer to the bme680 device.
 */
char bme680_loadSettings(bme680_t *dev);

/**
 * @brief Instructs the BME680 sensor to take a reading.  
 * Readings take approximately 200ms and should be retireved 
 * using bme680_temperature(), bme680_pressure(), bme680_humidity(),
 * bme680_altitude(), and bme680_gasResistance().
 *
 * @note The internal heating element for the gas (VOC) sensor can skew
 * temperature and humidity readings if the sensor is read at intervals
 * of under 3 seconds.  If frequent temperature and humidity readings
 * are desired, use bme680_heaterDisable() to prevent the heating element
 * from turning on.
 * 
 * @param *dev pointer to the bme680 device.
 */
char bme680_readSensor(bme680_t *dev);

/**
 * @brief Internal function used to read values from the
 * specified registers of the BME680 sensor.
 *
 * @param *dev pointer to the bme680 device.
 *
 * @param reg_addr the address of register to begin reading from.
 *
 * @param *reg_data the array to store the received data into. 
 *
 * @param len the number of bytes to read.
 */
void bme680_write(bme680_t *dev, unsigned char reg_addr, unsigned char *reg_data, unsigned short len);

/**
 * @brief Internal function used to write values to the
 * specified registers of the BME680 sensor.
 *
 * @param *dev pointer to the bme680 device.
 *
 * @param reg_addr the address of first register to write to.
 *
 * @param *reg_data the array containing alternating data and address bytes to write. 
 *
 * @param len the total number of data and address bytes to write.
 */
void bme680_read(bme680_t *dev, unsigned char reg_addr, unsigned char *reg_data, unsigned short len);

/**
 * @brief Change configurable settings for the BME680 sensor.
 *
 * @param *dev pointer to the bme680 device.
 *
 * @param setting the setting to change. May be 
 * 
 * Ambient Temperature in deg C (BME680_SETTING_AMB_TEMP) - default is 25.
 * Heater Temperature in deg C (BME680_SETTING_HEATER_TEMP) - default is 320.
 * Heater Duration in ms (BME680_SETTING_HEATER_DURATION) - default is 150.
 * Low-pass filter size (BME680_SETTING_FILTER_SIZE) - default is BME680_FILTER_SIZE_3.
 * Temperature samples to take (BME680_SETTING_TEMP_SAMPLES) - default is BME680_OS_8X.
 * Pressure samples to take (BME680_SETTING_PRESSURE_SAMPLES) - default is BME680_OS_4X.
 * Humidity samples to take (BME680_SETTING_HUMIDITY_SAMPLES) - default is BME680_OS_2X.
 * 
 * @param value the value to write into that setting. 
 */
void bme680_configure(bme680_t *dev, char setting, int value);

/**
 * @brief Close and free the memory used by the bme680 device structure.
 *
 * @param *dev pointer to the bme680 device.
 */
void bme680_close(bme680_t *dev);

/**
 * @brief Retrieve the temperature from the last read of the BME680 device.
 *
 * @param *dev Pointer to the bme680 device.
 *
 * @param unit Unit of meaure to return the measurement in.  
 * May be CELSIUS, FAHRENHEIT, or KELVIN 
 */
float bme680_temperature(bme680_t *dev, char unit);   

/**
 * @brief Retrieve the temperature from the last read of the BME680 device.
 *
 * @param *dev pointer to the bme680 device.
 *
 * @param unit Unit of meaure to return the measurement in.  
 * May be PASCALS, MMHG, INHG, or PSI.
 */
float bme680_pressure(bme680_t *dev, char unit);

/**
 * @brief Retrieve the estimated altitude from the last read of the BME680 device.
 *
 * @note this is calcualted from the pressure measurement.  It is not reliable for high altitudes,
 * and it is affected by the ambient (barometric) pressure due to weather.  For that reason,
 * the BME680 is better for measuring changes in altitude versus absolute altitude.
 *
 * @param *dev Pointer to the bme680 device.
 *
 * @param unit Unit of meaure to return the measurement in.  
 * May be METERS or FEET.
 */
float bme680_altitude(bme680_t *dev, char unit);

/**
 * @brief Retrieve the relative humidity as a percentage 
 * from the last read of the BME680 device.
 *
 * @param *dev pointer to the bme680 device.
 */
float bme680_humidity(bme680_t *dev);

/**
 * @brief Retrieve the relative humidity as a percentage 
 * from the last read of the BME680 device.
 *
 * @param *dev pointer to the bme680 device.
 */
float bme680_gasResistance(bme680_t *dev);

/**
 * @brief Allows the BME680 to send current to the heating 
 * element for its gas sensor.
 *
 * @param *dev pointer to the bme680 device.
 */
void bme680_heaterEnable(bme680_t *dev);

/**
 * @brief Turns off the current that the BME680 sends 
 * to the heating element for its gas sensor.
 *
 * @param *dev pointer to the bme680 device.
 */
void bme680_heaterDisable(bme680_t *dev);

#if defined(__cplusplus)
}
#endif
/* __cplusplus */ 
#endif
/* BME680_H */ 

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
