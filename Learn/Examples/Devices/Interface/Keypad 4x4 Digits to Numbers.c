/*
  Keypad 4x4 Digits to Numbers.c
  Demonstrates how to build numbers with multiple key presses.  
*/  

#include "simpletools.h"                      // Libraries simpletools & keypad
#include "keypad.h"

int rows[4] = {7, 6, 5, 4};                   // Row I/O pins (top to bottom)
int cols[4] = {3, 2, 1, 0};                   // Column I/O pins (left to right)

int values[16] = {  1,   2,    3,  'A',       // Values for each key in the 4x4
                    4,   5,    6,  'B',
                    7,   8,    9,  'C',
                  '*',   0,  '#',  'D' };
                  
int number = 0;                               // Stores number result

int main()                                    // Main function
{
  keypad_setup(4, 4, rows, cols, values);     // Setup dimensions, keypad arrays
  
  print("Type a number, then press #\r");     // User prompt
 
  while(1)                                    // Main loop
  {
    number = keypad_getNumber();              // Get number entered on keypad
    
    print("\r");                              // Next line
    print("You entered %d\r", number);        // Display result
  }  
}

