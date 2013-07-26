/*
  EEPROM Program Modes.side

  Use EEPROM to advance modes with each press/release of the reset button.
  Also advances with each power-off, power-on cycle. 
  
  http://learn.parallax.com/propeller-c-tutorials
*/

#include "simpletools.h"                      // Include simpletools header    .

int main(void)                                // Main function code starts here
{
  int addr = 65535;                           // Higest EEPROM address least used
  char mode = ee_get_byte(addr);              // Value at address 65535 -> mode
  mode += 1;                                  // Add one
  mode %= 3;                                  // Modulus (remainder of mode / 3)
  ee_put_byte(mode, addr);                    // New mode -> EEPROM addr 65535

  switch(mode)                                // Decide how the program behaves
  {
    case 0:                                   // If mode == 0, P26 light on
      high(26);
      break;
    case 1:                                   // If mode == 1, P27 light on
      high(27);
      break;
    case 2:
      high(26);                               // If mode == 2, both lights on
      high(27); 
      break;
  }

  while(1);                                   // Keep light(s) on
}
