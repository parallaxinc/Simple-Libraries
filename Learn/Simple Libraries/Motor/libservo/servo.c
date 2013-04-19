/**
 * @file servo_7.c
 *
 * @author Andy Lindsay
 *
 * @version dev001
 *
 * @copyright Copyright (C) Parallax, Inc. 2012.  See end of file for
 * terms of use (MIT License).
 *
 * @brief Manages control of up to seven servos using another LMM cog.
 *
 * @detail This is the first of several options that will work with servo.h 
 * in the Propeller EDU folder.  This one uses the stamp library to show how
 * you can make a simple process and then add usefulness with additional 
 * functions.  The process inside servo_14.c will not be as intuitively obvious, 
 * and servo_32.cogc will provide an example where the servo control process
 * executes from a cog.
 * 
 * Please submit bug reports, suggestions, and improvements to         
 * this code to editor@parallax.com.
 */

#include "simpletools.h"
#include "servo.h"

static unsigned int stack[(160 + (64 * 4)) / 4];     // Stack          

static volatile int p[7] = {-1, -1, -1, -1,          // I/O pins
                     -1, -1, -1};
static volatile int t[7] = {-1, -1, -1, -1,          // Current iteration pulse widths
                     -1, -1, -1};
static volatile int tp[7] = {-1, -1, -1, -1,         // Previous iteration pulse widhts
                      -1, -1, -1};
static volatile int r[7] = {2000, 2000, 2000, 2000,  // Step sizes initialized to 2000
                     2000, 2000, 2000};

static volatile unsigned int servoCog = 0;           // Cog initialazied to zero
static volatile unsigned int lockID;                 // Lock ID 

void servo(void *par);                        // Function prototype for servo

int servo_angle(int pin, int degreeTenths)     // Set continuous rotation speed
{
  return servo_set(pin, degreeTenths + 500);   // Add center pulse width to speed
}

int servo_speed(int pin, int speed)            // Set continuous rotation speed
{
  return servo_set(pin, speed + 1500);         // Add center pulse width to speed
}

int servo_set(int pin, int time)               // Set pulse width to servo on pin 
{
  if(servoCog == 0)                           // If cog not started
  {
    int result = servo_start();                // Start the cog
    if(result == 0) return 0;                 // No cogs open
    if(result == -1) return -1;               // No locks open
  }
  int s = sizeof(p)/sizeof(int);              // Array size to s
  int i;                                      // Index variable
  while(lockset(lockID));                     // Set the lock
  for(i = 0; i < s; i++)                      // Check if existing servo
  {
    if(p[i] == pin)                           // Yes?
    {
      t[i] = time;                            // Set pulse duration
      lockclr(lockID);                        // Clear lock
      return 1;                               // Return success 
    }
  }
  if(i == s)                                  // Not existing servo?
  {
    for(i= 0; i < s; i++)                     // Look for empty slot
    {
      if(p[i]==-1)                            // Found one?
      {
        break;                                // Exit for loop, keep index
      }
    }
    if(i <= s)                                // Found empty slot?
    {
      p[i] = pin;                             // Set up pin and pulse durations
      t[i] = time;
      tp[i] = time;
      lockclr(lockID);                        // Clear the lock 
      return 1;                               // Return success 
    }
    else                                      // Servo not found, no empty slots?
    {
      lockclr(lockID);                        // Clear lock
      return 0;                               // Return, set not completed
    }
  }
}

int servo_setramp(int pin, int stepSize)      // Set ramp step for a servo
{
  int s = sizeof(p)/sizeof(int);              // Get array size
  int i;                                      // Local index variable
  while(lockset(lockID));                     // Set lock
  for(i = 0; i < s; i++)                      // Find index for servo pin
  {
    if(p[i] == pin)                           // Found pin in array?
    {
      r[i] = stepSize;                        // Set ramp step
      lockclr(lockID);                        // Clear lock
      return 1;                               // Return success
    }
  }
  lockclr(lockID);                            // Clear lock
  return 0;                                  // Return -1, pin not found
}

int servo_get(int pin)                        // Get servo position
{
  int s = sizeof(p)/sizeof(int);              // Get size of servo arrays
  int i;                                      // Declare local index
  for(i = 0; i < s; i++)                      // Look for matching pin in array
  {
    if(p[i] == pin)                           // Found matching pin?
    {
      return tp[i];                           // Return associated pulse time
    }
  }
  return -1;                                  // No pin match?  Return -1
}

void servo(void *par)                         // Servo process in other cog
{
  int s = sizeof(p)/sizeof(int);              // Get size of servo array
  int i;                                      // Local index variable
  mark();                                     // Mark the current time
  while(1)                                    // Servo control loop
  {
    while(lockset(lockID));                   // Set the lock 
    for(i = 0; i < s; i++)                    // Go through all possible servos
    {
      if(t[i] == 0)                           // Detach servo? 
      {
        input(p[i]);                          // Set I/O pin to input
        p[i] = -1;                            // Remove from list
        t[i] = -1;
      }
      if(p[i] != -1)                          // If servo entry in pin array
      {
        int tPulse =  t[i];                   // Copy requested position to var
        int diff = tPulse - tp[i];            // Check size of change
        int d = abs(diff);                    // Take absolute value
        if(r[i] < d)                          // If change larger than ramp step
        {
          int step = r[i];                    // Copy step entry to variable
          if(diff < 0)                        // If negative
          {
            step = -step;                     // Make step negative
          }
          tPulse = tp[i] + step;              // Increment pulse by step 
        }
        pulse_out(p[i], tPulse);               // Send pulse to servo
        tp[i] = tPulse;                       // Remember pulse for next time
      }
    }
    lockclr(lockID);                          // Clear the lock
    wait(20000);
  }
}

void servo_stop(void)                          // Stop servo process, free a cog
{
  if(servoCog)                                // If the cog is running
  {
    cogstop(servoCog-1);                      // Stop it
    servoCog = 0;                             // Remember that it's stopped
    lockret(lockID);                          // Return the lock
  }
}

int servo_start(void)                          // Take cog & start servo process
{
  lockID = locknew();                         // Check out a lock
  if (lockID == -1) return -1;                // Return -1 if no locks
  servo_stop();                                // Stop in case cog is running
  servoCog = cogstart(&servo, NULL, stack,    // Launch servo into new cog
             sizeof(stack)) + 1;
  return servoCog;                            // Return cog that was taken
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
