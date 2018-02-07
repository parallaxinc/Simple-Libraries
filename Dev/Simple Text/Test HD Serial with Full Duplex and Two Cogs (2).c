#include "simpletools.h"
#include "serial.h"
#include "fdserial.h"

fdserial *msgOut;
fdserial *msgIn;

char s[10];

int val;

int c;

void sendVals();

int main()
{
  msgIn = fdserial_open(3, 7, TEXT_ECHO_ON, 9600);
  //msgIn = fdserial_open(3, 7, 0, 9600);
  pause(100);
  cog_run(sendVals, 256);
  while(1)
  {
    //val = readDec(msgIn);
    dscan(msgIn, "%d", &val);
    print("val = %d\n", val);
  }
}

void sendVals()
{
  msgOut = fdserial_open(7, 3, 0, 9600);
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
