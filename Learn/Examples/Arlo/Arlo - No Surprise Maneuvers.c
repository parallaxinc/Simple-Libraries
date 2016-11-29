/*
  Arlo - No Surprise Maneuvers.c

  Run this before ever turning on power to the Arlo's motors to prevent any
  unexpected motions.
*/

#include "simpletools.h"                      // Include simple tools
#include "arlodrive.h"                        // Include arlo drive

int main()                                    // Main function
{
  freqout(4, 2000, 3000);                     // Beep -> program starting
  print("Your Arlo will stay still\n");       // Success message
}
