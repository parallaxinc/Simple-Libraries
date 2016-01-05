/*
  Receive Time with IR.c
  Receives and displays time from another badge.  This app only 
  receives and displays, so if you want to update the time here, send it
  a time from the badge running Send Time with IR.side.  Note that the 
  time came in as an epoch time (seconds since midnight 1/1/1970), so 
  it gets converted back to datetime format with dt = dt_fromEt(et).
*/  

#include "simpletools.h"                      // Include simpletools library
#include "badgetools.h"                       // Include badgetools library
#include "datetime.h"                         // Include datetime library

datetime dt;                                  // Date/teme values
int et;                                       // Epoch time value

char dates[9];                                // Date string
char times[9];                                // Time string

void main()                                   // Main function
{
  badge_setup();                              // Call badge setup
  oledprint("waiting for time");              // User prompt
  
  while(1)                                    // Main loop
  {
    irscan("%d", &et);                        // Check for incoming time
    if(et != 0)                               // Got one?
    {
      rgbs(BLUE, BLUE);                       // Receive signal
      pause(50);                             
      rgbs(OFF, OFF);
      dt = dt_fromEt(et);                     // Convert epoch time to datetime
      dt_toDateStr(dt, dates);                // Convert datetime to strings
      dt_toTimeStr(dt, times);
      cursor(0, 0);                           // Cursor -> col 0, row 0
      oledprint("%s%s", dates, times);        // Display date/time
      pause(100);                             // Wait .1 s
      et = 0;                                 // Clear et for next IR message
    }
  }
}              
      