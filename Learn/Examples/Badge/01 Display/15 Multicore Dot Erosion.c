/*
   Multicore Dot Erosion.c
   Control 100 dots in another cog, and allow them to erode text 
   that reports the dt variable, which the cog running the main 
   function can use to adust the other cog's dot update interval,
   which in turn affects dot speed.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void dots();

int *cog;                                    // Cog process ID
volatile int dt;                             // Shared variable
 
void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  dt = 30;                                   // Initial dot interval
  oledprint("dt = %02d", dt);                // Display interval
  cog = cog_run(dots, 512);                  // Launch dots into new cog
  pause(5000);                               // Wait 5 s
  dt = 10;                                   // Reduce dot interval (faster)
  cursor(0, 1);                              // Position cursor
  oledprint("dt = %02d", dt);                // Display new interval
  pause(9000);                               // Wait for erosion

  cog_end(cog);                              // Stop cog running dots

  clear();                                   // Clear display
  screen_auto(ON);                           // Resume auto-update
  
  int y;                                     // Parabolas draw curtain
  for(int x = 0; x < 128; x++)
  {
    y = 64 - (x * x / 32);
    point( x, y, 1);
    point(128-x, y, 1);
    //pause(10);
  }
  
  text_size(LARGE);                          // Say byebye.
  cursor(2, 1);
  oledprint("Bye!");
}  

// Same as dots from previous example, except that a single cog is
// updating 100 point dot arrays (instead of single dots).
void dots()
{
  int points = 100;
  int x[points], y[points], vx[points], vy[points], ox[points], oy[points];
  for(int i = 0; i < points; i++)
  {
    x[i] = 5 + rand() % 100;
    ox[i] = x[i];
    y[i] = 3 + rand() % 50;
    oy[i] = y[i];
    vx[i] = 1 + rand() % 3;
    vy[i] = 1 + rand() % 3;
  }    
  while (1)
  {
    screen_auto(OFF);
    for(int i = 0; i < points; i++)
    {
      point( x[i], y[i], 1);
    }    
    screen_auto(ON);
    screen_update();
    pause(dt);  
   
    screen_auto(OFF);
    for(int i = 0; i < points; i++)
    {
      ox[i] = x[i];
      oy[i] = y[i];
      point( ox[i], oy[i], 0); 
    }
    screen_auto(ON);
    screen_update();

    for(int i = 0; i < points; i++)
    {
      x[i] = x[i] + vx[i];
      y[i] = y[i] + vy[i];
      
      if (x[i] >= 125 || x[i] <= 2) {
        vx[i] = -1 * vx[i];
      } 
      if (y[i] >= 62 || y[i] <= 2) {
        vy[i] = -1 * vy[i];
      }
    }         
  }
}

