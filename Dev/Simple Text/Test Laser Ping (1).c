#include "simpletools.h" 

serial *lp;
char c;
char s[10];
int distance;

int main()
{
  lp = serial_open(8, -1, 0b111100, 9600);
  pause(10);
  low(8);
  //pause(1);
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
      memcpy(s, 0, 9);
      for(int n = 0; n < 9; n++)
      {
        s[n] = readChar(lp);
        if(n == 'r')
        {
          break;
        }   
      }               
      print("distacne = %s\r", s);
      pause(250);
    }      
  }  
}



      //distance = readDec(lp);
      //dscan(lp, "%d ", &distance);
      //for(int n = 0; n < 9; n++)
      //{
      //print("distance = %d\r", distance);
      //pause(250);    
