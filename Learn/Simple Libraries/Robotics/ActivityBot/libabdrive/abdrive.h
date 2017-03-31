//#define _monitor_

/**
 * @file abdrive.h
 *
 * @author Andy Lindsay
 *
 * @copyright 
 * Copyright (C) Parallax, Inc. 2013. All Rights MIT Licensed.
 *
 * @brief This library takes care of encoder monitoring and servo signalling, 
 * and provides a simple set of functions for making the ActivityBot go certain
 * distances and speeds.
 * <br>
 * <br>
 * For more information, go here:
 * <br>
 * <br>
 * http://learn.parallax.com/activitybot/navigation-basics
 * <br>
 * <br>
 *
 * @par Core Usage
 * A single additional core takes care of ActivityBot encoder monitoring, control system
 * algorithm execution and servo control.
 *
 * @par EEPROM Usage
 * Reads from addresses 63418..65470. 
 *
 * @par Memory Models
 * Use with CMM. 
 *
 * @version 0.5.6
 * @li Adjust drive_servoPins and drive_encoderPins documentation.
 *
 * @version 0.5.5
 * @li drive_getTicksCalc
 * @li drive_getTicks
 * @li drive_open
 * @li drive_encoderPins
 * @li drive_servoPins
 * @li Values outside interpolation table ranges do not result in
 * rotation halt. 
 * @li Turning off feedback now allows full servo speed operation
 *
 * @version 0.5.1
 * @li Trim enabled by default.
 * @li Clear trim settings during calibration. (v0.5.1)
 * @li Make trim for a direction mutually exclusive to one side. (v0.5.1)
 *
 * @todo
 * @li Make ramp go to percentage of full speed
 * @li Correct error in start string verification
 * @li Make sure that control system's compensation cannot cause the servo signal to cross
 * its direction boundary  
 * @li drive_distance
 * @li drive_getSpeedCalc
 * @li drive_getSpeedActual
 * @li Code comments
 * @li Reduce calibration array elements to 16-bit
 * @li Condense left/right duplicate code
 * @li Remove other variables
 *
 * @par Help Improve this Library
 * Please submit bug reports, suggestions, and improvements to this code to
 * editor@parallax.com.
 */

#ifndef ABDRIVE_H
#define ABDRIVE_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"
#include "simpletext.h"
#include "fdserial.h"

/*
 #ifndef interactive_development_mode
 #define interactive_development_mode
 void display_control_sys(int start, int end);
 #endif
*/

#ifndef _ActivityBot_EE_Start_
/**
 *
 * @brief ActivityBot EEPROM calibration data start address.
 */
#define _ActivityBot_EE_Start_ 63418
#endif

#ifndef _ActivityBot_EE_Pins_
#define _ActivityBot_EE_Pins_ 12
#endif

#ifndef _ActivityBot_EE_Trims_
#define _ActivityBot_EE_Trims_ 28
#endif

#ifndef _ActivityBot_EE_Left_
#define _ActivityBot_EE_Left_ 52
#endif

#ifndef _ActivityBot_EE_Right_
#define _ActivityBot_EE_Right_ 1052
#endif

#ifndef _ActivityBot_EE_End_
/**
 *
 * @brief ActivityBot EEPROM calibration data end address.
 */
#define _ActivityBot_EE_End_ 63418 + 2052
#endif

#ifndef AB_RIGHT  
#define AB_RIGHT  1
#endif

#ifndef AB_LEFT
#define AB_LEFT -1
#endif

// NEW Constants
#define SIDE_LEFT 0
#define SIDE_RIGHT 1
#define SIDE_BOTH 2

#ifndef AB_FORWARD
#define AB_FORWARD 1
#endif

#ifndef AB_BACKWARD
#define AB_BACKWARD -1
#endif

#ifndef OFF
/**
 * @brief OFF can be used in place of zero to enabled parameters in
 * functions like drive_feedback and drive_trim.
 */
#define OFF 0
#endif

#ifndef ON
/**
 * @brief ON can be used in place of a nonzero value to enabled
 * parameters in functions like drive_feedback and drive_trim.
 */
#define ON  1
#endif

void monitor_start(int monitorReps);
void monitor_stop();


// When blocking set to 0, returns value that corresponds to the 0, 1, 2 status of a manueuver.  
// In addition to SIDE_LEFT and SIDE_RIGHT, it the side parameter can receive SIDE_BOTH, and 
// returns the sum of both sides.  When that is 0, the maneuver has been completed.  
int drive_gotoStatus(int side);
           
// Set mode to 1 or ON for blocking execution of drive_goto. 
void drive_gotoMode(int mode);

// Default not set yet.  I'm imagining that it'll be 400 ticks/second-squared, which evaluates to 
// (8 ticks/s)/50th of s -> which is equivalent to call drive_setRampStep(8, 8).  
void drive_setAcceleration(int ticksPerSecondSquared);


/**
 * @brief Enables or disables encoder feedback for speed control.  
 *
 * @param enabled Set to 1 to enable feedback (default) or 0 to disable.
 */
void drive_feedback(int enabled);                      


/**
 * @brief Enables or disables drive trim which can be used to compensate for
 * mechanical wheel alignment errors  
 *
 * @param enabled Set to 1 to enable trim (default) or 0 to disable.
 */
void drive_trim(int enabled);


