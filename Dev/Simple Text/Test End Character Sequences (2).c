#include "simpletools.h"

void send_ecs(char *c, char *ec, char *ecs);

char ecListRN[] = {'\r', '\n', 0, 0};    // List of recognized end characters
char ecListR[]  = {'\r',    0, 0, 0};    
char ecListN[]  = {'\n',    0, 0, 0};    

char ecsrn[]  = {'\r', '\n', 0, 0};    // \r\n end character list
char ecsn[]   = {'\n',    0, 0, 0};    // \n cahracter list
char ecsr[]   = {'\r',    0, 0, 0};    // \r character list

char str[] = "abcdef\0";

int main()
{
  pause(500);
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListRN, ecsrn);
  send_ecs(str, ecListRN, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListRN, ecsr);
  send_ecs(str, ecListRN, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListRN, ecsn);
  send_ecs(str, ecListRN, ecsn);
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

