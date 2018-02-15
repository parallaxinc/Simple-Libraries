#include "simpletools.h"
#include "serial.h"

serial *com;

int n;
int val;

int main() 
{
  com = serial_open(8, 7, 0, 9600);
  while (1) 
  {
    val = readDec(com);
    pause(1);
    writeDec(com, val);
    writeChar(com, '\r');
  }
}