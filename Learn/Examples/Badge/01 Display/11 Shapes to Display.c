/*
   Shapes to Display.c
   Draw shapes in pixel arrays, position on screen, erase, and invert.
   These shape arrays are placed using 
      shape(array, colorOf1, xTopLeft, yTopLeft, pixelWidth, pixelHeight);
   Array is the array's address (its name without the square brackets).  
   The colorOf1 can be WHITE, BLACK, or XOR.  xTopLeft and yTopLeft are 
   the x pixels to the right and y pixels down position of the shape's
   top-left corner.  The pixelWidth and pixelHeight are the pixel 
   dimensions of the shape.     
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

char ball[];                                 // Shape array names
char paddle[];

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  screen_auto(OFF);                          // Disable auto-update
  while(1)
  {
	// Place regular shapes
    shape(ball, SCR_WHITE, 32, 16, 16, 16);
    shape(paddle, SCR_WHITE, 128-34, 64-32, 8, 24);
    screen_update();
    pause(500);
	// Erase shapes
    shape(ball, SCR_BLACK, 32, 16, 16, 16);
    shape(paddle, SCR_BLACK, 128-34, 64-32, 8, 24);
    screen_update();
    pause(500);
	// Invert shape colors
    shape(ball, SCR_XOR, 32, 16, 16, 16);
    shape(paddle, SCR_XOR, 128-34, 64-32, 8, 24);
    screen_update();
    pause(500);
	// Erase inverted colors
    shape(ball, SCR_BLACK, 32, 16, 16, 16);
    shape(paddle, SCR_BLACK, 128-34, 64-32, 8, 24);
    screen_update();
    pause(500);
  }    
}

char ball[] = 
{
  0b00000011,0b11000000,
  0b00001111,0b11110000,
  0b00011111,0b11111000,
  0b00111111,0b11111100,
  0b01111111,0b11111110,
  0b01111111,0b11111110,
  0b11111111,0b11111111,
  0b11111111,0b11111111,
  0b11111111,0b11111111,
  0b11111111,0b11111111,
  0b01111111,0b11111110,
  0b01111111,0b11111110,
  0b00111111,0b11111100,
  0b00011111,0b11111000,
  0b00001111,0b11110000,
  0b00000011,0b11000000,
}; 

char paddle[] = 
{
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
  0b01111110,
};  

