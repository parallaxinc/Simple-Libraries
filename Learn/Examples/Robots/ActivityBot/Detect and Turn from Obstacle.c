/*
  Detect and Turn from Obstacle.c

  Detect obstacles in the ActivityBot's path, and turn a random direction to avoid them.

  http://learn.parallax.com/activitybot/roaming-ultrasound
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header

int turn;                                     // Navigation variable

int main()                                    // main function
{
  drive_setRampStep(10);                      // 10 ticks/sec / 20 ms

  drive_ramp(128, 128);                       // Forward 2 RPS

  // While disatance greater than or equal
  // to 20 cm, wait 5 ms & recheck.
  while(ping_cm(8) >= 20) pause(5);           // Wait until object in range

  drive_ramp(0, 0);                           // Then stop

  // Turn in a random direction
  turn = rand() % 2;                          // Random val, odd = 1, even = 0

  if(turn == 1)                               // If turn is odd
    drive_speed(64, -64);                     // rotate right
  else                                        // else (if turn is even)
    drive_speed(-64, 64);                     // rotate left

  // Keep turning while object is in view
  while(ping_cm(8) < 20);                     // Turn till object leaves view

  drive_ramp(0, 0);                           // Stop & let program end
}
