/*
  Keypad 4x4 Read Keys.c
  Demonstrates how to read individual key presses with the keypad library.  
*/  

#include "simpletools.h"                      // Libraries simpletools & keypad
#include "keypad.h"

int rows[4] = {7, 6, 5, 4};                   // Row I/O pins (top to bottom)
int cols[4] = {3, 2, 1, 0};                   // Column I/O pins (left to right)

int values[16] = {  1,   2,    3,  'A',       // Values for each key in the 4x4
                    4,   5,    6,  'B',
                    7,   8,    9,  'C',
                  '*',   0,  '#',  'D' };

int main()                                    // Main function
{
  keypad_setup(4, 4, rows, cols, values);     // Setup dimensions, keypad arrays
 
  while(1)                                    // Main loop
  {
    int key = keypad_read();                  // Get pressed key (or -1 for none)
    
    if(key <= 9)                              // Display key value
      print("key = %d\r", key);               // If <= 9, dispaly as decimal
    else
      print("key = %c\r", key);               // Otherwise, display as character
    pause(500);                               // Wait 0.5 s before repeat
  }  
}