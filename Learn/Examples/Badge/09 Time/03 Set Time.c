/*
  Set Time.c
  Example of using the buttons to set the time.  
*/  

#include "simpletools.h"                       // Include simpletools library
#include "badgetools.h"                        // Include badgetools library
#include "datetime.h"                          // Include datetime library

datetime dt = {2015, 10, 23, 9, 12, 7};        // Set up the date/time

char dates[9];                                 // Stores date string
char times[9];                                 // Stores time string

// Forward declare functions for setting date/time with the badge's buttons.
void setYear(void);                            
void setMonth(void);
void setDay(void);
void setHour(void);
void setMinute(void);
void setSecond(void);
void menu(void);
void submenu(void);

void main()                                    // Main function
{
  badge_setup();                               // Start badge systems
  dt_run(dt);                                  // Start system timer with dt

  oledprint(" OSH to   SET   ");               // Message how to set w/ OSH
  pause(2000);   
  
  while(1)                                     // Main loop
  {
    dt = dt_get();                             // Get system time
    dt_toDateStr(dt, dates);                   // Convert to strings
    dt_toTimeStr(dt, times);
    cursor(0, 0);                              // Position cursor
    oledprint("%s%s", dates, times);           // Display date/time
    pause(100);                                // Wait .1 s before repeating                 
     
    if(button(6) == 1)                         // If OSH pressed...
    {
      menu();                                  // Display menu
      pause(1000);                             // 1 s to let go of button
      int states = 0;                          // States variable
      while(states == 0)                       // Wait for button press
      {
        states = buttons();                    // Keep checking
      }        
      states = 0;                              // Clear the states
      while(states != 0b1000000)
      {
        states = buttons();                    // Check buttons
        switch(states)                         // Handle each case
        {
          case 0b0100000:                      // P17 set year
            print("year\n");
            setYear();
            break;
          case 0b0010000:                      // P16 set month
            setMonth();
            break;
          case 0b0001000:                      // P15 set day
            setDay();
            break;
          case 0b0000100:                      // P25 set hour
            setHour();
            break;
          case 0b0000010:                      // P26 set minute
            setMinute();
            break;
          case 0b0000001:                      // P27 set second
            setSecond();
            break;
          case 0b1000000:                      // OSH save and exit
            dt_set(dt);
            break;
        }     
      }        
    } 
  }      
}  


void menu(void)                                // Display buttons menu
{
  clear();
  text_size(SMALL);
  cursor(0, 0);
  oledprint("P17-Yr");
  cursor(0, 3);
  oledprint("P16-Mon");
  cursor(0, 6);
  oledprint("P15-Day");
  cursor(10, 6);
  oledprint("P25-Hr");
  cursor(9, 3);
  oledprint("P26-Min");
  cursor(9, 0);
  oledprint("P17-Sec");
  cursor(4, 7);
  oledprint("OSH-Done");
  text_size(LARGE);
}  

void submenu(void)                             // Display time set menu
{
  text_size(SMALL);
  cursor(9, 0);
  oledprint("P27-UP");
  cursor(12, 3);
  oledprint("P26");
  cursor(11, 4);
  oledprint("NEXT");
  cursor(9, 7);
  oledprint("P25-DN");
  text_size(LARGE);
}  

void setYear(void)                             // Year setting function
{
  clear();                                     // Clear display
  oledprint("YEAR");                           // Display year
  submenu();                                   // Display button submenu

  int y = dt.y;                                // Temp copy of dt.y to y

  cursor(0, 1);                                // Cursor -> row 0, col 1
  oledprint("%d", y);                          // Display current year
  pause(1000);                                 // 1 s for letting go of 
                                               // previous button
  while(1)                                     // Setting loop
  {
    int states = buttons();                    // Check buttons
    if(states == 0b0000001)                    // If P27
    {
      y++;                                     // Add 1 to year
    }
    else if(states == 0b0000100)               // If P25
    {
      y--;                                     // Subtract 1 from year
    }
    else if(states == 0b0000010)               // If P26
    {
      dt.y = y;                                // Copy y back to dt.y
      break;                                   // Break from while loop
    }
    text_size(LARGE);                          // Back to large text
    cursor(0, 1);                              // Cursor at bottom-left
    oledprint("%d", y);                        // Update year display
    pause(100);                                // Wait .1 s
  }
  menu();                                      // Back to menu
  return;                                      // Return from function
}

