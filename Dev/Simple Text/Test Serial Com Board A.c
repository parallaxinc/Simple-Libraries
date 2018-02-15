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
    n++;
    writeDec(com, n);
    writeChar(com, '\r');
    val = readDec(com);
    print("val = %d\r", val);
    pause(100);
  }
}