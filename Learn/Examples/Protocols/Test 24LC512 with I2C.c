/*
  Test 24LC512 with I2C.c

  Test writes data to I2C EEPROM, then reads it back and displays it.   

  http://learn.parallax.com/propeller-c-simple-protocols/i2c-diy
*/

#include "simpletools.h"                      // Include simpletools header

i2c *eeBus;                                   // I2C bus ID

int main()                                    // Main function
{
  eeBus = i2c_newbus(28,  29,   0);           // Set up I2C bus, get bus ID

                                              // Use eeBus to write to device
  i2c_out(eeBus, 0b1010000,                   // with I2C address 0b1010000,
          32768, 2, "abcdefg", 8);            // send 2 byte command of 32768
                                              // and 8 byte data string.

  while(i2c_busy(eeBus, 0b1010000));          // Wait for EEPROM to finish
  
  char testStr[] = {0, 0, 0, 0, 0, 0, 0, 0};  // Set up test string
     
                                              // Use eeBus to read from device
  i2c_in(eeBus, 0b1010000,                    // with I2C address 0b1010000,   
         32768, 2, testStr, 8);               // send 2 byte command of 32768
                                              // & store data in 8 byte array.

  print("testStr = %s \n", testStr);          // Display result
}
