/*
  Arlo - Test Motor Connections.c

  Run this program to verify that your Arlo goes forward.
*/

#include "simpletools.h"                      // Include simple tools
#include "arlodrive.h"                        // Include arlo drive

char s[48];

int main()                                    // Main function
{
  freqout(4, 1000, 3000);                     // Beep -> program starting
  print("Program running...\n");              // Program running message
  drive_feedback(0);                          // Disable encoders
  drive_speed(20, 20);                        // 20/127 of full power to motors
  pause(3000);                                // Go for 3 seconds
  drive_speed(0, 0);                          // Stop
  print("Program done!\n");                   // Program done message
}
