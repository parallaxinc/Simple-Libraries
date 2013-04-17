/*
  Test 2125 Tilt.c
  
  Measure tilt.  Assumes MX2125 is being held horizontally and then tilted.   
  
  http://learn.parallax.com/C/Simple-Devices-Propeller-C/tilt-acceleration
*/

#include "simpletools.h"                          // Include simpletools header
#include "mx2125.h"                               // Include mx2125 header 

int main()                                        // Main function
{
  while(1)                                        // Repeat indefinitely
  {
    int x = mx_tilt(10);                          // X-axis tilt
    int y = mx_tilt(11);                          // Y-axis tilt
    printf("%ctilt x = %d, tilt y = %d, %c\n",    // Display tilts 
            HOME,       x,           y, CLREOL);
    pause(200);                                   // 1/5th second before repeat
  }  
}