void setMonth(void)                             // Similar to setYear
{                                               // See setYear for comments
  clear();
  text_size(LARGE);
  oledprint("MON");
  submenu();

  int mo = dt.mo;

  cursor(0, 1);    
  oledprint("%02d", mo);
  pause(1000);
  while(1)
  {
    int states = buttons();
    if(states == 0b0000001)
    {
      mo++;
      if(mo > 12) mo = 1;
    }
    else if(states == 0b0000100)
    {
      mo--;
      if(mo < 1) mo = 12;
    }
    else if(states == 0b0000010)
    {
      dt.mo = mo;
      break;
    }
    text_size(LARGE);
    cursor(0, 1);
    oledprint("%02d", mo);
    pause(100);
  }
  menu();
  return;
}  

void setDay(void)                               // Similar to setYear
{                                               // See setYear for comments
  clear();
  text_size(LARGE);
  cursor(0, 0);
  oledprint("DAY");
  submenu();

  int d = dt.d;

  cursor(0, 1);
  oledprint("%02d", d);
  while(1)
  {
    int states = buttons();
    if(states == 0b0000001)
    {
      d++;
      if(d > 31) d = 1;
    }
    else if(states == 0b0000100)
    {
      d--;
      if(d < 1) d = 31;
    }
    else if(states == 0b0000010)
    {
      dt.d = d;
      break;
    }
    text_size(LARGE);
    cursor(0, 1);
    oledprint("%02d", d);
    pause(100);
  }
  menu();
  return;
}  

void setHour(void)                              // Similar to setYear
{                                               // See setYear for comments
  clear();
  text_size(LARGE);
  oledprint("HOUR");
  submenu();

  int h = dt.h;

  cursor(0, 1);    
  oledprint("%02d", h);
  pause(1000);
  while(1)
  {
    int states = buttons();
    if(states == 0b0000001)
    {
      h++;
      if(h > 23) h = 0;
    }
    else if(states == 0b0000100)
    {
      h--;
      if(h < 0) h = 23;
    }
    else if(states == 0b0000010)
    {
      dt.h = h;
      break;
    }
    text_size(LARGE);
    cursor(0, 1);
    oledprint("%02d", h);
    pause(100);
  }
  menu();
  return;
}  

void setMinute(void)                            // Similar to setYear
{                                               // See setYear for comments
  clear();
  text_size(LARGE);
  oledprint("MIN");
  submenu();

  int m = dt.m;

  cursor(0, 1);    
  oledprint("%02d", m);
  pause(1000);
  while(1)
  {
    int states = buttons();
    if(states == 0b0000001)
    {
      m++;
      if(m > 59) m = 0;
    }
    else if(states == 0b0000100)
    {
      m--;
      if(m < 0) m = 59;
    }
    else if(states == 0b0000010)
    {
      dt.m = m;
      break;
    }
    text_size(LARGE);
    cursor(0, 1);
    oledprint("%02d", m);
    pause(100);
  }
  menu();
  return;
}  

void setSecond(void)                            // Similar to setYear
{                                               // See setYear for comments
  clear();
  text_size(LARGE);
  oledprint("SEC");
  submenu();

  int s = dt.s;

  cursor(0, 1);    
  oledprint("%02d", s);
  pause(1000);
  while(1)
  {
    int states = buttons();
    if(states == 0b0000001)
    {
      s++;
      if(s > 59) s = 0;
    }
    else if(states == 0b0000100)
    {
      s--;
      if(s < 0) s = 59;
    }
    else if(states == 0b0000010)
    {
      dt.s = s;
      break;
    }
    text_size(LARGE);
    cursor(0, 1);
    oledprint("%02d", s);
    pause(100);
  }
  menu();
  return;
}  
