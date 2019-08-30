/*
  Test 2125 Acceleration.c
  
  Measure X and Y-axis acceleration with Memsic 2125 accelerometer.
  
  http://learn.parallax.com/propeller-c-simple-devices/tilt-and-acceleration-mx2125
*/

#include "simpletools.h"                      // Include simpletools header
#include "mx2125.h"                           // Include mx2125 header 

int main()                                    // main function
{
  while(1)                                    // Repeat indefinitely
  {
    int x = mx_accel(10);                     // X-axis acceleration 
    int y = mx_accel(11);                     // Y-axis acceleration
    print("%cx = %d, y = %d, %c\n",           // Display both
           HOME, x,      y,  CLREOL);
    pause(200);                               // 1/5th second before repeat
  }  
}

