#include "simpletools.h"
#include "serial.h"
#include "fdserial.h"

char s[10];

int val;

int c;

int main()
{
  //msgIn = fdserial_open(31, 30, TEXT_ECHO_ON, 115200);
  //msgIn = fdserial_open(3, 7, 0, 9600);
  pause(2000);
  print("hello\r");
  //cog_run(sendVals, 256);
  while(1)
  {
    //val = readDec(msgIn);
    scan("%d", &val);
    print("val = %d\r", val);
  }
}

