/*
  AB Interpreter.c

  Fetches text commands from file on SD card, interprets them,
  and executes maneuvers. Requires abdrive 0.5.5 from
  ActivityBot library 2013-10-31 or later.

  http://learn.parallax.com/activitybot/text-file-maneuver-list
*/

#include "simpletools.h"                     // Library includes
#include "abdrive.h"  

FILE *fp;                                    // File pointer for SD
char str[512];                               // File buffer

char cmdbuf[10];                             // Command buffer
char valbuf[4];                              // Text value buffer
int  val;                                    // Value

int main()                                   // Main function
{
  int DO = 22, CLK = 23;                     // SD I/O pins
  int DI = 24, CS = 25;
  sd_mount(DO, CLK, DI, CS);                 // Mount SD file system
  fp = fopen("navset.txt", "r");             // Open navset.txt

  fread(str, 1, 512, fp);                    // navset.txt -> str 
  int strLength = strlen(str);               // Count chars in str
  int i = 0;                                 // Declare index variable

  drive_speed(0, 0);                         // Speed starts at 0

  while(1)                                   // Loop through commands
  {
    // Parse command
    while(!isalpha(str[i])) i++;             // Find 1st command char
    sscan(&str[i], "%s", cmdbuf);            // Command -> buffer
    i += strlen(cmdbuf);                     // Idx up by command char count
    if(!strcmp(cmdbuf, "end")) break;        // If command is end, break

    // Parse distance argument
    while(!isdigit(str[i])) i++;             // Find 1st digit after command
    sscan(&str[i], "%s", valbuf);            // Value -> buffer
    i += strlen(valbuf);                     // Idx up by value char count
    val = atoi(valbuf);                      // Convert string to value

    // Execute command
    if(strcmp(cmdbuf, "forward") == 0)       // If forward
      drive_goto(val, val);                  // ...go forward by val
    else if(strcmp(cmdbuf, "backward") == 0) // If backward
      drive_goto(-val, -val);                // ... go backward by val
    else if(strcmp(cmdbuf, "left") == 0)     // If left
      drive_goto(-val, val);                 // ...go left by val
    else if(strcmp(cmdbuf, "right") == 0)    // If right
      drive_goto(val, -val);                 // ... go right by val
  }
  
  fclose(fp);                                // Close SD file
}