/*
  SD Minimal.side

  Create test.txt, write characters in, read back out, display. 
  
  http://learn.parallax.com/propeller-c-simple-devices/sd-card-data
*/

#include "simpletools.h"                      // Include simpletools header    

int DO = 22, CLK = 23, DI = 24, CS = 25;      // SD card pins on Propeller BOE

int main(void)                                // main function
{
  sd_mount(DO, CLK, DI, CS);                  // Mount SD card

  FILE* fp = fopen("test.txt", "w");          // Open a file for writing
  fwrite("Testing 123...\n", 1, 15, fp);      // Add contents to the file
  fclose(fp);                                 // Close the file
  
  char s[15];                                 // Buffer for characters
  fp = fopen("test.txt", "r");                // Reopen file for reading
  fread(s, 1, 15, fp);                        // Read 15 characters
  fclose(fp);                                 // Close the file

  print("First 15 chars in test.txt:\n");     // Display heading
  print("%s", s);                             // Display characters
  print("\n");                                // With a newline at the end
}    

