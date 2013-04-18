/*
  SD Minimal.side

  Create test.txt, write characters in, read back out, display. 
  
  http://learn.parallax.com/C/Simple-Devices-Propeller-C/sd-card-data
*/

#include "simpletools.h"                      // Include simpletools header    .

int DO = 22, CLK = 23, DI = 24, CS = 25;      // SD card pins on Propeller BOE

int main(void)                                // Main function
{
  pause(1000);                                // Delay for terminal

  sd_mount(DO, CLK, DI, CS);                  // Mount SD card

  FILE* fp = fopen("test.txt", "w");          // Open a file for writing
  fprintf(fp, "Testing 123...\n");            // Add contents to the file
  fclose(fp);                                 // Close the file
  
  char s[15];                                 // Buffer for characters.
  fp = fopen("test.txt", "r");                // Reopen file for reading.
  fread(s, 1, 15, fp);                        // Read 21 characters
  fclose(fp);                                 // Close the file.

  printf("First 21 chars in test.txt:\n");    // Display heading
  printf("%s", s);                            // Display characters
  printf("\n");                               // With a newline at the end.
}    

