#include "abdrive.h"

volatile int abd_record = 0;               // Record values to an array

#ifdef interactive_development_mode
volatile int abd_rv[2600];
#endif // interactive_development_mode

#ifdef interactive_development_mode
void drive_displayInterpolation(void)
{
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  if(!intTabSetup) interpolation_table_setup();
 
  dprint(xbee, "Left Servo\n");
  dprint(xbee, "elCntL = %d, cntrLidx = %d\n\n", elCntL, cntrLidx);
  for(int r = 0; r < elCntL; r++)
  {
    dprint(xbee, "r = %d, spdrL = %d, spdmL = %d, \n", r, spdrL[r], spdmL[r]);
  }
  
  dprint(xbee, "Right Servo\n");
  dprint(xbee, "\n\nelCntR = %d, cntrRidx = %d\n\n", elCntR, cntrRidx);
  for(int r = 0; r < elCntR; r++)
  {
    dprint(xbee, "r = %d, spdrR = %d, spdmR = %d, \n", r, spdrR[r], spdmR[r]);
  }
  //getchar();  
  //#endif
}
#endif // interactive_development_mode


#ifdef interactive_development_mode
void drive_trimDisplay(void)
{
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  if(!intTabSetup) interpolation_table_setup();

  dprint(xbee, "trimFL %d, trimFR %d, trimBL %d, trimBR %d, trimticksF %d, trimticksB %d\n",
         trimFL, trimFR, trimBL, trimBR, trimticksF, trimticksB);
}
#endif // interactive_development_mode


#ifdef interactive_development_mode
void drive_displayControlSystem(int start, int end)
{
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  dprint(xbee, "\neaL = %d, eaR = %d \n\n", eaL, eaR);
  dprint(xbee, "ridx = %d \n\n", ridx);
  for(int i = start*11; i < (end-1) * 11; i+=11)
  {
    //dprint(xbee, "index = %d, speed = %d, dlc = %d, ticksL = %d, edL = %d, drc = %d, ticksR = %d, edr = %d\n", 
    //      i, rv[i],  rv[i+1], rv[i+2], rv[i+3], rv[i+4], rv[i+5], rv[i+6]); 
    dprint(xbee, "i = %d, v = %d, dlc = %d, ticksL = %d, edL = %d, pL = %d, iL = %d, drc = %d, ticksR = %d, edr = %d, pR = %d, iR = %d\n", 
          i, rv[i],  rv[i+1], rv[i+2], rv[i+3], rv[i+4], rv[i+5], rv[i+6], rv[i+7], rv[i+8], rv[i+9], rv[i+10]); 
  }
  dprint(xbee, "\neaL = %d, eaR = %d \n\n", eaL, eaR);
}
#endif // interactive_development_mode


#ifndef interactive_development_mode
fdserial *xbee;
#endif


#ifndef interactive_development_mode
void drive_record(int startStop)
{
  abd_record = startStop;
}
#endif

