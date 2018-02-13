#include "simpletools.h"
#include "serial.h"
#include "fdserial.h"

fdserial *msgOut;

serial *msgIn;

char s[10];

int val;

void sendVals();

int main()
{
  msgIn = serial_open(3, 4, 0, 9600);
  pause(100);
  cog_run(sendVals, 256);
  while(1)
  {
    memset(s, 0, 10);
    //readStr(msgIn, s, 10);
    //while(readChar(msgIn) != '\r');
    val = readDec(msgIn);
    print("\rval = %d\r", val);
    //val = readChar(msgIn);
    //print("%c", val);
    //print("%s\r", s);
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
    writeChar(msgOut, '\n');
    //writeChar(msgOut, ' ');
  }
}      
