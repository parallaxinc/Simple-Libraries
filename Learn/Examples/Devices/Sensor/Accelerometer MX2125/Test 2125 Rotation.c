/*
  Test 2125 Rotation.c
  
  Measure rotation.  Assumes MX2125 is being held vertically and rotated.   
  
  http://learn.parallax.com/C/Simple-Devices-Propeller-C/tilt-acceleration
*/

#include "simpletools.h"                      // Include simpletools header
#include "mx2125.h"                           // Include mx2125 header 

int main()                                    // Main function
{
  while(1)                                    // Repeat indefinitely
  {
    int angle = mx_rotate(10, 11);            // Rotation -> angle variable
    printf("%crotate angle = %d, %c\n",       // Display rotation angle
            HOME, angle, CLREOL);
    pause(200);                               // 1/5th second before repeat
  }  
}

