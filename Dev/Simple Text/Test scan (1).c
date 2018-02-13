#include "simpletools.h"

int val;
int n = 0;

int main()
{
  while(1)
  {
    if ((((n / 3) % 2) & 1) == 1)
    {
      print("echo off\r");
      terminal_setEcho(simpleterm_pointer(), 0);
    }
    else
    {
      print("echo on\r");
      terminal_setEcho(simpleterm_pointer(), 1);
    }                 
    n++;
    print("enter a number: ");
    scan("%d ", &val);
    print("\rYou entered %d\r\r", val);
    pause(1000);
  }
}
