/*
  EEPROM Data.side

  Write values and text to the Proepller Chip's dedicated EEPROM, and then
  read back and display.
  
  http://learn.parallax.com/propeller-c-simple-devices/eeprom-data
*/

#include "simpletools.h"                      // Include simpletools header    .

int main(void)                                // Main function code starts here
{
  pause(1000);                                // Wait 1 s for SimpleIDE Terminal
  int addr = 64000;                           // Pick EEPROM base address. 

  ee_put_int(42, addr);                       // 42 -> EEPROM address 64000
  int eeVal = ee_get_int(addr);               // EEPROM address 64000 -> eeVal
  print("myVal = %d\n", eeVal);               // Display result

  ee_put_str("hello!\n", 7, addr + 4);        // hello!\n -> EEPROM 64004..64010
  char s[7];                                  // Character array to hold string
  ee_get_str(s, 7, addr + 4);                 // EEPROM 64004..64010 -> s[0]..s[5]
  print("s = %s", s);                         // Display s array
}

