/*
  Test SIRC Remote.c

  http://learn.parallax.com/propeller-c-simple-devices/ir-receiver-and-remote

  Connect 38 kHz IR receiver to Propeller P10
  Decodes button presses on Sony-compatible IR remote 
  Run with Terminal 
*/

#include "simpletools.h"                      // Libraries included
#include "sirc.h"

int main()                                    // main function
{
  sirc_setTimeout(1000);                      // -1 if no remote code in 1 s

  while(1)                                    // Repeat indefinitely
  {                                         
                                              //  decoding signal from P10
    print("%c remote button = %d%c",          //  Display button # decoded
          HOME, sirc_button(10), CLREOL);     //  from signal on P10
  
    pause(100);                               // 1/10 s before loop repeat
  }  
}


