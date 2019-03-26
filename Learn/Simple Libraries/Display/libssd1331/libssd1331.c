/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "ssd1331.h"                      // Include simple tools
#include "colormath.h"

screen *oledc;

int main()                                    // Main function
{
  oledc = ssd1331_init(6, 7, 8, 9, 10, 96, 64);
  setDisplayRotation(oledc, 2);
  setDisplayRotation(oledc, 1);
  toggle(26);
  set_direction(26, 1);
  fillCircle(oledc, 60, 60, 15, remapColor(0xff0000, "8R8G8B", "5R6G5B"));
  fillCircle(oledc, 40, 40, 15, remapColor(0xff0000, "8R8G8B", "5R6G5B"));
  
  drawLine(oledc, 0, 0, 95, 63, BLUE);
  pause(1000);
  drawPrint(oledc, "hello world!");
  while (1) {
    invertDisplay(oledc, 1);
    pause(1000);
    invertDisplay(oledc, 0);
    pause(1000);
  }

}
