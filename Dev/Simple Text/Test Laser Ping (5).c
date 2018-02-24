#include "simpletools.h" 

serial *lp;
int distance;

int main()
{
  lp = serial_open(8, -1, 0, 9600);
  pause(1);
  low(8);
  pause(1);
  writeByte(lp, 'I');
  input(8);
 
  while(1)
  {
    while(readChar(lp) != '\r');
    distance = readDec(lp);      
    print("distance = %d\r", distance);
    pause(500);
  }  
}

