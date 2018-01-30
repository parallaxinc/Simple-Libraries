/*
  Acceleration speed test.
*/

#include "simpletools.h"
#include "servo360.h"

servo360_cog_t _fb360c;
servo360_t _fs[S360_DEVS_MAX];

void measureAcceleration();

volatile int l, lp, r, rp, begin, end, dts, dt, t, reps, ti, tf, state, statep, result;
volatile int position, positionP;
volatile int pulseCount;

int main() 
{
  result = 0;
  servo360_connect(12, 14);
  servo360_speed(12, 0);
  pause(100);  
  
  cog_run(measureAcceleration, 512);

  servo360_setAcceleration(12, 36);
  //servo360_setRampStep(12, 72 * 4096 / 360);

  pause(50);

  servo360_speed(12, 720);
  for(int n = 0; n < 80; n++)
  {
    print("position = %d\r", position);
    pause(100);
    if(result != 0) break;
  }    
  servo360_speed(12, 0);
  
  print("acceleration = %d ticks/s^2\r", result);
}  

void measureAcceleration()
{
  pulseCount = _fb360c.pulseCount;
  positionP  = (_fs[0].angle * 360 / 4096);
  while(1)
  {
    while(pulseCount == _fb360c.pulseCount);
    pulseCount = _fb360c.pulseCount;
    position = (_fs[0].angle * 360 / 4096);
    if(abs(position - positionP) > 10)
    {
      pulseCount = _fb360c.pulseCount;      
      positionP = position;
      break;
    }      
  }    
    
  ti = CNT;
  
  while(1)
  {
    t = CNT;
    while(1)
    {
      while(pulseCount == _fb360c.pulseCount);
      pulseCount = _fb360c.pulseCount;
      position = (_fs[0].angle * 360 / 4096);
      if(abs(positionP - position) >= 16) break;
      positionP = position;
      //pause(2);
    }      
    dt = CNT - t;
    if(dt <= ((CLKFREQ / 1000) * 20)) 
    {
      break;
    }    
    pause(4);
    toggle(26);  
  } 
     
  tf = CNT;
  low(26);
  
  dts = (tf - ti) / (CLKFREQ/1000);
  dts = 720000 / (dts);
  
  result = dts;
  
  while(1);
}  
  
