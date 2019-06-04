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
  setDisplayRotation(oledc, 0);
  setDisplayRotation(oledc, 1);
  toggle(26);
  set_direction(26, 1);
  fillCircle(oledc, 60, 60, 15, remapColor888to565(0xff0000));
  fillCircle(oledc, 40, 40, 15, remapColor888to565(0xff0000));
  
  drawLine(oledc, 0, 0, 95, 63, BLUE);
  pause(1000);
  drawPrint(oledc, "hello world!");
  //while (1) {
  //  invertDisplay(oledc, 1);
  //  pause(1000);
  //  invertDisplay(oledc, 0);
  //  pause(1000);
  //}
  
  
  for (int k = -32; k < 64; k++) {
    //scrollDisplay(oledc, 0, 0);
    drawPrint(oledc, "%d, ",k);
    //drawNumber(oledc, k, DEC);
    //drawText(oledc, ",");
    //pause(1000);
    //scrollDisplay(oledc, k, 0);
    pause(50);
  } 
     
    
}