/*
  SD for Text Files and Back to Variables.c
  
  Save variable values to a text file that can be viewed with Windows 
  Notepad and Apple TextEdit.  Retrieve those values and convert them from 
  text representation back to variables for use by the program.  This fixed 
  line width approach with sprint, fwrite, fread, and sscan is recommended 
  because the program size will not increase too much if float types are used
  in place of int.  
    
  http://learn.parallax.com/propeller-c-simple-devices/
*/

#include "simpletools.h"                      // Include simpletools header    

int DO = 22, CLK = 23, DI = 24, CS = 25;      // SD card pins on Propeller BOE

int val;                                      // Declare value variable
char s[32];                                   // 32 byte array for strings

int main(void)                                // main function
{
  sd_mount(DO, CLK, DI, CS);                  // Mount SD card

  FILE* fp = fopen("test.txt", "w");          // Open a file for writing
  
  // Store values as text in test.txt.
  for(int i = -5; i < 15; i++)                // Repeat 20x (-5...14)
  {
    memset(s, ' ', 30);                       // 30 spaces into string
    s[30] = '\r';                             // Newline for Windows Notepad
    s[31] = '\n';                             
    val = i * 10;                             // Emulate sensor reading
    sprint(s, "i = %d , val = %d ", i, val);  // Data to s array as characters
    fwrite(s, 1, 32, fp);                     // Write line to file
  }  
  
  fclose(fp);                                 // Close file
  
  // Retrieve values from file and store in 
  // variables for program use.
  fp = fopen("test.txt", "r");                // Reopen file for reading

  int idx;
  for(int i = -5; i < 15; i++)                // go back through
  {
    memset(s, '\0', 32);                      // All characters to zero
    fread(s, 1, 32, fp);                      // Read the string
    sscan(s, "i = %d , val = %d ", &idx, &val);  // String values -> variables
    print("idx = %d, val = %d \n", idx, val);    // Print variables
  }  

  fclose(fp);                                 // Close the file
}