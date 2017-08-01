/*
  Keypad 4x4 Countdown Timer.c
  Builds a number with multiple key presses, then counts down to zero from that
  number.  
*/  

#include "simpletools.h"                      // Libraries simpletools & keypad
#include "keypad.h"

int countdown(int t);                         // Function prototypes
int getNumber(void); 

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
    print("Type number of seconds, ");        // User prompt
    print("then press #.\r");   
    
    int number = keypad_getNumber();          // Get number from keypad
    
    int result = countdown(number);           // Start the countdown
    
    if(result == 0)                           // If counted down to 0
    {
      print("Countdown complete!\r");         // ...display success
    }        
    else                                      // If not
    {
      print("Countdown terminated");          // ...display terminated
      print(" at %d seconds.\r", result);
      while(keypad_read() != -1);             // Wait for key release
    }              
  }    
}

int countdown(int t)                          // t = countdown time in s
{
  int key;                                    // keypad reading variable
  
  do
  {                                           // before starting countdown
    key = keypad_read();
  }
  while(key != -1);                           // Wait for key to be released         

  while(1)                                    // Keep counting down until 0
  {
    print("t = %d\r", t);                     // Display seconds
    if(keypad_read() != -1) break; 
    if(t == 0) break;                         // t == 0 exits loop
    pause(1000);                              // Delay 1 s
    t--;                                      // Subtract 1 from seconds
  }
  
  return t;                                   // After loop, return the result
}

