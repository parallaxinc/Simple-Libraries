/*
  SoundImpactSensor StateMachine.c

  Expands on "SondImpactSensor Simple" by remembering the previous state of
  the sound impact sensor's output.

  Connect: SIG to (R = 2.2 k) to P4, 5V to 5V, GND to GND 
  
  http://www.parallax.com/product/29132
*/

#include "simpletools.h"                          // Include simpletools

int p4 = 0, p4old = 1;                            // Current & previous states

int main()                                        // Main function
{
  while(1)                                        // Main loop
  {
    int p4 = input(4);                            // Check sensor 
    if(p4 != p4old)                               // If state changed
    {
      if(p4 == 1)                                 // and if state is 1 (detected)
      {
        print("Sound detected! \n");              // Display message and wait
        pause(500);
      }
      else                                        // If state 0 (not detected)
      {
        print("Waiting for sound... \n");         // Display waiting...
      }
    }
    p4old = p4;                                   // Save old state before repeat
  }  
}
