/*
  ePaper Test Coordinates.c
*/

// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "il3820.h"

// ------ Global Variables and Objects ------
screen *ePaper;

// ------ Main Program ------
int main() 
{
  ePaper = il3820_init(11, 10, 9, 8, 7, 6, 128, 296);
  setTextColor(ePaper, 0);
  setBgColor(ePaper, 0);
  setCursor(ePaper, 3, 3, 0);
  drawText(ePaper, "Hello World!");
  setCursor(ePaper, 8, 8, 0);
  drawText(ePaper, "Hello world!");
  setCursor(ePaper, 11, 11, 0);
  drawText(ePaper, "Hello World!");
  updateDisplay(ePaper);

}