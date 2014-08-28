/*
  Test Whiskers with LEDs.c
 
  Display whisker states in terminal.  1 = not pressed, 0 = pressed.

  http://learn.parallax.com/activitybot/add-whisker-indicator-lights
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // main function
{
  freqout(4, 2000, 3000);                     // Speaker tone: P4, 2 s, 3 kHz
  while(1)                                    // Endless loop
  {
    int wL = input(7);                        // Left whisker -> wL variable
    int wR = input(8);                        // Right whisker -> wR variable
    if(wL == 0) high(26); else low(26);       // Light for left whisker
    if(wR == 0) high(27); else low(27);       // Light for right whisker
    print("%c", HOME);                        // Terminal cursor home (top-left)
    print("wL = %d  wR = %d", wL, wR);        // Display whisker variables
    pause(50);                                // Pause 50 ms before repeat
  }
}
