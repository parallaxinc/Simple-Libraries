/*
  Display Date Time.c
  
  Creates a datetime type named dt with year, month, day, hour, minute, and
  second.  The dt_run function uses the dt values to set the current time, 
  and then starts counting seconds automatically.  The dt = dt_get() call
  copies the current time values to dt.  The dt_toDate/TimeStr functions
  create 8-character strings that work nicely with the badge display.
  
  NOTE: The custom datetime library is used in these examples because it
        takes less program space than the standard time.h + sys/time.h that's 
        built into Propeller GCC.
*/  

#include "simpletools.h"                       // Include simpletools library
#include "badgetools.h"                        // Include badgetools library
#include "datetime.h"                          // Include datetime library

//                y  mo   d  h   m   s
datetime dt = {2015, 10, 23, 8, 47, 40};       // Set up the date/time

char dates[9];                                 // Stores date string
char times[9];                                 // Stores time string

void main()                                    // Main function
{
  badge_setup();                               // Start badge systems
  dt_run(dt);                                  // Start system timer with dt

  while(1)                                     // Main loop
  {
    dt = dt_get();                             // Get current system time
    dt_toDateStr(dt, dates);                   // Convert to strings
    dt_toTimeStr(dt, times);
    cursor(0, 0);                              // Position cursor
    oledprint("%s%s", dates, times);           // Display date/time
    pause(100);                                // Wait .1 s before repeating
  }      
}  
