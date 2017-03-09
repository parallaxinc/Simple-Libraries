/*
   Hello oLED Screen.c
   Displays “hello” message in Parallax eBadge oLED screen with
   oledprint function.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("Hello!");                       // hello -> badge screen
}


