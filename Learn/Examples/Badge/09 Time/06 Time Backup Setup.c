/*
  Time Backup Setup.c
  
  This sets up the badge for the next app by writing the system time as an
  epoch time value (seconds since midnight, 1/1/1970) to EEPROM address
  60000.  This area is the least likely to interfere with the eeprint/scan
  and store/retrieve functions, which build from 32768 upward with data, and
  from 65535 downward with an int for each record.  
  
  The Time with backup application will load the time from address 60000 and
  update that time in EEPROM every minute to help in the event of power loss
  or reset.  Note that we don't actually need to start the system timer for
  this with dt_run.  Just create a datetime value, convert to epoch time, and 
  save in EEPROM.  
  
  IMPORTANT: The badgetools ee_writeInt function sets a lock while it 
  communicates with the EEPROM bus.  This forces any other cogs to take 
  turns communicating with EEPROM (or the accelerometer which is on the 
  same bus).  The simpletools ee_putInt function does not set the lock, so
  if your Parallax eBadge app needs to access specific EEPROM addresses, 
  make sure to use ee_write* and ee_read* functions with the badge.
   
*/  

#include "simpletools.h"                       // Include simpletools library
#include "badgetools.h"                        // Include badgetools library
#include "datetime.h"                          // Include datetime library

datetime dt = {2015,  10,  23,   9,  58, 52};  // Set up the date/time

void main()                                    // Main function
{
  badge_setup();                               // Start badge systems

  int et = dt_toEt(dt);                        // Epoch time from datetime
  ee_writeInt(et, 60000);                      // Store epoch time in EEPROM
  
  oledprint("Done RunProgram7");               // Display done
}  
