/*
   Receive Strings with IR.c
   For receiving IR strings, use the receive function.  128 is your 
   maxiumum buffer size.
*/
                                                                                
#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library
                                             
char irbuf[128];                             // Receive buffer 
int irlen, states, exist;                    // IR, button and EEPROM status

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)
  {
    clear();                                 // Menu
    text_size(LARGE);
    oledprint(" IR Rcv ");
    text_size(SMALL);
    cursor(0, 5);
    oledprint("     Receive-P27\n");
    oledprint("P15-Upload      ");
    text_size(LARGE);

    while(1)                                 // Wait for button press
    {
      states = buttons();
      if(states) break;
    }

    if(states == 0b0001000)                  // If P15, upload contacts
    {
      clear();
      oledprint("Upload  ...");
      contacts_displayAll();
      oledprint("Done");
      pause(250);
      continue;                              // Back to while(1)
    }      
    if(states != 0b0000001)                  // Not P27?, try again
    {
      cursor(0, 0);
      text_size(LARGE);
      oledprint("  Try    Again  ");
      pause(1000);
      continue;                              // Back to while(1)
    }
    
    // P27 has to have been pressed to get to here
    clear();
    oledprint("Ready   for IR  ");           // Display ready for IR

    // Wait for IR message
    irclear();                               // Clear ir com buffers
    while(1)
    {
      irlen = receive(irbuf);                // Check for incoming IR
      if(irlen > 0)                          // Yes? Break from while loop
      {
        break;
      }       
    }
    
    clear();                                 // Menu, what to do with data
    text_size(SMALL);
    oledprint(irbuf);
    cursor(0, 5);
    oledprint("       Store-P26");
    cursor(0, 6);
    oledprint("     Discard-P25");

    while((states = buttons()) == 0);        // Wait for button press

    text_size(LARGE);
    clear();
    if(states == 0b0000010)                  // If P26, store to EEPROM
    {
      if(!stored(irbuf)) store(irbuf);
      oledprint("Stored");
    }      
    if(states == 0b0000100)                  // if(P25), discard
    {
      oledprint("Discard");
    }      
    pause(500);                              // Pause before repeat
  }
}  


