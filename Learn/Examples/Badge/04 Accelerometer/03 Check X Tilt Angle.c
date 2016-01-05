/*
   Check X Tilt Angle.c
   The raw accelerometer measurement can be converted to tilt angle.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int tilt_angle(int cg);                      // Function forward declaration

int x, degrees;                              // X axis and degrees

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint(" X Tilt");
  while(1)
  {
    x = accel(AX);                           // Raw measurement
    // Convert from centi-gravity -> degrees.
	degrees = tilt_angle(x);                 // Function call 
    
    cursor(0, 1);                            // Displayed
    oledprint(" %02d deg ", degrees);

    pause(20);                               // 1/50 s delay before repeat
  }    
}

int tilt_angle(int cg)                       // Centi-gravity to tilt angle
{
  if(cg > 100) cg = 100;                     // Limit input to +/- 100
  if(cg < -100) cg = -100;
  float fpcg = (float) cg;                    // Centi-gravity to floating point
  float fpangle = asin(fpcg/100.0);           // Calculate the arcsine
  fpangle *= 180.0 / PI;                      // Convert from radians to degrees
  int angle = (int) fpangle;                  // Floating point back to int
  return angle;                               // Return the angle
}  
