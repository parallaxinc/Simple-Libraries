#include "simpletools.h"

void send_ecs(char *c, char *ec, char *ecs);

char ecList[] = {'\r', '\n', 0, 0};    // List of recognized end characters

char ecsrn[]  = {'\r', '\n', 0, 0};    // \r\n end character list
char ecsr[]   = {'\n',    0, 0, 0};    // \n cahracter list
char ecsn[]   = {'\r',    0, 0, 0};    // \r character list

int main()
{
  pause(1000);
  char str[] = "abcdef\r";
  send_ecs(str, ecList, ecsrn);
}

void send_ecs(char *c, char *ec, char *ecs)
{
  while(1)
  {
    for(int n = 0; n < 4; n++)
    {
      if(c[n] == ec[n])
      {
        while(1)
        {
          putChar(ecs[n]);
          if(ecs[n] == 0) break;
        } 
      }
      if(ecs[n] == 0) break;
    }
    
  }    
  return;
}                   