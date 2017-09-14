/*
   Store Retrieve Strings.c
   Store strings to and then retrieve them from EEPROM and display them 
   in the SimpleIDE Terminal.  REMEMBER to use the SimpleIDE's Run with
   Terminal button.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

//   badge        num   name
char fred[]   = {"123\n Fred\n"};
char wilma[]  = {"456\n Wilma\n"};
char barney[] = {"789\n Barney\n"};
char betty[]  = {"147\n Betty\n"};

char their[16];                              // String for retrieved strings

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  text_size(SMALL);    
  oledprint("Use SimpleIDE\nTerminal.");
  
  store(wilma);                              // Store two strings in EEPROM
  store(betty);
  
  contacts_displayAll();                     // Display all stored strings
}  
