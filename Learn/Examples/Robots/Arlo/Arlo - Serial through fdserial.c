/*
  Arlo Serial through fdserial.c
*/

#include "simpletools.h"
#include "fdserial.h"

#define SERVO_L 12 

char dhb10_reply[48];
char *reply;

fdserial *arlo;

char *config(void);

int main()
{
  arlo = fdserial_open(SERVO_L, SERVO_L, 0b1100, 19200);
  pause(10);

  print("SPEED & DISTANCE\n\n");
  print("To DHB-10         From DHB-10\n");
  print("-------------     ----------------\n");

  print("gospd 32 32\\r     ");
  dprint(arlo, "gospd 32 32\r");
  reply = config();
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  pause(2000);

  print("gospd 0 0\\r       ");
  dprint(arlo, "gospd 0 0\r");
  reply = config();
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  // Display distance reply as text
  print("dist\\r            ");
  dprint(arlo, "dist\r");
  reply = config();
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  print("-------------     ----------------\n");

  // Convert distance reply text to numeric values to use in 
  // calculations, and display the results stored by int variables.
  int countLeft, countRight;
  print("\nVARIABLE VALUES\n", reply);
  sscan(reply, "%d%d", &countLeft, &countRight);
  print("countLeft = %d, countright = %d\n", countLeft, countRight);
}

char *config(void)
{
  memset(dhb10_reply, 0, 48);
  int i = 0, cta = 0, ca = 0;
  int t = CNT;
  int dt = CLKFREQ;
  while(1)
  {
    cta = fdserial_rxCount(arlo);
    if(cta)
    {
      ca = readChar(arlo);
      dhb10_reply[i] = ca;
      if(dhb10_reply[i] == '\r')
      {
        reply = dhb10_reply;
        break;
      }  
      i++;
    }
    if(CNT - t > dt)
    {
      *reply = 0;  
      break;
    }  
  }
  return reply;    
}