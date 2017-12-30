/*
  Acceleration speed test.
*/

#include "simpletools.h"
#include "abdrive.h"

void measureAcceleration();

volatile int l, lp, r, rp, begin, end, dts, dt, t, reps, ti, tf, state, statep, result;

int main() 
{
  result = 0;
  
  cog_run(measureAcceleration, 128);

  drive_speed(0, 0);

  drive_setAcceleration(FOR_SPEED, 2000);
  
  drive_speed(128, 128);
  
  while(result == 0);
  
  
  print("acceleration = %d ticks/s\r", result);
  
  drive_speed(0, 0);
}  

void measureAcceleration()
{
  state = input(14);
  while(state == input(14));
  
  ti = CNT;
  
  while(1)
  {
    if(input(14) == 0)
    {
      while(input(14) == 0);
      t = CNT;
      while(input(14) == 1);
      while(input(14) == 0);
      //while(input(14) == 1);
    }      
    else
    {
      while(input(14) == 1);
      t = CNT;
      while(input(14) == 0);
      while(input(14) == 1);
      //while(input(14) == 0);
    }    
    dt = CNT - t;
    if(dt <= ((CLKFREQ / 1000) * 15)) 
    {
      //reps++;
      //if(reps == 2)break;
      break;
    }      
  }    
  tf = CNT;
  
  dts = (tf - ti) / (CLKFREQ/1000);
  dts = 128000 / (dts);
  
  result = dts;
  
  while(1);
  
}  
  
