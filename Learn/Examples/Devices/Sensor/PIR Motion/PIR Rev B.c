/*
  PIR Rev B.c
  
  http://learn.parallax.com/propeller-c-simple-devices/pir-motion-sensor

  Connect:
    OUT to P5
    VCC to 3.3V
    GND to GND

  The PIR sensors OUT pin sends a high signal for several seconds if motion is detected.  
  This output is copied to a variable named state with the statement: state = input(5).  
  The state variable will store 1 if motion has been detected recently, or 0 if it has
  not.   Detected output (state = 1) takes several seconds to clear after motion event 
  is over.
*/

#include "simpletools.h"                      // Include simpletools library

int main()                                    // Main function
{
  while(1)                                    // Main loop
  {
    int state = input(5);                     // Check sensor (1) motion, (0) no motion
    print("%c state = %d%c\n",                // Display sensor
           HOME, state, CLREOL);
    pause(200);                               // Pause 1/5 second before repeat
  }  
}

