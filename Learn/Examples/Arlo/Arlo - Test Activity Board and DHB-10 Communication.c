/*
  Arlo - Test Activity Board and DHB-10 Communication.c

  Run this program to verify that your Activity Board and DHB-10 are communicating.

  Should display:
       Hardware
         HWVER = 1
       Firmware
         VER = 10

  If it instead displays:
      "ERROR, no reply from DHB..."
  It means there is a wiring problem.
*/

#include "simpletools.h"                      // Include simple tools
#include "arlodrive.h"                        // Include arlo drive

char *s;

int main()                                    // Main function
{
  freqout(4, 2000, 3000);                     // Beep -> program starting
  print("Program running...\n");              // Program running msg
  s = dhb10_com("HWVER\r");                // Request hardware version
  print("Hardware\n  HWVER = %s", s);         // Display reply
  s = dhb10_com("VER\r");                  // Request firmware version
  print("Firmware\n  VER = %s", s);           // Display reply
}
