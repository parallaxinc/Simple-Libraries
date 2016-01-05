/*
   Check XY Rotation Angle.c
   For rotation, hold the badge straight up/down, and rotate it in front of
   you as though it's a steering wheel.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int xy_rotation(int x, int y);               // Function forward declaration

int x, y, degrees;                           // X,Y inputs, degree output

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("Rotation");                     
  while(1)
  {
    x = accel(AX);                           // Get x and y axes
    y = accel(AY);
    // Convert from xy centi-gravity 
	// to degrees of rotation.
    degrees = xy_rotation(x, y);             // Function call
    
    cursor(0, 1);                            // Display result
    oledprint("%03d deg ", degrees);

    pause(20);
  }    
}

// Convert from xy centi-gravity to degrees of rotation.
int xy_rotation(int x, int y)
{
  float fpx = (float) x;                     // int -> float conversions
  float fpy = (float) y;

  float fpangle = atan2(fpx, fpy);           // Arctangent(x/y)
  fpangle *= 180.0 / PI;                     // Convert to radians to degrees
  int angle = (int) fpangle;                 // Convert float angle to int
  if(angle < 0) angle = 360 + angle;         // -180 to 180 -> 0 to 360 
  return angle;                              // Return angle
}  
