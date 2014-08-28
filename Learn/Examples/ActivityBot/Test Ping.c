/*
  Test Ping.c

  Test the PING))) sensor before using it to navigate with the ActivityBot.

  http://learn.parallax.com/activitybot/build-and-test-ping-sensor-circuit
*/

#include "simpletools.h"                      // Include simpletools header
#include "ping.h"                             // Include ping header

int distance;                                 // Declare distance variable

int main()                                    // main function
{
  while(1)                                    // Repeat indefinitely
  {
    distance = ping_cm(8);                    // Get cm distance from Ping)))

    print("%c distance = %d%c cm",            // Display distance
           HOME, distance, CLREOL);           

    pause(200);                               // Wait 1/5 second
  }
}
