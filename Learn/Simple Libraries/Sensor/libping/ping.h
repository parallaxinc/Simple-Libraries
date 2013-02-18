/**
 * @file ping.h
 *
 * @author Andy Lindsay
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2012. All Rights MIT Licensed.
 *
 * @brief CONSTRUCTION ZONE: This is a preliminary library, 
 * revisions pending, not for release.  This library 
 * provides convenience functions for the Ping))) Ultrasonic 
 * Distance Sensor.
 */

/**
 * @brief Measure echo time in terns of Propeller system clock
 * ticks.
 *
 * @param pin Number of the I/O pin to set to connected to the
 * Ping))) sensor's SIG line.
 *
 * @returns the number of clock ticks it took for the Ping)))'s
 * echo to return to it.
 */
int ping(int pin);

/**
 * @brief Report Ping))) measurement as a centimeter distance.
 *
 * @param pin Number of the I/O pin to set to connected to the
 * Ping))) sensor's SIG line.
 *
 * @returns measured centimeter distance.
 */
int ping_cm(int pin);

/**
 * @brief Report Ping))) measurement as an inch distance.
 *
 * @param pin Number of the I/O pin to set to connected to the
 * Ping))) sensor's SIG line.
 *
 * @returns measured inch distance.
 */
int ping_inches(int pin);
