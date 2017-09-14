/*
   Check One Button.c
   Displays the state of button 0, the button adjacent to the P27 label.
   The button function returns 1 if pressed, or 0 if not pressed.  The
   button(index) function also has 0 to 6 options.  0 to 5 are are the
   same as the LEDs, from top-right clockwise.  Button 6 is the OSH 
   button just below the screen.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int state27;

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    state27 = button(0);                     // Check button 0 (by P27)

    cursor(0, 0);                            // Cursor -> top-left
    oledprint("P27 = %d", state27);          // Display label, state

    if(state27 == 1)                         // If pressed
    {
      led(0, ON);                            // Adjacent light on
    }
    else                                     // If not pressed
    {
      led(0, OFF);                           // Adjacent light off
    }            
  }    
}


