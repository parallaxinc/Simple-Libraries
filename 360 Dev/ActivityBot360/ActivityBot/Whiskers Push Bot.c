/*
  Whiskers Push Bot.c
  
  Push the whiskers to make the ActivityBot back up.
  
  http://learn.parallax.com/activitybot/whisker-wheel-response
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header

int main()                                    // main function
{
  freqout(4, 2000, 3000);                     // Speaker tone: 2 s, 3 kHz

  while(1)
  {
    // Check whisker states.
    int wL = input(7);                        // Left whisker -> wL variable
    int wR = input(8);                        // Right whisker -> wR variable

    // If whisker pressed, back up
    if((wL == 0) || (wR == 0))                // Either whisker detects
    {
      drive_speed(-64, -64);                  // Back up
    }
    else                                      // Neither whisker detects
    {
      drive_speed(0, 0);                      // Stay still
    }
  }
}
