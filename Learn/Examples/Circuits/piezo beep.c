/*
  piezo beep.c
  
  Beep a piezo speaker connected to P4.
  
  http://learn.parallax.com/propeller-c-simple-circuits/beep-piezospeaker  
  
*/

#include "simpletools.h"                      // Include simpletools header                      

int main()                                    // main function             
{
  freqout(4, 1000, 3000);                     // pin, duration, frequency
}
