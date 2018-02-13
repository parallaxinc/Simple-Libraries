#include "simpletools.h"
#include "serial.h"
#include "fdserial.h"

serial *msgOut;
serial *msgIn;

char s[10];

volatile int val;
volatile int idx;

int c;

void sendVals();
void receiveVals();

int main()
{
  cog_run(sendVals, 256);
  cog_run(receiveVals, 256);
  val = 0;
  int idxPrev = idx;
  while(1)
  {
    /*
    if(idx != idxPrev)
    {
      if(isprint(c)) print("%c", c); else print("[%d]", c);
      if(c == 13 || c == 10) print("\r");
      idxPrev = idx;
    }  
    */
    //val = readDec(msgIn);  
    while(idx == idxPrev);
    idxPrev = idx;  
    print("val = %d\r", val);
    //pause(500);
  }    
}

void receiveVals()
{
  msgIn = serial_open(3, 2, 0, 9600);
  pause(100);
  while(1)
  {
    //dscan(msgIn, "%d", &val);
    //val = readDec(msgIn);
    //pause(10);
    //c = readChar(msgIn);
    val = readDec(msgIn);
    idx++;
  }
}  

void sendVals()
{
  msgOut = serial_open(4, 3, 0, 9600);
  int t = CNT;
  int dt = CLKFREQ/10;
  int n = 0;
  while(1)
  {
    waitcnt(t += dt);
    writeChar(msgOut, ' ');
    writeChar(msgOut, ' ');
    writeDec(msgOut, n);
    writeChar(msgOut, '\r');
    writeChar(msgOut, '\n');
    n++;
    //writeChar(msgOut, ' ');
  }
}      
