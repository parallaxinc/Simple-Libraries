/*
  Keypad 4x4 Read Simultaneous Keys.c
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

    while(key != -1)                          // Loop getting more pressed keys
    {
      key = keypad_readFrom(key);             // Use readFrom previous key
      if(key <= 9)                            // Process the same way as read
        print("key = %d\r", key);
      else
        print("key = %c\r", key);
    }    

    // Extra carriage return and delay for the terminal.        
    print("\r");
    pause(500);
  }  
}