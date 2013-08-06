/*
  EEPROM Data.side

  Version 0.94 for use with SimpleIDE 9.40 and its Simple Libraries

  Write values and text to the Proepller Chip's dedicated EEPROM, and then
  read back and display.
  
  http://learn.parallax.com/propeller-c-tutorials
*/

#include "simpletools.h"                      // Include simpletools header    .

int main(void)                                // main function
{
  int addr = 64000;                           // Pick EEPROM base address. 

  ee_putInt(42, addr);                        // 42 -> EEPROM address 64000
  int eeVal = ee_getInt(addr);                // EEPROM address 64000 -> eeVal
  print("myVal = %d\n", eeVal);               // Display result

  ee_putStr("hello!\n", 7, addr + 4);         // hello!\n -> EEPROM 64004..64010
  char s[7];                                  // Character array to hold string
  ee_getStr(s, 7, addr + 4);                  // EEPROM 64004..64010 -> s[0]..s[5]
  print("s = %s", s);                         // Display s array
}

