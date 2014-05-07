/*
  SD with Tests.side

  SD Minimal modified so that it tests for drive and file before performing
  any read/write operations.  
  
  http://learn.parallax.com/propeller-c-simple-devices/sd-card-data
*/

#include "simpletools.h"                            // Include simpletools header     

int DO = 22, CLK = 23, DI = 24, CS = 25;            // SD card pins on Activity Board

int main(void)                                      // main function
{
  int erc = sd_mount(DO, CLK, DI, CS);              // Mount SD card
  if(!erc)                                          // Error code = 0, good, continue
  {
    FILE* fp = fopen("test.txt", "w");              // Open a file for writing
    
    if(fp)                                          // Nonzero file pointer?  
    {                                               // Good, continue
      fwrite("Test message, hello!\n", 1, 21, fp);  // Add contents to the file
    }
    else                                            // Zero file pinter?
    {                                               // Bad, error message.
      print("File did not open.\n");         
    }                                         
    fclose(fp);                                     // Close the file
  
    fp = fopen("test.txt", "r");                    // Reopen file for reading.
  
    char s[80];                                     // Buffer for characters.
  
    if(fp)                                          // Nonzero file pinter?  
    {                                               // Good, continue.
      print("First 21 chars in test.txt:\n");       // Display heading
      fread(s, 1, 21, fp);                          // Read 21 characters
      print("%s", s);                               // Display them
      print("\n");                                  // With a newline at the end.
    }
    else                                            // Zero file pointer?
    {                                               // Bad, print error.
      print("File did not open.\n");         
      print("\n");
    }
    fclose(fp);                                     // Close the file.
  }
  else                                              // Mount error code not zero?
  {                                                 // Bad, display code
    print("Error opening card.");
    print("error code = %d\n", erc);
  }
}    
            
