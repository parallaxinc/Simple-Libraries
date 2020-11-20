/*
  ePaper Draw Lines.c
*/

// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "il3820.h"

// ------ Global Variables and Objects ------
screen *ePaper;
int item;

// ------ Main Program ------
int main() 
{
  ePaper = il3820_init(11, 10, 9, 8, 7, 6, 128, 296);
  for (item = 5; item <= 50; item += (5)) 
  {
    drawLine(ePaper, item + 5, item + 5, item + 40, item + 10, 0);
    updateDisplay(ePaper);

  }
}