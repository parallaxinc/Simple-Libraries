#include "simpletools.h"


int main()
{
  int val;
  while(1)
  {
    //val = random(-11, -14);
    val = random(0, -5);
    print("val = %d\r", val);
    pause(100);
  }    
}

