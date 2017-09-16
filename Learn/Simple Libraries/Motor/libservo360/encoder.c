#include "simpletools.h"  
//#include "servo.h" 
#include "fdserial.h"
#include "servo360.h"

//servo360 fb[2];

int fb360_dutyCycle(int p, int scale)
{
  int pin = fb[p].pinFb;
  CTRA = (1000 << 26) | pin;
  CTRB = (1100 << 26) | pin;
  FRQA = 1;
  FRQB = 1;
  
  int mask = 1 << pin;
  int phsa, phsb;
  
  while(INA & mask);
  PHSA = 0;
  while(!(INA & mask));
  PHSB = 0;
  while(INA & mask);
  phsa = PHSA;
  while(!(INA & mask));
  phsb = PHSB;
  
  CTRA = 0;
  CTRB = 0;

  int dc = (phsa * scale) / (phsa + phsb);
  
  return dc;
}  


int fb360_getTheta(int p)
{
  fb[p].dc = fb360_dutyCycle(p, FB360_M); 
  
  if(fb[p].angleSign == CCW_POS)
  {
    fb[p].theta = (FB360_ENC_RES - 1) - (fb[p].dc + FB360_B);
  }
  else if(fb[p].angleSign == CCW_NEG)
  {    
    fb[p].theta = fb[p].dc + FB360_B;
  }  

  fb[p].theta &= 0xFFF;
  return fb[p].theta;
}  


int fb360_crossing(int current, int previous, int units)
{
  int angleLow = units/3;
  int angleHigh = angleLow * 2;
  if(previous > angleHigh && current < angleLow)
  {
    return 1;
  }    
  else if(previous < angleLow && current > angleHigh)
  {
    return -1;
  }    
  else
  {
    return 0;
  }    
}      


void fb360_setPositiveDirection(int p, int direction)
{
  fb[p].angleSign = direction;
}  


