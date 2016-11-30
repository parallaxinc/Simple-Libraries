/* 
  Arlo - Speeds for Navigation.c
  
  Navigate by making your ActivityBot go certain speeds for certain amounts
  of time.

  http://learn.parallax.com/activitybot/set-certain-speeds
*/


#include "simpletools.h"                      // simpletools library

#include "arlodrive.h"                        // <- CHANGE abdrive to arlodrive

int main()                   
{
  drive_speed(64, 64);                        // Forward 64 tps for 2 s
  pause(2000);
  drive_speed(0, 0);

  drive_speed(26, 0);                         // Turn 26 tps for 1 s
  pause(1000);
  drive_speed(0, 0);

  drive_speed(128, 128);                      // Forward 128 tps for 1 s
  pause(1000);
  drive_speed(0, 0);
}