/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "ssd1331.h"                      // Include simple tools

screen *oled;

int main()                                    // Main function
{
  oled = ssd1331_init(22, 21, 20, 19, 18, 96, 64);
  
  drawLine(oled, 0, 0, 95, 63, BLUE);
  drawPrint(oled, "hello world!");
}
