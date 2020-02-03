/**
 * @file lis3dh.h
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2014. All Rights MIT Licensed.
 *
 * @brief Simplifies reading Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 */


#ifndef LIS3DH_H
#define LIS3DH_H

#if defined(__cplusplus)
extern "C" {
#endif



#include "simpletools.h"


/**
 * @defgroup group-1 Constant definitions
 *
 * Constant definitions to simplify coding with the Parallax LIS3DH 3-Axis Accelerometer Module
 *
 * @{
 *   
 */
#define LIS3DH_STATUS_REG_AUX     0x07 // r 07 000 0111 Output
#define LIS3DH_OUT_ADC1_L         0x08 // r 08 000 1000 Output
#define LIS3DH_OUT_ADC1_H         0x09 // r 09 000 1001 Output
#define LIS3DH_OUT_ADC2_L         0x0A // r 0A 000 1010 Output
#define LIS3DH_OUT_ADC2_H         0x0B // r 0B 000 1011 Output
#define LIS3DH_OUT_ADC3_L         0x0C // r 0C 000 1100 Output
#define LIS3DH_OUT_ADC3_H         0x0D // r 0D 000 1101 Output
#define LIS3DH_WHO_AM_I           0x0F // r 0F 000 1111 00110011 Device identification register
#define LIS3DH_WHO_AM_I_REPLY     0x33 // Expected reply to WHO_AM_I
#define LIS3DH_CTRL_REG0          0x1E // rw 1E 001 1110 00010000
#define LIS3DH_TEMP_CFG_REG       0x1F // rw 1F 001 1111 00000000
#define LIS3DH_CTRL_REG1          0x20 // rw 20 010 0000 00000111
#define LIS3DH_CTRL_REG2          0x21 // rw 21 010 0001 00000000
#define LIS3DH_CTRL_REG3          0x22 // rw 22 010 0010 00000000
#define LIS3DH_CTRL_REG4          0x23 // rw 23 010 0011 00000000
#define LIS3DH_CTRL_REG5          0x24 // rw 24 010 0100 00000000
#define LIS3DH_CTRL_REG6          0x25 // rw 25 010 0101 00000000
#define LIS3DH_REFERENCE          0x26 // rw 26 010 0110 00000000
#define LIS3DH_STATUS_REG         0x27 // r 27 010 0111 Output
#define LIS3DH_OUT_X_L            0x28 // r 28 010 1000 Output
#define LIS3DH_OUT_X_H            0x29 // r 29 010 1001 Output
#define LIS3DH_OUT_Y_L            0x2A // r 2A 010 1010 Output
#define LIS3DH_OUT_Y_H            0x2B // r 2B 010 1011 Output
#define LIS3DH_OUT_Z_L            0x2C // r 2C 010 1100 Output
#define LIS3DH_OUT_Z_H            0x2D // r 2D 010 1101 Output
#define LIS3DH_FIFO_CTRL_REG      0x2E // rw 2E 010 1110 00000000
#define LIS3DH_FIFO_SRC_REG       0x2F // r 2F 010 1111 Output
#define LIS3DH_INT1_CFG           0x30 // rw 30 011 0000 00000000
#define LIS3DH_INT1_SRC           0x31 // r 31 011 0001 Output
#define LIS3DH_INT1_THS           0x32 // rw 32 011 0010 00000000
#define LIS3DH_INT1_DURATION      0x33 // rw 33 011 0011 00000000
#define LIS3DH_INT2_CFG           0x34 // rw 34 011 0100 00000000
#define LIS3DH_INT2_SRC           0x35 // r 35 011 0101 Output
#define LIS3DH_INT2_THS           0x36 // rw 36 011 0110 00000000
#define LIS3DH_INT2_DURATION      0x37 // rw 37 011 0111 00000000
#define LIS3DH_CLICK_CFG          0x38 // rw 38 011 1000 00000000
#define LIS3DH_CLICK_SRC          0x39 // r 39 011 1001 Output
#define LIS3DH_CLICK_THS          0x3A // rw 3A 011 1010 00000000
#define LIS3DH_TIME_LIMIT         0x3B // rw 3B 011 1011 00000000
#define LIS3DH_TIME_LATENCY       0x3C // rw 3C 011 1100 00000000
#define LIS3DH_TIME_WINDOW        0x3D // rw 3D 011 1101 00000000
#define LIS3DH_ACT_THS            0x3E // rw 3E 011 1110 00000000
#define LIS3DH_ACT_DUR            0x3F // rw 3F 011 1111 00000000
/** @} */


/**
 * @defgroup group-2 Mask definitions
 *
 * Mask definitions to simplify coding with the Parallax LIS3DH 3-Axis Accelerometer Module
 *
 * @{
 *   
 */
#define LIS3DH_MASK_READSINGLE    0x80 // 0b10000000
#define LIS3DH_MASK_READREPEAT    0xC0 // 0b11000000
#define LIS3DH_MASK_BDUMODE       0x80 // 0b10000000
#define LIS3DH_MASK_SPIMODE       0x01 // 0b00000001
#define LIS3DH_RANGE_16           0x03 // 0b00000011
#define LIS3DH_RANGE_8            0x02 // 0b00000010
#define LIS3DH_RANGE_4            0x01 // 0b00000001
#define LIS3DH_RANGE_2            0x00 // 0b00000000
#define LIS3DH_AXIS_X             0b01 // Axis X mask
#define LIS3DH_AXIS_Y             0b10 // Axis Y mask
#define LIS3DH_AXIS_Z             0b11 // Axis Z mask  
#define LIS3DH_ADC_1              0b01 // ADC 1 mask
#define LIS3DH_ADC_2              0b10 // ADC 2 mask
#define LIS3DH_ADC_3              0b11 // ADC 3 mask
#define LIS3DH_SPIMODE_3          0b01 // SPI Mode 3 mask
#define LIS3DH_SPIMODE_4          0b00 // SPI Mode 4 mask
#define LIS3DH_BDUMODE_CONTINUOUS 0b01 // BDU continuous mode mask
#define LIS3DH_BDUMODE_CONSISTENT 0b00 // BDU consistent mode mask

/** @} */


/**
 * @defgroup group-3 Structure and Type definitions * 
 *
 * @{
 *   
 */


/**
 * Structure to hold configuration values for LIS3DH module.
 */
typedef struct lis3dh_st
{
  volatile int tempcalC; // for degrees Celcius
  
  volatile int tiltavgX;
  volatile int tiltavgY;
  volatile int tiltavgZ;
  volatile int tiltavg_factor;
  
  int sdi_pin;
  int sdo_pin;
  int sck_pin;
  int cs_pin;
 
} lis3dh_t;


// Simpler type name for use with SimpleIDE
typedef lis3dh_t lis3dh;



/** @} */


/**
 * @defgroup group-4 Functions
 * 
 *
 * @{
 *   
 */


                      

/**
 * @brief Initialize the sensor with typical configuration for reading axis and adc. Uses 3-Wire SPI mode
 *
 * @param pinSCK I/O pin connected to the SCK pin.
 *
 * @param pinSDI I/O pin connected to the SDI pin.
 *
 * @param pinCS I/O pin connected to the /CS pin.
 * 
 * @returns A Pointer to the sensor device structure, or NULL on failure
 */
lis3dh_t *lis3dh_init(int pinSCK, int pinSDI, int pinCS);



/**
 * @brief Initialize the sensor with typical configuration for reading axis and adc. Uses 4-Wire SPI mode
 *
 * @param pinSCK I/O pin connected to the SCK pin.
 *
 * @param pinSDI I/O pin connected to the SDI pin.
 *
 * @param pinSDO I/O pin connected to the SDO pin.
 *
 * @param pinCS I/O pin connected to the /CS pin.
 * 
 * @returns A Pointer to the sensor device structure, or NULL on failure
 */
lis3dh_t *lis3dh_init4wire(int pinSCK, int pinSDI, int pinSDO, int pinCS);



/**
 * @brief Shutdown the sensor, set configuration defaults with sensor disabled and clear buffers.
 *
 * @param device Pointer to the sensor device structure
 */
void lis3dh_shutdown(lis3dh_t *device);



/**
 * @brief Reads the sensor identification register (WhoAmI).
 * 
 * @param device Pointer to the sensor device structure
 *
 * @returns Value must be 0x33 (51) to indicate valid LIS3DH sensor.
 * 
 */
int lis3dh_getWhoAmI(lis3dh_t *device);



/**
 * @brief Sets the bit resolution for the sensor readings. 8-bit, 10-bit or 12-bit.
 *
 * @details Values returned when reading the accelerometer axis or adc will be sampled according to the resolution number of bits.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @param bits Value to set the sensor resolution. Must be 8, 10 or 12.
 * 
 */
void lis3dh_setResolution(lis3dh_t *device, int bits);



/**
 * @brief Reads the bit resolution setting from the sensor. 8-bit, 10-bit or 12-bit.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @returns Value representing the sensor resolution in bits (8, 10 or 12) or 0 for invalid configuration.
 *
 */
int lis3dh_getResolution(lis3dh_t *device);



/**
 * @brief Sets the g measurement range to +/- 2, +/-4, +/- 8, +- 16 g.
 *
 * @details This function makes the sensor apply scalars to the accelerometer readings. Higher range setting reduces sensitivy.
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param range Value representing the GForce range (sensitivity). Must be 2, 4, 8 or 16
 * 
 */
void lis3dh_setRange(lis3dh_t *device, int range);



/**
 * @brief Reads the g measurement range; one of +/- 2, +/-4, +/- 8, +- 16 g.
 * 
 * @param device Pointer to the sensor device structure
 *
 * @returns Value of the GForce sensitivy range. 2, 4, 8 or 16
 *
 */
int lis3dh_getRange(lis3dh_t *device);



/**
 * @brief Sets the SPI mode to either 3-wire or 4-wire
 *
 * @param device Pointer to the sensor device structure
 *
 * @param mode Value representing SPI wire mode. Must be 3 or 4.
 * 
 */
void lis3dh_setSPImode(lis3dh_t *device, int mode);



/**
 * @brief Read the SPI mode currently configured in the LIS3DH module; either 3-wire or 4-wire
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @returns Value representing the active SPI mode: 3 or 4
 *
 */
int lis3dh_getSPImode(lis3dh_t *device);



/**
 * @brief Sets the sensor BDU (Block Data Update) mode.
 *
 * @param device Pointer to the sensor device structure
 *
 * @param mode expects a constant which represents the BDU mode (LIS3DH_BDUMODE_COMPLETE  or  LIS3DH_BDUMODE_CONTINUOUS)
 * 
 * @details LIS3DH_BDUMODE_CONTINUOUS means data is ready to be read as each register is updated
 *          LIS3DH_BDUMODE_CONSISTENT means data is only ready to be read when both LSB and MSB registers are updated
 *
 */
void lis3dh_setBDUmode(lis3dh_t *device, int mode);



/**
 * @brief Sets ADC mode for the Parallax LIS3DH 3-Axis Accelerometer Module.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @param adcEnable 1 = ADC enabled, 0 = ADC disabled
 * 
 * @param tempEnable ADC channel 3 (AD3) source control. 1 = Internal temperature sensor, 0 = Input on AD3 pin
 *
 * @note To read from the internal temperature sensor, both adcEnable and tempEnable must be set to 1.
 */
void lis3dh_setADCmode(lis3dh_t *device, int adcEnable, int tempEnable);



/**
 * @brief Gets raw adc measurements from all three ADC channels.
 * 
 * @details ADC resolution is user-configured in the sensor to 8 or 10 bit. (Refer to setResolution and getResolution functions).
 *
 * @note Channel 1 range is 0-8000mV. Channel 2 and 3 ranges are 900-1800mV.
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param *ad1 Variable to store ADC channel 1 reading into, scaled to ADC resolution.
 * 
 * @param *ad2 Variable to store ADC channel 2 reading into, scaled to ADC resolution.
 * 
 * @param *ad3 Variable to store ADC channel 3 reading into, scaled to ADC resolution.
 * 
 */
void lis3dh_adc(lis3dh_t *device, int *ad1, int *ad2, int *ad3);

                    
                    
/**
 * @brief Gets raw adc measurement from a single ADC channel.
 * 
 * @details ADC resolution is user-configured in the sensor to 8 or 10 bit. (Refer to setResolution and getResolution functions).
 *
 * @note Channel 1 range is 0-8000mV. Channel 2 and 3 ranges are 900-1800mV.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @param channel Value of the ADC channel to read from. Must be 1, 2 or 3.
 *
 * @returns raw ADC reading from specified channel, scaled to ADC resolution.
 * 
 */
int lis3dh_getADC(lis3dh_t *device, int channel);                    
                    


/**
 * @brief Gets mV adc measurements from all three ADC channels.
 *
 * @details ADC resolution is user-configured in the sensor to 8 or 10 bit. (Refer to setResolution and getResolution functions).
 * 
 * @note Channel 1 range is 0-8000mV. Channel 2 and 3 ranges are 900-1800mV.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @param *ad1 Variable to store ADC channel 1 reading into, scaled to ADC resolution.
 * 
 * @param *ad2 Variable to store ADC channel 2 reading into, scaled to ADC resolution.
 * 
 * @param *ad3 Variable to store ADC channel 3 reading into, scaled to ADC resolution.
 * 
 */
void lis3dh_adc_mV(lis3dh_t *device, int *ad1, int *ad2, int *ad3);



/**
 * @brief Gets mV adc measurement from a single ADC channel.
 * 
 * @details ADC resolution is user-configured in the sensor to 8 or 10 bit. (Refer to setResolution and getResolution functions).
 *
 * @note Channel 1 range is 0-8000mV. Channel 2 and 3 ranges are 900-1800mV.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @param channel Value of the ADC channel to read from. Must be 1, 2 or 3.
 *
 * @returns mV ADC reading from specified channel, scaled to ADC resolution.
 * 
 */
int lis3dh_getADC_mV(lis3dh_t *device, int channel);



/**
 * @brief Sets the actual temperature to provide a reference for the relative temperature sensor.
 * 
 * @details The internal temperature sensor is a relative mode sensor, and requires calibration before use. 
 *
 * @param device Pointer to the sensor device structure
 *
 * @param actualTempC Value of the temperature in degrees Celcius, where the sensor is being used.
 *
 */
void lis3dh_tempCal_C(lis3dh_t *device, int actualTempC);



/**
 * @brief Sets the actual temperature to provide a reference for the relative temperature sensor.
 * 
 * @details The internal temperature sensor is a relative mode sensor, and requires calibration before use.
 *
 * @note The sensor operates in Celcius internally. Fahrenheit values are converted automatically, and may lose accuracy compared with Celcius calibration.
 *
 * @param device Pointer to the sensor device structure
 * 
 * @param actualTempF Value of the temperature in degrees Fahrenheit, where the sensor is being used.
 *
 */
void lis3dh_tempCal_F(lis3dh_t *device, int actualTempF);



/**
 * @brief Reads the raw relative temperature value from the sensor.
 * 
 * @details The internal temperature sensor is a relative mode sensor, and requires calibration before use.
 * In 8-bit mode, the raw value will change 1 digit / degree Celcius change. 
 *
 * @note The sensor operates in Celcius internally. Fahrenheit values are converted automatically, and may lose accuracy.
 *
 * @param device Pointer to the sensor device structure
 *
 * @returns Value of the temperature change.
 *
 */
int lis3dh_tempRaw(lis3dh_t *device);



/**
 * @brief Reads the calibrated (referenced) temperature value from the sensor.
 * 
 * @details The internal temperature sensor is a relative mode sensor, and requires calibration before use.
 * In 8-bit mode, the raw value will change 1 digit / degree Celcius change. 
 *
 * @note The sensor operates in Celcius internally. Fahrenheit values are converted automatically, and may lose accuracy.
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @returns Value of the temperature, in degrees Celcius.
 *
 */
int lis3dh_temp_C(lis3dh_t *device);



/**
 * @brief Reads the calibrated (referenced) temperature value from the sensor.
 * 
 * @details The internal temperature sensor is a relative mode sensor, and requires calibration before use.
 * In 8-bit mode, the raw value will change 1 digit / degree Celcius change. 
 *
 * @note The sensor operates in Celcius internally. Fahrenheit values are converted automatically, and may lose accuracy.
 *
 * @param device Pointer to the sensor device structure
 *
 * @returns Value of the temperature, in degrees Fahrenheit.
 *
 */
int lis3dh_temp_F(lis3dh_t *device);




/**
 * @brief Gets raw accelerometer measurements from all three axis (x, y, z).
 *
 * @details Resolution is user-configured in the sensor to 8, 10 or 12 bit. (Refer to setResolution and getResolution functions).
 *          Range is user-configured in the sensor as +/- 2, +/-4, +/- 8, +- 16 g. (Refer to setRange and getRange functions).
 * 
 * @param device Pointer to the sensor device structure
 * 
 * @param *x Variable to store x axis reading into, scaled by resolution and range.
 * 
 * @param *y Variable to store x axis reading into, scaled by resolution and range.
 * 
 * @param *z Variable to store x axis reading into, scaled by resolution and range.
 *
 * @returns 1 if new data is available, 0 if no new data is available.
 * 
 */
//int lis3dh_accel(int *x, int *y, int *z);
int lis3dh_accel(lis3dh_t *device, int *x, int *y, int *z);


/**
 * @brief Gets raw accelerometer measurements for a single axis (x, y, or z).
 *
 * @details Resolution is user-configured in the sensor to 8, 10 or 12 bit. (Refer to setResolution and getResolution functions).
 *          Range is user-configured in the sensor as +/- 2, +/-4, +/- 8, +- 16 g. (Refer to setRange and getRange functions).
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param axis Value of the axis to read from. Must be 1, 2 or 3 (representing x, y or z).
 * 
 * @returns 1 if new data is available, 0 if no new data is available, or invalid axis requested.
 * 
 */
int lis3dh_getAccel(lis3dh_t *device, int axis);



/**
 * @brief Gets mg (milli-g's) accelerometer measurements from all three axis (x, y, z).
 *
 * @details Resolution is user-configured in the sensor to 8, 10 or 12 bit. (Refer to setResolution and getResolution functions).
 *          Range is user-configured in the sensor as +/- 2, +/-4, +/- 8, +- 16 g. (Refer to setRange and getRange functions).
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param *xmg Variable to store x axis reading into, scaled by resolution and range, converted to milli-g's.
 * 
 * @param *ymg Variable to store x axis reading into, scaled by resolution and range, converted to milli-g's.
 * 
 * @param *zmg Variable to store x axis reading into, scaled by resolution and range, converted to milli-g's.
 *
 * @returns 1 if new data is available, 0 if no new data is available.
 * 
 */
int lis3dh_accel_mg(lis3dh_t *device, int *xmg, int *ymg, int *zmg);



/**
 * @brief Gets mg (milli-g's) accelerometer measurements from a single axis (x, y, or z).
 *
 * @details Resolution is user-configured in the sensor to 8, 10 or 12 bit. (Refer to setResolution and getResolution functions).
 *         Range is user-configured in the sensor as +/- 2, +/-4, +/- 8, +- 16 g. (Refer to setRange and getRange functions).
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param axis Value of the axis to read from. Must be 1, 2 or 3 (representing x, y or z).
 * 
 * @returns 1 if new data is available, 0 if no new data is available, or invalid axis requested.
 * 
 */
int lis3dh_getAccel_mg(lis3dh_t *device, int axis);



/**
 * @brief Gets tilt angle measurements for each axis, and magnitude of motion.
 *
 * @details Angle to each axis in degrees, 
                  X relative to ground
                  Y relative to ground
                  Z relative to gravity.
            Motion is the sum of g-force on all axis relative to gravity at ground level (1G). 
                  0 is motionless, larger positve or negative values represent more intense motion.
                  The motion value could be used on it's own for projects requiring vibration sensing.
            
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param *ax Variable to store angle of x axis relative to ground.
 * 
 * @param *ay Variable to store angle of y axis relative to ground.
 * 
 * @param *az Variable to store angle of z axis relative to gravity.
 *
 * @param *motion Variable to store positive or negative value representing intensity of motion, with 0 being motionless at ground level.
 * 
 * @returns 1 if new data is available, 0 if no new data is available, or invalid request.
 * 
 */
int lis3dh_tilt(lis3dh_t *device, int *ax, int *ay, int *az, int *motion);


/**
 * @brief Optional configuration for tilt sensor.
 *
 * @details Values stored in RAM. Reasonable defaults are set by the library.
 * 
 * @param device Pointer to the sensor device structure
 *
 * @param avg_factor Percentage of new data added to tilt readings low pass filter (moving average).
 *                   Valid values are 0 to 100. (Setting 0 or 100 will disable the filter.
 *                   For example, if avg_factor is 75, moving average calculation will include 75% new data and 25% existing data.
 *                   Default value = 100 (moving average low pass filter disabled).
 *
 * @returns 1 if operation successful, 0 if operation failed (invalid values).
 * 
 */
int lis3dh_tiltConfig(lis3dh_t *device, int avg_factor); 



/**
 * @brief write a byte value to an LIS3DH register
 *
 * @param device Pointer to the sensor device structure
 *
 * @param address LIS3DH register address.
 *
 * @param value Configuration value for the register.
 */
//void lis3dh_writeByte(unsigned char address, unsigned char value);
void lis3dh_writeByte(lis3dh_t *device, unsigned char address, unsigned char value);


/**
 * @brief Read a value from an LIS3DH register
 *
 * @param device Pointer to the sensor device structure
 *
 * @param address LIS3DH register address.
 *
 * @returns Value stored by the LIS3DH register.
 */
//unsigned char lis3dh_readByte(unsigned char address);
unsigned char lis3dh_readByte(lis3dh_t *device, unsigned char address);

/** @} */


#if defined(__cplusplus)
}
#endif
/* __cplusplus */ 
#endif
/* LIS3DH_H */ 




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





