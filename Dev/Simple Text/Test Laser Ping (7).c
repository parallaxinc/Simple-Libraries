#include "simpletools.h" 

serial *lp;
char c;
int distance;

int main()
{
  lp = serial_open(8, -1, 0, 9600);
  
  low(8);
  writeByte(lp, 'I');
  input(8);
 
  while(1)
  {
    c = readChar(lp);
    if(c == '\r')
    {
      distance = readDec(lp);               
      print("distance = %d\r", distance);
      pause(500);
    }      
  }  
}
