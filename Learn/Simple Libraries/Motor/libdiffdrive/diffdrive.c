#include "diffdrive.h"                           // Include servo lib funct defs

int pinLeft, pinRight, rampLeft, rampRight;   // Global variables

void drivePins(int left, int right)           // drivePins function
{
  pinLeft = left;                             // Local to global assignments
  pinRight = right;
}

void driveSpeeds(int left, int right)         // driveSpeeds function
{
  servoSpeed(pinLeft, left);                  // Use vals in servoSpeed calls
  servoSpeed(pinRight, -right);
}

void driveRampSteps(int left, int right)      // driveRampSteps function
{
  rampStep(pinLeft, left);                    // Use vals in rampStep calls
  rampStep(pinRight, right);
}

void driveSleep()                             // driveSleep function
{
  servoSet(pinLeft, 0);                       // Put servos to sleep
  servoSet(pinRight, 0);
}

void driveStop()                              // driveStop function
{
  servoStop();                                // Stop the servo processor
}

