/*
  Hello LCD.c
  Needs to be converted to access a Parallax Serial LCD library.
  learn.parallax.com/propeller-c-simple-devices/serial-lcd
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

