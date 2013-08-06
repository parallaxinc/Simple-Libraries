/*
  Piezo Beep.c

  Version 0.94 for use with SimpleIDE 9.40 and its Simple Libraries
  
  Beep a piezo speaker connected to Propeller I/O pin P4.
  
  http://learn.parallax.com/propeller-c-simple-circuits/piezo-beep
*/

#include "simpletools.h"                      // Include simpletools                   

int main()                                    // main function             
{
  freqout(4, 1000, 3000);                     // pin, duration, frequency
}
