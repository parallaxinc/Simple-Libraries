#include "servodiffdrive.h"                   // Include servo lib funct defs

int pinLeft, pinRight, rampLeft, rampRight;   // Global variables

void drive_pins(int left, int right)          // drivePins function
{
  pinLeft = left;                             // Local to global assignments
  pinRight = right;
}

void drive_speeds(int left, int right)        // driveSpeeds function
{
  servo_speed(pinLeft, left);                 // Use vals in servoSpeed calls
  servo_speed(pinRight, -right);
}

void drive_setramp(int left, int right)       // driveRampSteps function
{
  servo_setramp(pinLeft, left);               // Use vals in rampStep calls
  servo_setramp(pinRight, right);
}

void drive_sleep()                            // driveSleep function
{
  servo_set(pinLeft, 0);                      // Put servos to sleep
  servo_set(pinRight, 0);
}

void drive_stop()                             // driveStop function
{
  servo_stop();                               // Stop the servo processor
}

