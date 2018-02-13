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
  msgIn = fdserial_open(3, 4, 0, 9600);
  pause(100);
  cog_run(sendVals, 256);
  while(1)
  {
    //memset(s, 0, 10);
    //readStr(msgIn, s, 10);
    //while(readChar(msgIn) != '\r');
    val = readDec(msgIn);
    print("val = %d\r", val);
    //val = readChar(msgIn);
    //print("%c", val);
    //print("%s\r", s);
    /* works with fdser send and receive
    c = readChar(msgIn);
    if(isprint(c)) print("%c", c); else print("[%d]", c);
    if(c == 13 || c == 10) print("\r");
    */
  }
}

void sendVals()
{
  msgOut = fdserial_open(4, 3, 0, 9600);
  int t = CNT;
  int dt = CLKFREQ;
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
