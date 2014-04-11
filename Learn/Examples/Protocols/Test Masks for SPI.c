/*
  MMA7455 Test Z Axis with SPI.c
  
  Demonstrates creating bit masks and using them to set and clear bits in
  certain variables.  Useful in SPI when a particular bit in a variable
  has to be set or cleared for writing data to or reading data from the chip.

  http://learn.parallax.com/propeller-c-simple-protocols/bit-masks-better-code
*/

#include "simpletools.h"                          // Include simpletools header

const int MCTL  = 0x16;        // = 0b0100101     // Control register address
const int ZOUT8 = 0x08;        // = 0b0001000     // 8-bit z register address


const int writeMask  = 1 << 6;                    // Write mask for setting bit 6
const int readMask   = ~(1 << 6);                 // Read mask for clearing bit 6
                                                
signed char z;                                    // Z-axis

int cmd;                                          // Variable for storing command

int main()                                        // Main function
{
  print("MCTL      = %07b \n", MCTL);             // Display binary MCTL address
  print("writeMask = %07b (OR)\n", writeMask);    // Display binary writeMask

  cmd = MCTL | writeMask;                         // MCTL OR writeMask to cmd

  print("-------------------------\n");           // Draw line
  print("cmd       = %07b \n\n", cmd);            // Display cmd result
  print("ZOUT8     = %07b \n", ZOUT8);            // Display binary ZOUT address
  print("readMask  = %07b (AND)\n",               // Display binary readMask
        readMask & 0b1111111);                    // Bits 31...7 -> 0 for display

  cmd = ZOUT8 & readMask;                         // ZOUT8 AND readMask to cmd

  print("-------------------------\n");           // Draw line
  print("cmd       = %07b \n", cmd);              // Display cmd result
}