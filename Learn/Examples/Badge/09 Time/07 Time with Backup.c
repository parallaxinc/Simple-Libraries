/*
  Time with Backup.c
  
  This application displays time, but also saves it to EEPROM every minute.
  It boots from the most recently saved time, so if the badge gets restarted
  for some reason, the time will only need small adjustments to get it back
  to current.  Make sure to read the comments in Time Backup Setup.side for 
  some background on the EEPROM access approach.
  
  That a the datetime dt type is not initialized because the application
  reads the date and time from EEPROM as an epoch time value (seconds since
  Midnight, 1/1/1970).  It then converts to datetime with dt_fromEt(), and 
  that gets used to start the system timer with dt_run.  
  
  IMPORTANT: This will wear out the EEPROM after a few year's worth of 
  continuous use.  Updating EEPROM less frequently will extend its useful 
  life.
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
  badge_setup();                              // Start badge systems

  et = ee_readInt(60000);                     // Get most recent time
  dt = dt_fromEt(et);                         // Convert from epoch to datetime
  dt_run(dt);                                 // Use to start system timer
  
  while(1)                                    // Main loop
  {
    dt = dt_get();                             // Get current system time
    dt_toDateStr(dt, dates);                   // Convert to strings
    dt_toTimeStr(dt, times);
    cursor(0, 0);                              // Position cursor
    oledprint("%s%s", dates, times);           // Display date/time
    pause(100);                                // Wait .1 s before repeating
    if(dt.s == 0)                              // If next minute over
    {
      et = dt_toEt(dt);                        // Datetime -> epoch time
      ee_writeInt(et, 60000);                  // Store in EEPROM
      led(0, ON);                              // Indicate storing P27 LED
      while(dt.s == 0)                         // Wait for second 0 to finish
      {                                        // to avoid multiple EE writes
        dt = dt_get();                         // Check time
      }
      led(0, OFF);                             // Second over, P27 LED off
    }
  }      
}  
