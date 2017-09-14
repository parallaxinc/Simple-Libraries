/*
  Hello LCD.c

  Under development; Version 0.94 for use with SimpleIDE 9.40 and its Simple Libraries

  http://learn.parallax.com/propeller-c-simple-protocols/half-duplex-serial
*/

#include "simpletools.h"

const int ON  = 22;
const int CLR = 12;

int main()
{
  serial *lcd = serial_open(12, 12, 0, 9600);
  
  writeChar(lcd, ON);
  writeChar(lcd, CLR);
  pause(5);
  dprint(lcd, "Hello LCD!!!");
}

