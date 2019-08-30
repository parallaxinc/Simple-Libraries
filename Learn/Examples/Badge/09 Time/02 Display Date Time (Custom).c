/*
  Display Date Time (Custom).c
  Customizes the time display by oledprint-ing it in a different format 
  and adjusting values for 12 hour (instead of 24 hour) time.  Uses the
  dt type's elements: dt.y, dt.mo, dt.d, dt.h, dt.m, and dt.s.  They are
  all int values for convenient arithmetic adjustments.
*/  

#include "simpletools.h"                       // Include simpletools library
#include "badgetools.h"                        // Include badgetools library
#include "datetime.h"                          // Include datetime library

//             dt.y dt.mo dt.d dt.h dt.m dt.s
datetime dt = {2015,  10,  23,   8,  2, 44};  // Set up the date/time

void main()                                    // Main function
{
  badge_setup();                               // Start badge systems
  dt_run(dt);                                  // Start system timer with dt

  oledprint("Day/Time");                       // Display heading
  text_size(SMALL);                            // Change to small text
  
  while(1)                                     // Main loop
  {
    dt = dt_get();                             // Get system time
    int hrs = dt.h % 12;                       // Adjust to 12 hours
    if(dt.h == 0 || dt.h == 12) hrs = 12; 
    cursor(0, 5);                              // Position cursor row 5
    // Display time with formatting flags
    oledprint("   %04d.%02d.%02d\n\n  %02d:%02d:%02d  ",
    dt.y, dt.mo, dt.d, hrs, dt.m, dt.s);
    if(dt.h >= 12) oledprint("PM");            // Display AM/PM
    else oledprint("AM");
  }      
}  
