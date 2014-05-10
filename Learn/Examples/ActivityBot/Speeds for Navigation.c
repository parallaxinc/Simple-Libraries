/* 
  Speeds for Navigation.c

  http://learn.parallax.com/activitybot
*/


#include "simpletools.h"                      // simpletools library
#include "abdrive.h"                          // abdrive library

int main()                   
{
  drive_speed(64, 64);                       // Forward 64 tps for 2 s
  pause(2000);
  drive_speed(0, 0);

  drive_speed(26, 0);                        // Turn 26 tps for 1 s
  pause(1000);
  drive_speed(0, 0);

  drive_speed(128, 128);                     // Forward 128 tps for 1 s
  pause(1000);
  drive_speed(0, 0);
}