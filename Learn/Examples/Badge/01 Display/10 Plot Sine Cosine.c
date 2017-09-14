/*
   Plot Sine Cosine (1).c
   Plot y = sin(2theta) and y = cos(2theta) together.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x, y;                                    // Integer X and Y for pixels
float brad, theta;                           // Floating point for sin & cos 

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  line(0, 0, 0, 64, 1);                      // Line along left of screen
  line(0, 32, 128, 32, 1);                   // Horizontal line across center
  
  brad = 2*PI/128;                           // Brad value (binary radian)

  for(x = 0; x < 128; x++)                   // Count 0 to 127
  {
    theta = (float) x * brad;                // Theta in binary radians
	// Calculate with floating point, then
	// convert to int for plotting as point.
    y = 32 - (int)(24.0 * sin(2.0 * theta)); // y = sin(2theta)
    point(x, y, 1);                          // Plot white point
    y = 32 - (int)(24.0 * cos(2.0 * theta)); // y = cos(2theta)
    point(x, y, 1);                          // Plot white point
  }
}  
