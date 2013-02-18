// WARNING: This is a development copy.  For public versions, 
// go to code.google.com/p/propside/downloads/list

/*
  Welcome.c
  
  Welcome to SimpleIDE, the C programming environment that 
  makes it easy to get started with the multi-core Propeller 
  microcontroller! 
  
  To run this program:
  
    - Is this the first Parallax software you've installed 
      on your computer?  If so, install USB driver's now: 
      www.parallax.com/usbdrivers
    - Connect Propeller board to computer's USB (+ power if
      needed).
    - Make sure to select your board and COM port from the 
      toolbar dropdown menus.
    - Click Tools and select Run with Terminal (or click the 
      Run with Terminal button).  
      
   Next, check the Help menu for new online tutorials, 
   software manual, and reference material.
*/

#include "simpletools.h"                      // Include simple tools

int main()                                    // Main function
{
  pause(1000);                                // Wait 1 s for terminal software
  printf("Hello!");                           // Display test message
}
