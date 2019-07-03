/*
  ePaper Count Down.c
*/

// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "il3820.h"

// ------ Global Variables and Objects ------
screen *ePaper;
int item;



// ------ Main Program ------
int main() {
  ePaper = il3820_init(11, 10, 9, 8, 7, 6, 128, 296);
  setTextColor(ePaper, 0);
  setBgColor(ePaper, 1);
  clearDisplay(ePaper);
  for (item = 100; item >= 1; item--) 
  {
    setCursor(ePaper, 0, 0, 0);
    drawNumber(ePaper, item, DEC);
    updateDisplay(ePaper);
    pause(1000);
    clearDisplay(ePaper);
  }
}