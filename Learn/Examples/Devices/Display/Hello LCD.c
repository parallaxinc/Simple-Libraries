/*
  Hello LCD.c
  Needs to be converted to access a Parallax Serial LCD library.
*/

#include "simpletools.h"

const int ON  = 22;
const int CLR = 12;

int main()
{
  serial lcd = sser_setTx(11, 9600);
  
  fputc(ON, lcd);
  fputc(CLR, lcd);
  pause(5);
  fprintf(lcd, "Hello LCD!!!");
}

