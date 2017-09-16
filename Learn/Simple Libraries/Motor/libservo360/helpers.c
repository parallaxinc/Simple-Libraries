#include "simpletools.h"  
//#include "servo.h" 
//#include "fdserial.h"
#include "servo360.h"


int servo360_getAngleCalc(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].angleCalc;
  lockclr(lock360);
  return val;
}  

int servo360_getCsop(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].csop;
  lockclr(lock360);
  return val;
}  


int servo360_getTopSpeed(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].speedLimit;
  lockclr(lock360);
  return val;
}  


int servo360_getRampStep(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].rampStep;
  lockclr(lock360);
  return val;
}  


int fb360_setRampStep(int pin, int stepSize)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
    
  while(lockset(lock360));
  fb[p].rampStep = stepSize;
  lockclr(lock360);
}


int fb360_findServoIndex(int pin)
{
  int p = 0;
  while(1)
  {
    if(p >= FB360_DEVS_MAX)
    {
      return -1;
    }       
    if(fb[p].pinCtrl == pin || fb[p].pinFb == pin)
    {
      return p;
    }
    p++;
  }          
}  


void fb360_captureOffset(int p)
{
  fb[p].pvOffset = fb[p].angleFixed;
}  


int unitsAngleToEncoder(int value)
{
  int result = value * UNITS_ENCODER / fb[0].unitsRev;
  return result;
}  


int unitsEncoderToAngle(int value)
{
  int result = value * fb[0].unitsRev / UNITS_ENCODER;
  return result;
}  



