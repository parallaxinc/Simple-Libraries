/*
  Display Button.c
  
  Dislays the state of the P3 button in the SimpleIDE Terminal.
  1 -> button pressed, 0 -> button not pressed.
  
  http://learn.parallax.com/C/Simple-Circuits-Propeller-C/Check-Pushbuttons
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  while(1)                                    // Endless loop
  {
    int button = input(3);                    // P3 input -> button variable
    for(int i = 0; i < 10; i++)
    printf("button = %d\n", button);          // Display button state
    pause(100);                               // Wait 0.1 second before repeat
  }
}
