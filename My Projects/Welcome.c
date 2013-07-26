/*
  Welcome.c
  
  Welcome to SimpleIDE, the C programming environment that makes it easy to 
  get started with the multi-core Propeller microcontroller! 
  
  To run this program:
  
    - Is this the first Parallax software you've installed on your computer?  
      If so, install USB driver's now: www.parallax.com/usbdrivers
    - Connect your Propeller board to your computer's USB.  Also connect power
      to the board if needed, and if it has a power switch, turn it on.
    - Make sure to select your COM port from the toolbar dropdown menu in the
      upper-right corner.  If you are unsure which COM port your board is 
      connected to, disconnect it and click the dropdown to check the port 
      list, then reconnect it and check again.
    - Click Program and select Run with Terminal (or click the Run with Terminal 
      button).  The SimpleIDE Terminal should appear and display the "Hello!"
      message.
      
   Next, check the Help menu for new online tutorials, software manual, and 
   reference material.
   http://learn.parallax.com/propeller-c-tutorials
*/

#include "simpletools.h"                      // Include simple tools

int main()                                    // Main function
{
  print("Hello!");                            // Display test message
}
