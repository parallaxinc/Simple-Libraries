/*
  Hello Serial LCD.c
  
  Demonstrates using half duplex serial communication to control a Parallax 
  Serial LCD.

  http://learn.parallax.com/propeller-c-simple-protocols/half-duplex-serial
*/

#include "simpletools.h"

serial *lcd;

const int ON  = 22;
const int CLR = 12;

int main()
{
  lcd = serial_open(12, 12, 0, 9600);
 
  writeChar(lcd, ON);
  writeChar(lcd, CLR);
  pause(5);
  dprint(lcd, "Hello LCD!!!");
}