/*
   Multicore Dots.c
   Functions running in separate cogs independently update the positions
   of two different dots.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void dot_A();                                // Forward declare functions
void dot_B();
 
void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  cog_run(dot_A, 128);                       // dot_A to new cog
  cog_run(dot_B, 128);                       // dot_B to new cog 
} 

void dot_A()                                  // dot_A function
{
  srand(123);                                 // Random number seed
  int x, y, vx, vy, ox, oy, dt, t;            // Plotting & time
  x = 5 + rand() % 100;                       // Random inital x
  ox = x;                                     // Initialize old x
  y = 3 + rand() % 50;                        // Repeat for y
  oy = y;        
  vx = 1 + rand() % 3;                        // Distance increments
  vy = 1 + rand() % 3;
  dt = 15 + rand() %10;                       // Refresh time increment
  while (1)                                   // Cog loop
  {
    point( x, y, 1);                          // Plot new point
    pause(dt);                                // Wait refresh increment
   
    ox = x;                                   // Figure out old points 
    oy = y;
    point(ox, oy, 0);                         // Blot out old points

    x = x + vx;                               // Set up new points
    y = y + vy;
    
    if (x >= 125 || x <= 2) {                 // Limit point positions
      vx = -1 * vx;
    } 
    if (y >= 62 || y <= 2) {
      vy = -1 * vy;
    }
  }
}


// Same function, different seed, and different cog
void dot_B()                                 
{
  srand(456);
  int x, y, vx, vy, ox, oy, dt, t;
  x = 5 + rand() % 100;
  ox = x;
  y = 3 + rand() % 50;
  oy = y;
  vx = 1 + rand() % 3;
  vy = 1 + rand() % 3;
  dt = 15 + rand() %10;
  while (1)
  {
    point( x, y, 1);
    pause(dt);  
   
    ox = x;
    oy = y;
    point(ox, oy, 0); 

    x = x + vx;
    y = y + vy;
    
    if (x >= 125 || x <= 2) {
      vx = -1 * vx;
    } 
    if (y >= 62 || y <= 2) {
      vy = -1 * vy;
    }
  }
}

