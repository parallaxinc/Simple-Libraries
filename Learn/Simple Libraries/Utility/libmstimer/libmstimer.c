/*
  libmstimer.c
  
  mstimer library project for tutorial on adding Simple Libraries.  
*/

#include "simpletools.h"                      
#include "mstimer.h"

int main()                                   
{
  pause(1000);                               

  mstime_start();
  mark();
  while(1)
  {
    int time = mstime_get();
    printf("time = %d\n", time);                    
    wait(1000000);                               
  }    
}

