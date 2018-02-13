#include "simpletools.h"

int val;

int main()
{
  while(1)
  {
    print("enter a number: ");
    val = getDec();
    print("\rYou entered %d\r\r", val);
    pause(1000);
  }
}
