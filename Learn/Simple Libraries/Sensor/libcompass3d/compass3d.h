/**
 * @file compass3d.h
 *
 * @author Andy Lindsay
 *
 * @version v0.8
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2013. All Rights MIT Licensed.
 *
 * @brief WARNING, CONSTRUCTION ZONE: This is a preliminary library, 
 * revisions pending, not for release.  This file provides convenience 
 * functions for reading measurements from the Parallax Compass Module
 * 3-Axis HMC5883L.
 */

#include <i2c.h>

/**
 * @brief Initialize the Compass
 *
 * @details This function initializes the compass, but
 * before calling it, you have to set up an I2C bus.  
 * Example: Assuming the your program is using the 
 * simpletools library, you can use:
 *
 *   i2c mybus = i2c_init(sclPin, sdaPin)
 *
 * ... where sclPin is the number of the I/O pin number
 * connected to the compass module's SCL line and sdaPin
 * is the number of the pin connected to the module's
 * SDA line. 
 *
 * @param I2C bus pointer.  In the example above, the pointer
 * is mybus.  
 *
 * @returns void, but it will display an error message if the
 * compass module does not respond. 
 */
void CompassInit(I2C *bus);

/**
 * @brief Read values from compass
 *
 * @details This function finds a compas on the specified
 * bus, reads its x, y, and z values and loads them into
 * variables that are passed by address.
 *
 * @param *bus - a pointer to the I2C bus (mybus in the 
 * example above).
 *
 * @param *px - a pointer to a variable to receive the 
 * x value measurement.
 *
 * @param *py - a pointer to a variable to receive the 
 * y value measurement.
 *
 * @param *px - a pointer to a variable to receive the 
 * x value measurement.
 *
 * @returns void, but it will display an error message if the
 * compass module does not respond. 
 */
void CompassRead(I2C *bus, int *px, int *py, int *pz);