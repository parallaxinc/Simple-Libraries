/*
   Send Data with IR.c
   This is the 'with structures' version of 02 Receive and Store IR Strings.side.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

typedef struct info_st                       // info container
{
  char name[16];
  char email[32];
} info;

info their;                                  // For storing incoming info

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
      int contacts = contacts_count();
      for(int record = 0; record < contacts; record++)
      {
        eescan(record, "%s%s", their.name, their.email);
        print("record %d = %s, %s\n", record, their.name, their.email);
      }        
      oledprint("Done");
      pause(700);
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
    memset(&their, 0, sizeof(their));        // Clear their variables
    while(1)
    {
      irscan("%s%s", their.name, their.email);
      if(strlen(their.name) > 0)
      {
        break;
      }        
    }
    
    clear();                                 // Menu, what to do with data
    text_size(SMALL);
    oledprint("%s, %s\n", their.name, their.email);
    cursor(0, 5);
    oledprint("       Store-P26");
    cursor(0, 6);
    oledprint("     Discard-P25");

    
    while((states = buttons()) == 0);        // Wait for button press

    text_size(LARGE);                        // Act on button press
    clear();
    if(states == 0b0000010)
    {
      exist = eeprinted("%16s\n%32s\n", their.name, their.email);
      print("exist = %d\n", exist);
      if(!exist) 
        eeprint("%16s\n%32s\n", their.name, their.email);
      oledprint("Stored");
    }      
    if(states == 0b0000100)
    {
      oledprint("Discard");
    }      
    pause(500);
  }
}  


