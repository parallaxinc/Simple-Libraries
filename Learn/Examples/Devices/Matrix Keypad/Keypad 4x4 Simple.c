/*
  Keypad 4x4 Read Multiple Keys.c
  Demonstrates how to read individual key presses 
  with the keypad library.  
*/  

#include "simpletools.h"
#include "keypad.h"

// Row connections listed from top to bottom.
int rows[4] = {7,   6,  5,  4};

// Column connections listed from left to right.
int cols[4] = {3,   2,  1,  0};

// List values for each key to return.
int values[16] = {  1,   2,    3,  'A',
                    4,   5,    6,  'B',
                    7,   8,    9,  'C',
                  '*',   0,  '#',  'D' };

int main()
{
  // Parameters are # rows, # columns, rows array
  // columns array, and values array.
  keypad_setup(4, 4, rows, cols, values);
  
  while(1)
  {
    // Check for button press.  Returns button value 
    // or -1 if none pressed
    int key = keypad_read();
    // Display key value returned.
    if(key <= 9)
      print("key = %d\r", key);
    else
      print("key = %c\r", key);
    pause(1500);
  }  
}