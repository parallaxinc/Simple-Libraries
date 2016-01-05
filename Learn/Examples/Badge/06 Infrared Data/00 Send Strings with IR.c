/*
   Send Strings with IR.c
   Now that you know how to store and retrieve strings to/from EEPROM, 
   (with the store and retrieve functions) it's almost the same to send 
   and receive strings to/from another badge.  
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

// Sample contacts
char education[] = {"Education Staff\neducation@parallax.com\n"};
char sales[]     = {"Sales Staff\nsales@parallax.com\n"};
char support[]   = {"Tech Support\nsupport@parallax.com\n"};

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  
  // Menu for selecting which to send
  oledprint("IR Send");                      
  text_size(SMALL);
  cursor(0, 4);
  oledprint("P17 = Education\n");
  oledprint("P16 = Sales\n");
  oledprint("P15 = Support\n");
  
  while(1)                                   // Main loop
  {
    int states = buttons();                  // Check buttons
    if(states & 0b0111000)
    {
      rgbs(RED, RED);
    }      
    switch(states)                           // Check which button
    {
      case 0b0100000:                       // P17, send education
        send(education);
        break;
      case 0b0010000:                       // P16, send sales
        send(sales);
        break;
      case 0b0001000:                       // P15, send support
        send(support);
        break;
    }        
    if(states)                              // If just sent, delay before repeat
    {
      rgbs(OFF, OFF);
      pause(600);
    }      
  }      
}  
