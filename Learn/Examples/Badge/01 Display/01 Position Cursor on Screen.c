/*
   Position Cursor on Screen.c
   Positions cursor on screen with cursor function.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("Hello,");                       // First message
  cursor(2, 1);                              // Move cursor to col 2, row 1
  oledprint("again!");                       // Next message starts there
}


