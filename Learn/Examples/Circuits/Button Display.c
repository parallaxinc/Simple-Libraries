/*
  Button Display.c
  
  Dislays the state of the P3 button in the SimpleIDE Terminal.
  1 -> button pressed, 0 -> button not pressed.
  
  http://learn.parallax.com/propeller-c-simple-circuits/check-pushbuttons
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  while(1)                                    // Endless loop
  {
    int button = input(3);                    // P3 input -> button variable
    print("button = %d\n", button);           // Display button state
    pause(100);                               // Wait 0.1 second before repeat
  }
}
