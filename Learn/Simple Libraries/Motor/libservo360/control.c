#include "simpletools.h"  
//#include "servo.h" 
#include "fdserial.h"
#include "servo360.h"


int fb360_pidA(int p)
{
  {
    fb[p].speedTarget  = 0;
    fb[p].angleError = 0;
    fb[p].erDist = 0;
    fb[p].erDistP = 0;
    fb[p].integralV = 0;
    fb[p].derivativeV = 0;
    fb[p].pV = 0;
    fb[p].iV = 0;
    fb[p].dV = 0;
    fb[p].opPidV = 0;

    fb[p].angleCalc = fb[p].angle;
    //fb[p].angleCalcP = fb[p].angleCalc;
  }    
  
  fb[p].er = fb[p].sp - fb[p].angle;
  fb[p].integral += fb[p].er;
  fb[p].derivative = fb[p].er - fb[p].erP;
  
  if(fb[p].integral > fb[p].iMax) fb[p].integral = fb[p].iMax;
  if(fb[p].integral < fb[p].iMin) fb[p].integral = fb[p].iMin;

  fb[p].p = (fb[p].Kp * fb[p].er) / SCALE_DEN_A;
  fb[p].i = (fb[p].Ki * fb[p].integral) / SCALE_DEN_A;
  fb[p].d = (fb[p].Kd * fb[p].derivative) / SCALE_DEN_A;
  
  fb[p].op = (fb[p].p + fb[p].i + fb[p].d);
  
  int opMax = fb[p].speedLimit / 4;
  
  if(fb[p].op > opMax) fb[p].op = opMax;
  if(fb[p].op < -opMax) fb[p].op = -opMax;
  
  fb[p].erP = fb[p].er;
  return fb[p].op;
}
  


int fb360_pidV(int p)  
{
  int opv;  
  int opMax = fb[p].speedLimit / 4;

  int transition = fb360_crossing(fb[p].angle, fb[p].angleP, UNITS_ENCODER);
        
  //angleNow = angle;

  fb[p].speedMeasured = (fb[p].angle - fb[p].angleP) * 50; 

  fb[p].angleDeltaCalc = fb[p].speedTarget / FB360_CS_HZ;
  
  //angleCalc = anglePrevCalc + angleDeltaCalc;
  fb[p].angleCalc += fb[p].angleDeltaCalc;

  fb[p].angleError = fb[p].angleCalc - fb[p].angle;

  fb[p].erDist = fb[p].angleError;
  fb[p].integralV += fb[p].erDist;
  fb[p].derivativeV = fb[p].erDist - fb[p].erDistP;
  
  if(fb[p].integralV > fb[p].iMaxV) fb[p].integralV = fb[p].iMaxV;
  if(fb[p].integralV < fb[p].iMinV) fb[p].integralV = fb[p].iMinV;

  fb[p].pV = (fb[p].KpV * fb[p].erDist) / SCALE_DEN_V;
  fb[p].iV = (fb[p].KiV * fb[p].integralV) / SCALE_DEN_V;
  fb[p].dV = (fb[p].KdV * fb[p].derivativeV) / SCALE_DEN_V;
  
  fb[p].opV = fb[p].pV + fb[p].iV + fb[p].dV;

  if(fb[p].opV > opMax) fb[p].opV = opMax;
  if(fb[p].opV < -opMax) fb[p].opV = -opMax;
  
  fb[p].erDistP = fb[p].erDist;
  //anglePrev = angleNow;
//  anglePrevCalc = angleCalc;
  return fb[p].opV;
  //
}


int fb360_upsToPulseFromTransferFunction(int unitsPerSec)
{
  int pw, b, mx;
  int ups = unitsPerSec/4;
  
  if(ups > 0)
  {
    mx = ups;
    b = B_POS;
    pw = mx + b;
  }
  else if(ups < 0)
  {
    mx = ups;
    b = B_NEG;
    pw = mx + b;
  }    
  else
  {
    pw = 15000;
  }
  return pw;    
}  


void fb360_speedControl(int p)
{

  {
    fb[p].er = 0;
    fb[p].integral = 0;
    fb[p].derivative = 0;
    fb[p].p = 0;
    fb[p].i = 0;
    fb[p].d = 0;
    fb[p].op = 0;
    fb[p].erP = 0;
    fb[p].pw = 0;
  }    

  
  if(fb[p].speedTarget != fb[p].speedReq)
  {
    int speedDifference = fb[p].speedReq - fb[p].speedTarget;
    if( abs(speedDifference) > fb[p].rampStep)
    {
      if(speedDifference > 0)
      {
        fb[p].speedTarget += fb[p].rampStep;
      }
      else if(speedDifference < 0)
      {
        fb[p].speedTarget -= fb[p].rampStep;
      }        
    }
    else
    {
      fb[p].speedTarget = fb[p].speedReq;
      //speedUpdateFlag = 0;
    }
    fb[p].pw = fb360_upsToPulseFromTransferFunction(fb[p].speedTarget);
    fb[p].drive = fb[p].pw - 15000;
    fb[p].opPidV = fb[p].drive + fb360_pidV(p);
  }
  else    
  {
    fb[p].opPidV = fb[p].drive + fb360_pidV(p);
  }
  fb[p].speedTargetP = fb[p].speedTarget;
}  
  
  