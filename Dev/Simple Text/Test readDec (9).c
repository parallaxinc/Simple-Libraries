#include "simpletools.h"
#include "serial.h"
#include "fdserial.h"

serial *msgOut;
serial *msgIn;

char s[10];

int val;

int c;

void sendVals();

int main()
{
  msgIn = serial_open(3, 7, 0, 9600);
  pause(100);
  cog_run(sendVals, 256);
  while(1)
  {
    //val = readDec(msgIn);
    dscan(msgIn, "%d", &val);
    print("val = %d\r", val);
  }
}

void sendVals()
{
  msgOut = serial_open(7, 3, 0, 9600);
  int t = CNT;
  int dt = CLKFREQ/10;
  int n = 0;
  while(1)
  {
    waitcnt(t += dt);
    writeDec(msgOut, n);
    writeChar(msgOut, '\r');
    n++;
    //writeChar(msgOut, '\n');
    //writeChar(msgOut, ' ');
  }
}      
