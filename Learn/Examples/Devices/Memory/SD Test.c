/*
  SD Test.side
  SD file read and write basics.
*/

#include "simpletools.h"                      // Include simpletools header    .

int DO = 22, CLK = 23, DI = 24, CS = 25;      // SD card pins on Propeller BOE

int main(void)                                // Main function
{
  pause(1000);                                // Delay for terminal

  int erc = sd_mount(DO, CLK, DI, CS);        // Mount SD card
  if(!erc)                                    // Error code = 0, good, continue
  {
    FILE* fp = fopen("test.txt", "w");        // Open a file for writing
    
    if(fp)                                    // Nonzero file pointer?  
    {                                         // Good, continue
      fprintf(fp, "Test message, hello!\n");  // Add contents to the file
    }
    else                                      // Zero file pinter?
    {                                         // Bad, error message.
      printf("File did not open.\n");         
    }                                         
    fclose(fp);                               // Close the file
  
    fp = fopen("test.txt", "r");              // Reopen file for reading.
  
    char s[80];                               // Buffer for characters.
  
    if(fp)                                    // Nonzero file pinter?  
    {                                         // Good, continue.
    printf("First 21 chars in test.txt:\n");  // Display heading
    fread(s, 1, 21, fp);                      // Read 21 characters
    printf("%s", s);                          // Display them
    printf("\n");                             // With a newline at the end.
    }
    else                                      // Zero file pointer?
    {                                         // Bad, print error.
      printf("File did not open.\n");         
      printf("\n");
    }
    fclose(fp);                               // Close the file.
  }
  else                                        // Mount error code not zero?
  {                                           // Bad, display code
    printf("Error opening card.");
    printf("error code = %d\n", erc);
  }
}    
            
