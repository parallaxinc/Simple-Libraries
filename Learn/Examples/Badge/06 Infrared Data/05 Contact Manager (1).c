/*
   Contact Manager (1).c
   Example contact manager that can be used to exchange contact info with 
   other badges.
*/
                                                                               
#include "simpletools.h"                      // Include simpletools library
#include "badgetools.h"                       // Include badgetools library
                                              
char screenName[] =                           // Screen display name
     "  EDU   ";

char my[] =                                   // My contact info for shareing
     "Education Staff\neducation@parallax.com.com\n";

char irbuf[128];                              // Receive buffer 
int irlenb, states, shaken;                   // Incoming length, button states

void main()                                   // Main function
{
  badge_setup();                              // Call badge setup
  oledprint("Any BTN\nfor Menu");
  pause(1200);
  while(1)
  {
    clear();                                  // Display screen name
    text_size(LARGE);
    oledprint("%s", screenName);

    while(!buttons());                        // Wait for button press

    text_size(SMALL);                         // Menu
    clear();         
    oledprint("      MENU      ");
    oledprint("P17-Send        ");
    oledprint("     Receive-P27\n");
    oledprint("P15-Upload      ");
    oledprint("        Back-P25\n");
    oledprint("  Erase-OSH-All ");
    pause(250);
    
    while((states = buttons()) == 0);         // Wait for button press

    clear();                                  // Get ready to display operation
    text_size(LARGE);
    
    switch(states)                            // Handle button press
    {
      case 0b0100000:                         // P17 pressed, send IR
        clear;
        oledprint("Sending");
        rgbs(RED, RED);
        send(my); 
        rgbs(OFF, OFF);
        pause(50);
        continue;                             // Back to while(1)
      case 0b0000001:                         // P27 pressed
        break;                                // Skip to IR receive code
      case 0b0001000:
        clear();
        oledprint("Upload  ...");
        contacts_displayAll();
        oledprint("Done");
        pause(250);
        continue;                             // Back to while(1)
      case 0b1000000:                         // OSH pressed, erase EEPROM
        clear();
        oledprint("CONFIRM");
        pause(500);
        text_size(SMALL);
        cursor(0, 4);
        oledprint("Yes-OSH\n\n");
        oledprint("No-Any other btn");
        while(!(states = buttons()));         // Get confirmation
        if(states == 0b1000000)               // Yes, erase
        {
          text_size(LARGE);
          clear();
          oledprint("Wait 20s...");
          contacts_eraseAll();
          oledprint("Done!");
          pause(250);
        }          
        else                                   // No, don't erase
        {
          clear();
          pause(250);
        }   
        continue;                               // Back to while(1)  
      default:
        continue;                               // Back to while(1)
    }

    // P27 has to have been pressed to get to here
    clear();
    oledprint("IR Rcv");                      // Display ready for IR
    cursor(0, 7);
    text_size(SMALL);
    oledprint("        Back-P25");

    // Wait for IR message
    pause(250);
    irclear();                                // Clear the IR buffers
    while(1)
    {
      irlenb = receive(irbuf);
      if(irlenb > 0) break;
      states = buttons();
      if(states == 0b0000100)
      {
        led(0, OFF);
        break;
      }        
      led(0, ON);
      pause(150);
      led(0, OFF);
      pause(150);
    }
    if(states == 0b0000100) continue;
    clear();                                  // Menu, what to do with data
    oledprint(irbuf);
    cursor(0, 5);
    oledprint("       Store-P26");
    cursor(0, 6);
    oledprint("     Discard-P25");
    while((states = buttons()) == 0);         // Wait for button press
    text_size(LARGE);
    clear();
    if(states == 0b0000010)                   // If P26, store to EEPROM
    {
      if(!stored(irbuf)) store(irbuf);
      oledprint("Stored");
    }      
    if(states == 0b0000100)                   // if(P25), discard
    {
      oledprint("Discard");
    }  
    pause(500);    
  }
}  


