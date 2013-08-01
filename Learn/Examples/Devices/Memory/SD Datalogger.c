/*
  SD Datalogger.side

  Application prompts you to type numbers into SimpleIDE Terminal, and
  records to SD.  Plays back all numbers after you type q and press Enter.
  
  http://learn.parallax.com/propeller-c-simple-devices/sd-card-data
*/

#include "simpletools.h"                      // Include simpletools header    .

int DO = 22, CLK = 23, DI = 24, CS = 25;      // SD card pins on Propeller BOE

int main(void)                                // main function
{
  print("Enter several values.\n\n");         // User instructions
  print("To see logged values, press\n");
  print("Enter a second time.\n\n");

  sd_mount(DO, CLK, DI, CS);                  // Mount SD card

  FILE* fp = fopen("test.txt", "w");          // Open a file for writing

  int n, status;                              // Number & status variables
  while(1)                                    // Endless loop
  {
    print("> ");                              // User prompt
    status = scan("%d", &n);                  // Get number & status
    if(!status) break;                        // Status 0? Break out of loop
    fwrite(&n, 4, 1, fp);                     // Write number to SD card
  } 
  fclose(fp);                                 // Close the file
  
  print("\nYou entered:\n");                  // List heading

  fp = fopen("test.txt", "r");                // Open a file for writing
  while(1)
  {
    status = fread(&n, 4, 1, fp);             // Read from SD & get status
    if(!status) break;                        // If no more, break loop
    print("n = %d\n", n);                     // Display value
  } 
  fclose(fp);                                 // Close the file
}    

