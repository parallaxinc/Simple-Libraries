/*
   View First and Last 64 Bytes with Terminal.c
   You'll be using SimpleIDE Terminal for this one, so make sure to click
   the Run with Terminal button to load the program.  (That holds for all
   the EEPROM activities.)  After erasure, the values are set to 255, which
   is hexadecimal 0xFF.  The dev_ee_show function displays EEPRM byte values.
   Values that are not standard character codes are displayed as hexadecimal
   values. 
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  
  text_size(SMALL);                          // Use SimpleIDE Terminal prompt
  oledprint("Use SimpleIDE\n");
  oledprint("Run w Terminal\n");
  oledprint("button.\n\n");
  oledprint("View data with\n");
  oledprint("SimpleIDE Term.");
  
  print("EEOPROM addresses 32768 to 32831\n");  // Display the memory
  dev_ee_show(64, 32768);                       // This function does the work
  print("\n\n");                                // Repeat for 2nd range
  print("EEOPROM addresses 65472 to 65535\n");
  dev_ee_show(64, 65535 - 64);
}


