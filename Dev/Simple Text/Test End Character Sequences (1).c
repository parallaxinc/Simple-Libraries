#include "simpletools.h"

void send_ecs(char *c, char *ec, char *ecs);

char ecList[] = {'\r', '\n', 0, 0};    // List of recognized end characters

char ecsrn[]  = {'\r', '\n', 0, 0};    // \r\n end character list
char ecsn[]   = {'\n',    0, 0, 0};    // \n cahracter list
char ecsr[]   = {'\r',    0, 0, 0};    // \r character list

int main()
{
  print("hello\r");
  pause(1000);
  char str[] = "abcdef\n";
  send_ecs(str, ecList, ecsn);
  send_ecs(str, ecList, ecsn);
}

void send_ecs(char *c, char *ec, char *ecs)
{ 
  int i = 0;
  while(1)
  {
    for(int n = 0; n < 4; n++)
    {
      if(c[i] == ec[n])
      {
        for(int m = 0; m < 4; m++)
        {
          if(ecs[m] == 0 || ec[n] == 0) return;
          putChar(ecs[m]);
        }
        return;          
      }
      if(ec[n] == 0) break;
    }
    putChar(c[i]);  
    i++;
  }    
  return;
}                   