/**
 * @brief Stores trim values to EEPROM.
 *
 * @details Trim values can compensate for mechanical wheel alignment errors. 
 * When you set the ActivityBot's trim, you are telling it to make a certain
 * wheel turn an extra tick per certain number of ticks.  For example, you
 * can use this to make the right wheel turn 1 extra tick per every 64 ticks.
 * It will actually just expect to see an encoder transition 1/64th of a tick
 * sooner with every tick. 
 *
 * @param direction Selects to set the trim for a given direction.  Use
 * AB_FORWARD OR AB_BACKWARD.
 *
 * @param side Selects the side to make one more or less ticks per number of
 * ticks.  Use AB_LEFT or AB_RIGHT to select the left or right wheel.
 *
 * @param value Number of ticks that should elapse before the extra tick will
 * have accumulated.  Use a negative number if you want a given wheel to go
 * one less tick per number of ticks instead of one more tick.  
 */
void drive_trimSet(int direction, int side, int value);


/**
 * @brief Display the trim settings
 *
 * @details Displays most recent direction, side, and value settings from the
 * most recent call to drive_trimSet.
 */
void drive_trimDisplay(void);


/**
 * @brief Displays the interopolation table stored in EEPROM by the calibration
 * step.  For more info, see:
 *<br>
 *<br> http://learn.parallax.com/activitybot/test-and-tune-your-activitybot.
 *<br>
 */
void drive_displayInterpolation(void);


/**
 * @brief Set encoder pins to values other than the default P14 for left 
 * encoder and P15 for right encoder.  Stores values in EEPROM, so you only
 * need to call this function at the start of one program.  Programs that are 
 * after that will get the values from EEPROM.
 * 
 * @important This function should be called first, before any 
 * adbrive control functions (drive_speed, drive_goto, etc).
 *
 * @param encPinLeft I/O pin number for the left encoder signal connection.
 *
 * @param encPinRight I/O pin number for the right encoder signal connection.
 */
void drive_encoderPins(int encPinLeft, int encPinRight);


/**
 * @brief Set servo pins to values other than the default P12 for left 
 * servo and P13 for right servo.  Stores values in EEPROM, so you only
 * need to call this function at the start of one program.  Programs that are 
 * after that will get the values from EEPROM.
 * 
 * @important This function should be called first, before any 
 * adbrive control functions (drive_speed, drive_goto, etc).
 *
 * @param servoPinLeft I/O pin number for the left servo signal connection.
 *
 * @param servoPinRight I/O pin number for the right servo signal connection.
 */
void drive_servoPins(int servoPinLeft, int servoPinRight);


/**
 * @brief Set wheel speeds in encoder ticks per second.  An encoder tick is
 * 1/64th of a revolution, and makes causes the wheel to roll 3.25 mm.
 *
 * @param left Left wheel speed in ticks per second.
 *
 * @param right Left wheel speed in ticks per second.
 */
void drive_speed(int left, int right); 


/**
 * @brief This funciton allows your code to ask for a speed repeatedly in a loop, 
 * but each time your code asks for that speed, it takes a step toward the speed.
 * This helps cushon sudden maneuvers in sensor navigation, where the conditions
 * might change more rapidly than you would want your ActivityBot's speed to 
 * change.
 * 
 * @param left Left wheel speed in ticks per second.
 *
 * @param right Left wheel speed in ticks per second.
 */
void drive_rampStep(int left, int right);


/**
 * @brief Overrides the default 4 ticks/second per 50th of a second for ramping.
 *
 * @param stepsize The size of each step in ticks/second to change every 50th of
 * a second
 */
void drive_setRampStep(int stepsize);


/**
 * @brief Stop the servo/encoder system.  This is useful for reclaiming a processor 
 * for other tasks.
 */
void drive_close(void);



/**
 * @brief Start or restart the servo/encoder system.  
 */
int  drive_open();


/**
 * @brief Modifies the default maxiumum top speed for use with encoders.  The default
 * is 128 ticks/second = 2 revolutions per second (RPS).  This is the full speed that
 * drive_distance and drive_goto use.  This value can currently be reduced, but not 
 * increased.  Speeds faster than 128 ticks per second are "open loop" meaning the control
 * system does not use the encoders to correct distance/speed. 
 *
 * @param speed Maximum cruising speed for drive_distance and drive_goto.
 */
void drive_setMaxSpeed(int speed);


/**
 * @brief Make each wheel go a particular distance.  Recommended for straight forward,
 * backward, turns and pivots.  Not recommended for curves.  This function ramps up to
 * full speed if the distance is long enough.  It holds that speed until it needs to 
 * ramp down.  After ramping down it applies compensation.  This function is primarily a 
 * convenience for dead reckoning, and does not return until the maneuver has completed. 
 *
 * @param distLeft Left wheel distance.
 *
 * @param distRight Right wheel distance.
 */
void drive_goto(int distLeft, int distRight);


/**
 * @brief Get the measured number of ticks the have traveled. 
 *
 * @details The system samples the encoders at 400 times per second.
 *
 * @param *left Pointer to variable to receive the measured left distance.  
 *
 * @param *right Pointer to variable to receive the measured right distance.  
 */
void drive_getTicks(int *left, int *right);


/**
 * @brief Get the calculated number of ticks the encoders should have traveled. 
 *
 * @details The system samples the encoders at 400 times per second.
 *
 * @param *left Pointer to variable to receive the calculated left distance.  
 *
 * @param *right Pointer to variable to receive the calculated right distance.  
 */
void drive_getTicksCalc(int *left, int *right);


/*
  void drive_getSpeedCalc(int *left, int *right);
  void drive_getSpeedActual(int *left, int *right);
*/

#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif
/* ABDRIVE_H */  

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
