/*
   Receive Strings with IR.c
   For receiving IR strings, use the receive function.  128 is your 
   maxiumum buffer size.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

char irbuf[128];                             // Receive buffer 
int irlen, states;                           // Incoming length, button states

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    clear();
    text_size(LARGE);
    oledprint(" IR Rcv ");
    while(1)
    {
      irlen = receive(irbuf);                // Check incoming IR
      if(irlen > 0)                          // Yes? exit while loop
      {
        break;
      }          
    }
    clear();                                 // Display incoming message 
    text_size(SMALL);
    oledprint(irbuf);
    cursor(0, 6);                            // Press button to repeat
    oledprint("Again? Any btn.");
    while(!buttons());
  }
}  
