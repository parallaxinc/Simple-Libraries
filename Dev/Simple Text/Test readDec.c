#include "simpletools.h"
#include "serial.h"

serial *msgOut;
serial *msgIn;

int val;

void sendVals();

int main()
{
  cog_run(sendVals, 256);
  msgIn = serial_open(3, 4, 0, 9600);
  while(1)
  {
    while(readChar(msgIn) != '\r');
    val = readDec(msgIn);
    //print("enter a number: ");
    //val = getDec();
    print("\rval = %d\r\r", val);
    //pause(1000);
  }
}

void sendVals()
{
  msgOut = serial_open(4, 3, 0, 9600);
  int t = CNT;
  int dt = CLKFREQ;
  int n = 0;
  while(1)
  {
    n++;
    waitcnt(t += dt);
    writeDec(msgOut, n);
    writeChar(msgOut, '\r');
  }
}      
