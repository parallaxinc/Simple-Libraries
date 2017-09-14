/*
   Erase Badge EEPROM.c
   The contacts_eraseAll function erases all data from EEPROM addresses
   32768..65535.  The process takes about 20 s.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup

  oledprint("P17 to  ERASE");                // User prompt
  
  while(1)                                   // Main loop
  {
    if(button(5))                            // If P17 button pressed
    {
      clear();                               // Clear display
      oledprint("Erasing Wait 20s");         // Message to user
      contacts_eraseAll();                   // Erase 
      clear();                               // Display done
      oledprint("Done!");
    }
  }    
}


