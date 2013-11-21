/*
  Piezo Beep.c

  Beep a piezo speaker connected to Propeller I/O pin P4.
  
  http://learn.parallax.com/propeller-c-simple-circuits/piezo-beep
*/

#include "simpletools.h"                      // Include simpletools                   

int main()                                    // main function             
{
  freqout(4, 1000, 3000);                     // pin, duration, frequency
}
