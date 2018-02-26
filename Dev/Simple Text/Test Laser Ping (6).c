#include "simpletools.h" 

serial *lp;
char c;
int distance;

int main()
{
  lp = serial_open(8, -1, 0, 9600);
//  pause(10);
  low(8);
//  pause(1);
  //writeByte(lp, 'I');
  pulse_out(8, 100);
  pulse_out(8, 100);
  pulse_out(8, 100);
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
