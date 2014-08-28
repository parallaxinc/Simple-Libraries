/*
  Test 2125 Tilt.c
  
  Measure tilt.  Assumes MX2125 is being held horizontally and then tilted.   
  
  http://learn.parallax.com/propeller-c-simple-devices/tilt-and-acceleration-mx2125
*/

#include "simpletools.h"                          // Include simpletools header
#include "mx2125.h"                               // Include mx2125 header 

int main()                                        // main function
{
  while(1)                                        // Repeat indefinitely
  {
    int x = mx_tilt(10);                          // X-axis tilt
    int y = mx_tilt(11);                          // Y-axis tilt
    print("%ctilt x = %d, tilt y = %d, %c\n",     // Display tilts 
            HOME,       x,           y, CLREOL);
    pause(200);                                   // 1/5th second before repeat
  }  
}

