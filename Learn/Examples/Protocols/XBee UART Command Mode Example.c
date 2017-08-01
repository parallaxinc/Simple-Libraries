/*
  XBee UART Loopback.c
  
  Demonstrates using full duplex serial communication to configure an
  XBee Series 1 radio.

  http://learn.parallax.com/propeller-c-simple-protocols/full-duplex-serial
*/

#include "simpletools.h"
#include "fdserial.h"

fdserial *xbee;
char response[10];

int xbcmd(char *cmd, char *reply, int bytesMax, int msMax);

int main()
{
  xbee = fdserial_open(9, 8, 0, 9600);
  pause(1000);
  print("cmd = +++\n");
  int bytes = xbcmd("+++", response, 10, 2000);
  if(bytes == 0)
    print("Timeout error.\n");
  else
  {
    print("reply = %s", response);
    print("cmd = ATBD\n");
    xbcmd("ATBD\r", response, 10, 20);
    print("reply = %s", response);
    print("cmd = ATCN\n");
    xbcmd("ATCN\r", response, 10, 20);
    print("reply = %s", response);
  }
}

int xbcmd(char *cmd, char *reply, int bytesMax, int msMax)
{
  int c = -1, n = 0;
  writeStr(xbee, cmd);
  memset(reply, 0, bytesMax);

  int tmax = (CLKFREQ/1000) * msMax;
  int tmark = CNT;

  while(1)
  {
    c = fdserial_rxCheck(xbee);
    if(c != -1)
      reply[n++] = c;
    if(CNT - tmark > tmax)
      return 0;
    if(c == '\r')
      return n;
  }
}