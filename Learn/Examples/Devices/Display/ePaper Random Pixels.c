/*
  ePaper random pixels.c
*/

// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "il3820.h"

// ------ Global Variables and Objects ------
screen *ePaper;
int item;
int PixelX;
int PixelY;

// ------ Main Program ------
int main() 
{
  ePaper = il3820_init(11, 10, 9, 8, 7, 6, 128, 296);
  for (item = 1; item <= 100; item++) 
  {
    PixelX = (random(0, (getDisplayWidth(ePaper))));
    PixelY = (random(0, (getDisplayHeight(ePaper))));
    drawPixel(ePaper, PixelX, PixelY, 0);
    updateDisplay(ePaper);
  }
}