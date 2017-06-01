/*
  Keypad 4x4 Read Multiple Keys.c
  Demonstrates how to read keys when more than one might be
  pressed.  
  
  Caution, 2 keys is always correct, but 3 keys is not 
  always dependable.  Many combinations of up to 4 keys work
  fine, but certain combinations can result in ghosting on 
  keypads that do not have built-in diodes to prevent that.  
  
  Ghosting happens when two keys on the same row are pressed 
  and a third key on the same column with one the first two is
  pressed.  For example, pressing 1, 2, and 7 will result in
  1, 2, 7, and 8 being returned  
*/  

#include "simpletools.h"
// This keypad library is generic, so it requires
// some configuration to tell it you have a
// 4x4 and which pins it's connected to.
#include "keypad.h"

// Always list row connections from top to bottom.
int rows[4] = {7,   6,  5,  4};

// Always list column connections from left to right
int cols[4] = {3,   2,  1,  0};

// List the values you want the keypad library to
// return when a given keyp is pressed.  This should
// match the layout of the keypad.  You could optionally
// substitute 10 for A, 11 for B, etc.
int values[16] = {  1,   2,    3,  'A',
                    4,   5,    6,  'B',
                    7,   8,    9,  'C',
                  '*',   0,  '#',  'D' };

int main()
{
  // Call keypad setup passing these parameters:
  // number of rows, number of columns, pointer to
  // the rows array, pointer to the cols array,
  // pointer to the values array.
  keypad_setup(4, 4, rows, cols, values);
  
  while(1)
  {
    // Call keypad read.  Returns the first key that
    // it finds to be pressed.
    int key = keypad_read();
    // If you have a mixture of values and ASCII,
    // make sure to make the distinction.  If you end up
    // changing 'A' to 10, 'B' to 11, and so on, make sure
    // to change if(key <= 9) to if(key <= 13).
    if(key <= 9)
      print("key = %d\r", key);
    else
      print("key = %c\r", key);
    // The code can use keypad_readFrom to continue
    // reading from where it left off.  Since the key
    // variable contains the most recently read value, 
    // keypad_readFrom(key) makes the scan resume from
    // where it left off at the previous key in the scan.
    // This process can be repeated as long as
    // keypad_readFrom does not return -1 (meaning that it
    // ran out of keys to check without finding a pressed
    // one.
    while(key != -1)
    {
      key = keypad_readFrom(key);
      if(key <= 9)
        print("key = %d\r", key);
      else
        print("key = %c\r", key);
    }    

    // Extra carriage return and delay for the terminal.        
    print("\r");
    pause(1500);
  }  
}