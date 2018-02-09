#include "simpletools.h"

char ecListRN[] = {'\r', '\n', 0, 0};    // List of recognized end characters
char ecListR[]  = {'\r',    0, 0, 0};    
char ecListN[]  = {'\n',    0, 0, 0};    

char ecsrn[]  = {'\r', '\n', 0, 0};    // \r\n end character list
char ecsn[]   = {'\n',    0, 0, 0};    // \n cahracter list
char ecsr[]   = {'\r',    0, 0, 0};    // \r character list

char str[] = "abcdef\0 ";


void send_ecs(char *c, char *ec, char *ecs)
{ 
  char *ecp = ec;
  while(1)
  {
    for(int n = 0; n < 4; n++)
    {
      if(*c == *ec)
      {
        for(int m = 0; m < 4; m++)
        {
          if(*ecs == 0 || *ec == 0) return;
          putChar(*ecs++);
        }
        return;          
      }
      if(*ec++ == 0) break;
    }
    putChar(*c++);  
    ec = ecp;
  }    
  return;
}                   


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
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListRN, ecsr);
  send_ecs(str, ecListRN, ecsr);
  send_ecs(str, ecListRN, ecsr);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListR, ecsrn);
  send_ecs(str, ecListR, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListR, ecsr);
  send_ecs(str, ecListR, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListR, ecsn);
  send_ecs(str, ecListR, ecsn);
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListR, ecsr);
  send_ecs(str, ecListR, ecsr);
  send_ecs(str, ecListR, ecsr);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListN, ecsrn);
  send_ecs(str, ecListN, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListN, ecsr);
  send_ecs(str, ecListN, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListN, ecsn);
  send_ecs(str, ecListN, ecsn);
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListN, ecsr);
  send_ecs(str, ecListN, ecsr);
  send_ecs(str, ecListN, ecsr);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
  print("0_n_rn\r");
  memcpy(str, "\0", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("0_n_r\r");
  memcpy(str, "\0", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("0_n_n\r");
  memcpy(str, "\0", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("0_n_r\r");
  memcpy(str, "\0", 9);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
  print("r_n_rn\r");
  memcpy(str, "\r", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("r_n_r\r");
  memcpy(str, "\r", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("r_n_n\r");
  memcpy(str, "\r", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("r_n_r\r");
  memcpy(str, "\r", 9);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
  print("n_n_rn\r");
  memcpy(str, "\n", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("n_n_r\r");
  memcpy(str, "\n", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("n_n_n\r");
  memcpy(str, "\n", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("n_n_r\r");
  memcpy(str, "\n", 9);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
  print("rn_n_rn\r");
  memcpy(str, "\r\n", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("rn_n_r\r");
  memcpy(str, "\r\n", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("rn_n_n\r");
  memcpy(str, "\r\n", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("rn_n_r\r");
  memcpy(str, "\r\n", 9);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(500);
}

