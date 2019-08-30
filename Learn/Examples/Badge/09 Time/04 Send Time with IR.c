/*
  Send Time with IR.c
  Displays time and sends to another device with the press of P17.  Make
  sure other badge uses Receive Time with IR.side.  Note et = dt_toEt().
  That gets the epoch time value for the values currently stored in dt.
  Epoch time is the number of seconds since midnight, 1/1/1970.  This is 
  in Unix operating systems.  The 32 bit int value that the system timer 
  uses to actually count time, and it also takes fewer characters to 
  represent than a time strings for transmitting over IR.
*/  

#include "simpletools.h"                       // Include simpletools library
#include "badgetools.h"                        // Include badgetools library
#include "datetime.h"                          // Include datetime library

datetime dt = {2015, 10, 23, 9, 36, 27};       // Set up the date/time

char dates[9];                                 // Stores date string
char times[9];                                 // Stores time string

void main()                                    // Main function
{
  badge_setup();                               // Start badge systems
  dt_run(dt);                                  // Start system timer with dt

  oledprint("IR Snd T");                       // Display heading
  text_size(SMALL);                            // Text size -> small
  cursor(0, 4);                                // Cursor -> col 0, row 4
  oledprint("<- P17 to send");                 // User prompt
  
  while(1)                                     // Main loop
  {
    dt = dt_get();                             // Get current system time
    dt_toDateStr(dt, dates);                   // Convert to strings
    dt_toTimeStr(dt, times);
    cursor(4, 6);                              // Cursor -> col 4, row 6
    oledprint("%s", dates);                    // Display date string
    cursor(4, 7);                              // Cursor -> col 4, row 7
    oledprint("%s", times);                    // Display time string

    int states = buttons();                    // Check buttons
    if(states & 0b0100000)                     // If P17 pressed
    {
      int et = dt_toEt(dt);                    // Get epoch time from dt
      rgbs(RED, RED);                          // Signal transmitting
      irprint("%d", et);                       // Transmit epoch time
      rgbs(OFF, OFF);                          // Finish transmitting
      pause(600);                              // Wait .6 s for btn release
    }

    pause(100);                                // 0.1 seconds before repeat
  }      
}  
