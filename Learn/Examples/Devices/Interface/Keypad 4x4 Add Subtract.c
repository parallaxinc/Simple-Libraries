/*
  Keypad 4x4 Add Subtract.c
  Keypad addition and subtraction using the A button for add, and the B button
  for subtract.  

  IMPORTANT: In the values array, the 'A' key was reassigned the value '+', 
  the B key was reassigned '-', and the '#' key was reassigned '='.
*/  

#include "simpletools.h"                      // Libraries simpletools & keypad
#include "keypad.h"

int key, x, y, z, op;                         // Application variables
    
int rows[4] = {7, 6, 5, 4};                   // Row I/O pins (top to bottom)
int cols[4] = {3, 2, 1, 0};                   // Column I/O pins (left to right)

int values[16] = {  1,   2,    3,  '+',       // Values for each key in the 4x4
                    4,   5,    6,  '-',       // Note that A is now +, B is now
                    7,   8,    9,  'C',       // -, nad # is now =
                  '*',   0,  '=',  'D' };

int main()                                    // Main function
{
  keypad_setup(4, 4, rows, cols, values);     // Setup dimensions, keypad arrays
  
  while(1)                                    // Main loop
  {
    print("Type number, (A or B), ");         // User prompt
    print("number #\r");
    
    x = keypad_getNumber();                   // First keypad number -> x

    op = keypad_getNumberEndKey();            // Get operator that ended number

    y = keypad_getNumber();                   // Second keypad number -> x
    
    switch(op)                                // Operation based on op var
    {
      case '+':                               // if +, add
      {
        z = x + y;
        break;
      }
      case '-':                               // if -, subtract
      {        
        z = x - y;
        break;
      }
    }      
    print("%d\r", z);                         // Display the result
  }    
}
