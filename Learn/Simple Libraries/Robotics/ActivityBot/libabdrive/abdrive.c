/*
  abdrive.c library source
*/


#include "abdrive.h"                   // Include servo lib funct defs
#include "simpletools.h"
#include "simpletext.h"
#include "fdserial.h"
#include <string.h>



//#define test_t_interval
#ifdef test_t_interval
  volatile int rec_t[8000 / 4];
#endif



/*
  #ifdef interactive_development_mode
  dprint(xbee, "B After ramp distRampL = %d\n", distRampL);
  #endif
*/


void drive_com(int arrayLcnt, int arrayRcnt, 
               int centerL, int centerR, 
               int* pwAddrL, int* pwAddrR, 
               int* spdAddrL, int* spdAddrR);
void drive_set(int left, int right);
void encoders(void *par);
void interpolate(int* ltmp, int* rtmp);
void interpolation_table_setup();
void servos_diffDrive(void);
void drive_record(int startStop);
void drive_displayControlSystem(int start, int end);
void set_drive_speed(int left, int right);
void interpolate2(int *ltmp, int *rtmp);
void drive_rampStep2(int left, int right);


volatile char abd_str[128];

// drive_trimset
volatile int abd_trimFL, abd_trimFR, abd_trimBL, abd_trimBR, abd_trimticksF, abd_trimticksB;
volatile int abd_trimticksF = 0;
volatile int abd_trimticksB = 0;
int abd_eeAddr;

volatile int abd_aL;                                        // Acceleration in ticks/(s^2)
volatile int abd_aR;

volatile int abd_speedLold;
volatile int abd_speedRold;
volatile int abd_stopCtrL;
volatile int abd_stopCtrR;
volatile int abd_stopPulseRepsL = 8;
volatile int abd_stopPulseRepsR = 8;

// drive_goto
volatile int abd_ticksL = 0;                                // Measured distance left/right
volatile int abd_ticksR = 0;
volatile int abd_speedLT;                                   // Target speed left/right
volatile int abd_speedRT;                                   
volatile int abd_speedL;                                    // Current requested speed
volatile int abd_speedR;                                   

volatile int abd_ticksLi;
volatile int abd_ticksLf;

volatile int abd_ticksRi;
volatile int abd_ticksRf;

volatile int abd_gotoFlagL;
volatile int abd_gotoFlagR;
//volatile int abd_ticksGuardL;
//volatile int abd_ticksGuardR;


volatile int abd_rampStep = 8;
volatile int abd_rampStepL = 8;
volatile int abd_rampStepR = 8;
volatile int abd_speedLimit = 128;
volatile int abd_speedLimitTemp = 0;
volatile int abd_speedLimitL;
volatile int abd_speedLimitR;
volatile int abd_ticksGuardL;
volatile int abd_ticksGuardR;


volatile int abd_zeroDelay = ON;

volatile int abd_dlc;                                      // distance left calculated
volatile int abd_drc;                                      // distance right calculated
volatile int abd_dlca = 0;                                 // distance left calculated (accumulated)
volatile int abd_drca = 0;                                 // distance right calculated (accumulated)
volatile int abd_dsr = 400;                                // Distance sampling rate


volatile int abd_edL;                                      // error distance left
volatile int abd_edR;                                      // error distance right
volatile int abd_pL;                                       // proportional left
volatile int abd_pR;                                       // proportional right
volatile int abd_iL;                                       // integral left
volatile int abd_iR;                                       // integral right
volatile int abd_eaL = 0;                                  // Accumulated errors L/R
volatile int abd_eaR = 0;
volatile unsigned int _servoPulseReps;                     // Servo pulse counter

// servoPins
volatile int abd_sPinL = 12, abd_sPinR = 13;   // Global variables
volatile int abd_ePinL = 14, abd_ePinR = 15;
volatile int abd_us;
int abd_intTabSetup = 0;

// debug
volatile int abd_record = 0;               // Record values to an array

// display
volatile int abd_elCntL;
volatile int abd_elCntR;
volatile int abd_cntrLidx;
volatile int abd_cntrRidx;
int abd_spdrL[120];
int abd_spdmL[120];
int abd_spdrR[120];
int abd_spdmR[120];

static volatile int cntrLval;
static volatile int cntrRval;

static int cog = 0;
//static int servoCog2 = 0;
//static unsigned int stack[44 + 252];
static unsigned int stack[44 + 352];
//static unsigned int servoStack[(160 + (150 * 4)) / 4];


//static int a = 0;
static int r = 0;

//static int intTabSetup = 0;
//static int eeStarted = 0;

static volatile int trimctr = 0;
static volatile int dca, trimticks;

static volatile int leftPrev;
static volatile int  rightPrev;

static volatile int kp[6];

static volatile int tcL;
static volatile int tcR;
static volatile int tiL;


static volatile int ridx = 0;


static volatile int tiR;

static volatile int stateL;
static volatile int stateR;

static volatile int* pwL;
static volatile int* pwR;
static volatile int* spdL;
static volatile int* spdR;

//static volatile int etpsR;    // encoder ticks per second requested right
//static volatile int etpsL;    // encoder ticks per second requested right

static volatile int pcount;
static volatile unsigned int _sprOld;
static volatile unsigned int _sprNext;


static volatile int ssiL; // servo speeed interpolated left
static volatile int ssiR; // servo speeed interpolated right

static volatile int driveL;
static volatile int driveR;

static volatile int phsL;
static volatile int phsR;
static volatile int phsLr;
static volatile int phsRr;

static int trimFunction = 1;
static int encoderFeedback = 1;

static volatile int speedLprev = 0;
static volatile int speedRprev = 0;

volatile int nudgeIncL = 5;
volatile int nudgeIncR = 5;

volatile int abd_nudgeCtrL;
volatile int abd_nudgeCtrR;
volatile int abd_nudgeIncL;
volatile int abd_nudgeIncR;
volatile int abd_distErrorL;
volatile int abd_distErrorR;

volatile int signL;
volatile int signR;

volatile int abd_distL;
volatile int abd_distR;

volatile int abd_ditherAL;
volatile int abd_ditherAR;
volatile int abd_ditherALa;
volatile int abd_ditherARa;
volatile int abd_ditherALd;
volatile int abd_ditherARd;
volatile int abd_ditherALp;
volatile int abd_ditherARp;

volatile int abd_ditherVL;
volatile int abd_ditherVR;
volatile int abd_ditherVLa;
volatile int abd_ditherVRa;
volatile int abd_ditherVLd;
volatile int abd_ditherVRd;
volatile int abd_ditherVLp;
volatile int abd_ditherVRp;

volatile int abd_blockGoto = 1;

volatile int abd_speedLi;
volatile int abd_speedRi;
volatile int abd_speedLd;
volatile int abd_speedRd;
volatile int abd_dvFlagL;
volatile int abd_dvFlagR;
volatile int abd_dvFlagL;
volatile int abd_dvFlagR;
volatile int abd_dvFlagL;
volatile int abd_dvFlagR;


//int xbee_setup = 0;


int drive_open()
{
  if(!abd_intTabSetup)
  {
    interpolation_table_setup();
    set_drive_speed(0, 0);
  }
  return cog;
}

void drive_close()
{
  if(cog)
  {
    cogstop(cog - 1);
    cog = 0;
  }
}

void drive_setMaxSpeed(int maxTicksPerSec)
{
  abd_speedLimit = maxTicksPerSec;
}


void drive_setRampStep(int stepsize)
{
  abd_rampStep = stepsize;
}


void drive_setAcceleration(int ticksPerSecSq)
{
  abd_rampStep = ticksPerSecSq/50;
}

void drive_gotoMode(int mode)
{
  abd_blockGoto = mode;
}  


void drive_feedback(int enabled)
{
  encoderFeedback = enabled;
}


int drive_gotoStatus(int side)
{
  if(side == SIDE_LEFT)
  {
    return abd_gotoFlagL;
  }
  else if(side == SIDE_RIGHT)
  {
    return abd_gotoFlagR;
  }
  else
  {
    return abd_gotoFlagL + abd_gotoFlagR;
  }    
}  

/*
void drive_gotoMode(int mode)
{
  
}  
*/

void drive_trim(int enabled)
{
  trimFunction = enabled;
}


void drive_com(int arrayLcnt, int arrayRcnt, 
               int centerL, int centerR, 
               int* pwAddrL, int* pwAddrR, 
               int* spdAddrL, int* spdAddrR)
{
  abd_elCntL = arrayLcnt;
  abd_elCntR = arrayRcnt;
  abd_cntrLidx = centerL;
  abd_cntrRidx = centerR;
  pwL = pwAddrL;
  pwR = pwAddrR;
  spdL = spdAddrL;
  spdR = spdAddrR;
  cntrLval = pwAddrL[abd_cntrLidx];
  cntrRval = pwAddrR[abd_cntrRidx];
}


void interpolation_table_setup()
{
  if(!abd_us) abd_us = CLKFREQ/1000000; 

  //ee_putStr("ActivjtyBot", 12, _ActivityBot_EE_Start_);
  //putStr("hello");

  unsigned char str[12];
  ee_getStr(str, 12, _ActivityBot_EE_Start_);
  ee_getStr(str, 12, _ActivityBot_EE_Start_);

  /*
  if(strcmp(str, "ActivityBot"))
  {
    putStr("Calibrate your ActivityBot first!\n");
    putStr("For info, go to learn.parallax.com/ActivityBot/Calibrate-Your-ActivityBot\n");
    //drive_feedback(0);
  }
  */

  abd_eeAddr = _ActivityBot_EE_Start_ + _ActivityBot_EE_Left_;
  //print("left abd_eeAddr = %d\n", abd_eeAddr);
  int cntL = ee_getInt(abd_eeAddr);
  abd_eeAddr += 4;
  int zstartL = ee_getInt(abd_eeAddr);
  abd_eeAddr += 4;
  for(r = 0; r < cntL; r++)
  {
    abd_spdrL[r] = ee_getInt(abd_eeAddr);
    abd_eeAddr+=4;
    abd_spdmL[r] = ee_getInt(abd_eeAddr);
    abd_eeAddr += 4;  
  }
  abd_spdmL[cntL - 1] = 1000;
  abd_spdmL[0] = 1000;

  abd_eeAddr = _ActivityBot_EE_Start_ + _ActivityBot_EE_Right_;
  //print("right abd_eeAddr = %d\n", abd_eeAddr);
  int cntR = ee_getInt(abd_eeAddr);
  abd_eeAddr += 4;
  int zstartR = ee_getInt(abd_eeAddr);
  abd_eeAddr += 4;
  for(r = 0; r < cntR; r++)
  {
    abd_spdrR[r] = ee_getInt(abd_eeAddr);
    abd_eeAddr+=4;
    abd_spdmR[r] = ee_getInt(abd_eeAddr);
    abd_eeAddr += 4;  
  } 
  abd_spdmR[cntR - 1] = 1000;
  abd_spdmR[0] = 1000;

  drive_com(cntL, cntR, zstartL, zstartR, abd_spdrL, abd_spdrR, abd_spdmL, abd_spdmR);

  abd_eeAddr      =  _ActivityBot_EE_Start_ + _ActivityBot_EE_Trims_;
  //print("trims abd_eeAddr = %d\n", abd_eeAddr);
  abd_trimFL      =  ee_getInt(abd_eeAddr +  0);
  abd_trimFR      =  ee_getInt(abd_eeAddr +  4);
  abd_trimBL      =  ee_getInt(abd_eeAddr +  8);
  abd_trimBR      =  ee_getInt(abd_eeAddr + 12);
  abd_trimticksF  =  ee_getInt(abd_eeAddr + 16);
  abd_trimticksB  =  ee_getInt(abd_eeAddr + 20);

  int eeAddr = _ActivityBot_EE_Start_  + _ActivityBot_EE_Pins_;
  unsigned char pinInfo[16];

  for(int i = 0; i < 16; i++) 
    pinInfo[i] = ee_getByte(eeAddr + i);

  if(pinInfo[0] == 's' && pinInfo[1] == 'p' && pinInfo[2] == 'L' && pinInfo[5] == 'R')
  {
    abd_sPinL = (int) pinInfo[3];
    abd_sPinR = (int) pinInfo[6];
  }
    
  if(pinInfo[8] == 'e' && pinInfo[9] == 'p' && pinInfo[10] == 'L' && pinInfo[13] == 'R')
  {
    abd_ePinL = (int) pinInfo[11];
    abd_ePinR = (int) pinInfo[14];
  }

  //print("abd_spinL = %d, abd_sPinR = %d, abd_epinL = %d, abd_ePinR = %d\n", 
  //       abd_sPinL,      abd_sPinR,      abd_ePinL,      abd_ePinR); 

  abd_intTabSetup = 1;
}

void interpolate2(int *ltmp, int *rtmp)
{
  
  int left = *ltmp;
  int right = *rtmp;

  /////print("\netpsL = %d, etpsR = %d\n\n", etpsL, etpsR);

  int listep;
  int limit;
  int lookupval;

  if(left > 0)
  {
    listep = 1;
    limit = abd_elCntL;
    lookupval = left;
  }
  else
  {
    listep = -1;
    limit = 0;
    lookupval = -left;
  }

  int rprev = abd_cntrLidx;

  for(int r = abd_cntrLidx; r != limit; r+=listep)
  {
    if(spdL[r] == lookupval)
    {
      left = pwL[r]; 
      break;
    }
    if((spdL[rprev] < lookupval) && (spdL[r] > lookupval))
    {
      int x = ((pwL[r]-pwL[rprev])*(lookupval-spdL[rprev]))/(spdL[r]-spdL[rprev]); 
      left = pwL[rprev] + x; 
      break;
    }
    rprev = r;
  }
  //if(r >= elCntL) left = pwL[elCntL];                    // 2013.08.17
  //if(r <= 0) left = pwL[0];                              // 2013.08.17
  //if(r >= elCntL) left = *ltmp;                    // 2013.08.17
  //if(r <= 0) left = *ltmp;                              // 2013.08.17

  if(right > 0)
  {
    listep = 1;
    limit = abd_elCntL;
    lookupval = right;
  }
  else
  {
    listep = -1;
    limit = 0;
    lookupval = -right;
  }

  rprev = abd_cntrRidx;

  for(int r = abd_cntrRidx; r != limit; r+=listep)
  {
    if(spdR[r] == lookupval)
    {
      right = pwR[r]; 
      break;
    }
    if((spdR[rprev] < lookupval) && (spdR[r] > lookupval))
    {
      int x = ((pwR[r]-pwR[rprev])*(lookupval-spdR[rprev]))/(spdR[r]-spdR[rprev]); 
      right = pwR[rprev] + x; 
      break;
    }
    rprev = r;
  }
  //if(r >= elCntR) right = pwR[elCntR];                    // 2013.08.17
  //if(r <= 0) right = pwR[0];                              // 2013.08.17
  //if(r >= elCntR) right = *rtmp;                          // 2013.08.17
  //if(r <= 0) right = *rtmp;                               // 2013.08.17

  *ltmp = left;
  *rtmp = right;
}


void set_drive_speed(int left, int right)
{
  // ??? Is this necessary ??? //
  if(encoderFeedback)
  {
    if(left > abd_speedLimit) left = abd_speedLimit;
    if(left < -abd_speedLimit) left = -abd_speedLimit;
    if(right > abd_speedLimit) right = abd_speedLimit;
    if(right < -abd_speedLimit) right = -abd_speedLimit;
  }

  // ??? Set initial speeds ??? //
  //abd_speedLi = abd_speedLT;
  //abd_speedRi = abd_speedRT;
  abd_speedLi = abd_speedL;
  abd_speedRi = abd_speedR;
  
  abd_speedLT = left;
  abd_speedRT = right;
  /*
  sprint(
        abd_str, "\rvL%d, rspdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d | "\
        "vR%d, spdLimR=%d, rmpStpR=%d dthrAR=%d, dthrVR=%d\r\r",
        abd_speedLT, abd_speedLimitL, abd_rampStepL, abd_ditherAL, abd_ditherVL,
        abd_speedRT, abd_speedLimitR, abd_rampStepR, abd_ditherAR, abd_ditherVR
        ); 
  */      
  abd_speedLd = abd_speedLT - abd_speedLi;
  abd_speedRd = abd_speedRT - abd_speedRi;
  
  
  
  /*
  abd_rampStepL = abd_rampStep;
  abd_rampStepR = abd_rampStep;
  */
  
  // ??? Is this necessary, does it cause bugs ??? //
  abd_speedLimitL = abd_speedLimit;
  abd_speedLimitR = abd_speedLimit;
  
  /*
  abd_ditherAL = 0;
  abd_ditherAR = 0;
  */




  abd_ditherALa = 0;
  abd_ditherARa = 0;
  abd_ditherALd = 0;
  abd_ditherARd = 0;
  abd_ditherALp = 0;
  abd_ditherARp = 0;
  
  abd_ditherVLa = 0;
  abd_ditherVRa = 0;
  abd_ditherVLd = 0;
  abd_ditherVRd = 0;
  abd_ditherVLp = 0;
  abd_ditherVRp = 0;
  
  abd_gotoFlagL = 0;
  abd_gotoFlagR = 0;
  abd_dvFlagL = 1;
  abd_dvFlagR = 1;




  abd_speedLimitR = abd_speedLimit;
  abd_speedLimitL = abd_speedLimit;
  abd_rampStepL = abd_rampStep;
  abd_rampStepR = abd_rampStep;
  abd_ditherAL = 0;
  abd_ditherVL = 0;
  abd_ditherAR = 0;
  abd_ditherVR = 0;




  if(abs(abd_speedRd) > abs(abd_speedLd))
  {
    //abd_speedLimitL = abd_speedLimit * abs(abd_speedLd) / abs(abd_speedRd);
    abd_rampStepL = abd_rampStep * abs(abd_speedLd) / abs(abd_speedRd);

    abd_ditherAL = (abd_rampStep * abd_speedLd) % abs(abd_speedRd);
    abd_ditherAL *= 50;
    abd_ditherAL /= abs(abd_speedRd);
    abd_ditherAL = abs(abd_ditherAL);
  }          
  //else if(abs(abd_distL) > abs(abd_distR))
  else if(abs(abd_speedLd) > abs(abd_speedRd))
  {
    //abd_speedLimitR = abd_speedLimit * abs(abd_distR) / abs(abd_distL);
    abd_rampStepR = abd_rampStep * abs(abd_speedRd) / abs(abd_speedLd);

    abd_ditherAR = (abd_rampStep * abd_speedRd) % abs(abd_speedLd);
    abd_ditherAR *= 50;
    abd_ditherAR /= abs(abd_speedLd);
    abd_ditherAR = abs(abd_ditherAR);
    //print("ditherAR = %d, ditherVR = %d\r", abd_ditherAR, abd_ditherVR);  
  }
  /*
  else
  {
    //abd_speedLimitR = abd_speedLimit;
    //abd_speedLimitL = abd_speedLimit;
    abd_rampStepL = abd_rampStep;
    abd_rampStepR = abd_rampStep;
    abd_ditherAL = 0;
    abd_ditherVL = 0;
    abd_ditherAR = 0;
    abd_ditherVR = 0;
    //print("ditherAL = %d, ditherVL = %d\r", abd_ditherAL, abd_ditherVL);  
    //print("ditherAR = %d, ditherVR = %d\r", abd_ditherAR, abd_ditherVR);  
  }   
  */
  
  //abd_ditherVL = 0;
  //abd_ditherVR = 0;


  /*
  abd_ditherALa = 0;
  abd_ditherARa = 0;
  abd_ditherALd = 0;
  abd_ditherARd = 0;
  abd_ditherALp = 0;
  abd_ditherARp = 0;
  
  abd_ditherVLa = 0;
  abd_ditherVRa = 0;
  abd_ditherVLd = 0;
  abd_ditherVRd = 0;
  abd_ditherVLp = 0;
  abd_ditherVRp = 0;
  
  abd_gotoFlagL = 0;
  abd_gotoFlagR = 0;
  abd_dvFlagL = 1;
  abd_dvFlagR = 1;
  */

  /*
    abd_speedLimitL = abd_speedLimit * abd_distL / abs(abd_distR);
    abd_rampStepL = abd_rampStep * abd_distL / abs(abd_distR);
  */
  #ifdef _monitor_
  sprint(
        abd_str, "\rvL%d, rspdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d | "\
        "vR%d, spdLimR=%d, rmpStpR=%d dthrAR=%d, dthrVR=%d\r\r",
        abd_speedLT, abd_speedLimitL, abd_rampStepL, abd_ditherAL, abd_ditherVL,
        abd_speedRT, abd_speedLimitR, abd_rampStepR, abd_ditherAR, abd_ditherVR
        );
  #endif       

  if(!cog)
  {
    /////print("\n\n!!!!! Starting COG !!!!!!\n\n");
    cog = 1 + cogstart(encoders, NULL, stack, sizeof(stack)-1);
  }

  //
  if(abd_stopCtrL || abd_stopCtrR)
  {
    while(abd_stopCtrL || abd_stopCtrR);
  }        
  //int n = _servoPulseReps + 6;
  int n = _servoPulseReps + 6;
  while(_servoPulseReps != n);
  if(abd_stopCtrL || abd_stopCtrR)
  {
    while(abd_stopCtrL || abd_stopCtrR);
  }        
  //
  
  /*
  if(abd_stopCtrL || abd_stopCtrR)
  {
    while(abd_stopCtrL || abd_stopCtrR);
  }  
  */
  /*      
  int n = _servoPulseReps + 6;
  while(_servoPulseReps != n)
  {
    if(abd_stopCtrL || abd_stopCtrR)
    {
      while(abd_stopCtrL || abd_stopCtrR);
    }        
  } 
  */   
}


void drive_speed(int left, int right)        // driveSpeeds function
{
  if(!abd_intTabSetup)
  {
    interpolation_table_setup();
    set_drive_speed(0, 0);
    //pause(100);
  }
  
  if((left != speedLprev) || (right != speedRprev))
  {
  
    set_drive_speed(left, right);
    
    //speedLprev = abd_speedLT;
    //speedRprev = abd_speedRT;
  }    

  //speedLprev = abd_speedL;
  //speedRprev = abd_speedR;

  //speedLprev = left;
  //speedRprev = right;
  
  speedLprev = abd_speedLT;
  speedRprev = abd_speedRT;
}


void drive_goto(int left, int right)
{
  
  if(abd_speedLimit > 64) 
  {
    abd_speedLimitTemp = abd_speedLimit;
    abd_speedLimit = 64;
  }    

  //sprint("\r\r\rdrive_goto(%d, %d)\r\r", left, right);
  if(!abd_intTabSetup)
  {
    interpolation_table_setup();
    set_drive_speed(0, 0);
  }
  
  abd_distL = left;
  abd_distR = right;

  if(abs(abd_ticksLf - abd_ticksL) < 6)
  {
    abd_ticksLi = abd_ticksLf;
  }
  else
  {
    abd_ticksLi = abd_ticksL;
  }        

  if(abs(abd_ticksRf - abd_ticksR) < 6)
  {
    abd_ticksRi = abd_ticksRf;
  }
  else
  {
    abd_ticksRi = abd_ticksR;
  }        

  //abd_ticksRi = abd_ticksR;
  abd_ticksLf = abd_ticksLi + left;
  abd_ticksRf = abd_ticksRi + right;
  
  
  
  
  
  
    /*
    abd_speedLimitR = abd_speedLimit;
    abd_speedLimitL = abd_speedLimit;
    abd_rampStepL = abd_rampStep;
    abd_rampStepR = abd_rampStep;
    abd_ditherAL = 0;
    abd_ditherVL = 0;
    abd_ditherAR = 0;
    abd_ditherVR = 0;
    */
  
  
  
    abd_speedLimitR = abd_speedLimit;
    abd_speedLimitL = abd_speedLimit;
    abd_rampStepL = abd_rampStep;
    abd_rampStepR = abd_rampStep;
    abd_ditherAL = 0;
    abd_ditherVL = 0;
    abd_ditherAR = 0;
    abd_ditherVR = 0;
  
  
        
  if(abs(abd_distR) > abs(abd_distL))
  {
    abd_speedLimitL = abd_speedLimit * abs(abd_distL) / abs(abd_distR);
    abd_rampStepL = abd_rampStep * abs(abd_distL) / abs(abd_distR);

    abd_ditherAL = (abd_rampStep * abd_distL) % abs(abd_distR);
    abd_ditherAL *= 50;
    abd_ditherAL /= abs(abd_distR);
    abd_ditherAL = abs(abd_ditherAL);

    abd_ditherVL = (abd_speedLimit * abd_distL) % abs(abd_distR);
    abd_ditherVL *= 50;
    abd_ditherVL /= abs(abd_distR);
    abd_ditherVL = abs(abd_ditherVL);
    //print("ditherAL = %d, ditherVL = %d\r", abd_ditherAL, abd_ditherVL);  
  }          
  else if(abs(abd_distL) > abs(abd_distR))
  {
    abd_speedLimitR = abd_speedLimit * abs(abd_distR) / abs(abd_distL);
    abd_rampStepR = abd_rampStep * abs(abd_distR) / abs(abd_distL);

    abd_ditherAR = (abd_rampStep * abd_distR) % abs(abd_distL);
    abd_ditherAR *= 50;
    abd_ditherAR /= abs(abd_distL);
    abd_ditherAR = abs(abd_ditherAR);
    abd_ditherVR = (abd_speedLimit * abd_distR) % abs(abd_distL);
    abd_ditherVR *= 50;
    abd_ditherVR /= abs(abd_distL);
    abd_ditherVR = abs(abd_ditherVR);
    //print("ditherAR = %d, ditherVR = %d\r", abd_ditherAR, abd_ditherVR);  
  }
  //
  else
  {
    abd_speedLimitR = abd_speedLimit;
    abd_speedLimitL = abd_speedLimit;
    abd_rampStepL = abd_rampStep;
    abd_rampStepR = abd_rampStep;
    abd_ditherAL = 0;
    abd_ditherVL = 0;
    abd_ditherAR = 0;
    abd_ditherVR = 0;
    //print("ditherAL = %d, ditherVL = %d\r", abd_ditherAL, abd_ditherVL);  
    //print("ditherAR = %d, ditherVR = %d\r", abd_ditherAR, abd_ditherVR);  
  }
  //   
  
  abd_ditherALa = 0;
  abd_ditherARa = 0;
  abd_ditherALd = 0;
  abd_ditherARd = 0;
  abd_ditherALp = 0;
  abd_ditherARp = 0;
  
  abd_ditherVLa = 0;
  abd_ditherVRa = 0;
  abd_ditherVLd = 0;
  abd_ditherVRd = 0;
  abd_ditherVLp = 0;
  abd_ditherVRp = 0;
  
  abd_gotoFlagL = 1;
  abd_gotoFlagR = 1;
  abd_dvFlagL = 0;
  abd_dvFlagR = 0;
  
  abd_ticksGuardL = 0;
  abd_ticksGuardR = 0;

  /*
    abd_speedLimitL = abd_speedLimit * abd_distL / abs(abd_distR);
    abd_rampStepL = abd_rampStep * abd_distL / abs(abd_distR);
  */
  
  //
  #ifdef _monitor         
  if(abd_blockGoto == 1)
  {
    sprint(abd_str, "\r\rddL%d, spdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d | "\
          "ddR%d, spdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d\r\r",
          left, abd_speedLimitL, abd_rampStepL, abd_ditherAL, abd_ditherVL,
          right, abd_speedLimitR, abd_rampStepR, abd_ditherAR, abd_ditherVR
          );// 
  }         
  #endif      
        
  if(abd_blockGoto == 1)
  {
    //19 while((abd_gotoFlagL != 0) || (abd_gotoFlagR != 0));
    while((abd_gotoFlagL != 0) || (abd_gotoFlagR != 0) || (abd_stopCtrL > 0) || (abd_stopCtrR > 0));
    pause(40); //19
    while((abd_gotoFlagL != 0) || (abd_gotoFlagR != 0) || (abd_stopCtrL > 0) || (abd_stopCtrR > 0)); //19
  } 
  #ifdef _monitor         
  sprint(abd_str, "\r\rddL%d, spdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d | "\
        "ddR%d, spdLimR=%d, rmpStpR=%d dthrAR=%d, dthrVR=%d\r\r",
        left, abd_speedLimitL, abd_rampStepL, abd_ditherAL, abd_ditherVL,
        right, abd_speedLimitR, abd_rampStepR, abd_ditherAR, abd_ditherVR
        );// 
  #endif 
  
  if(abd_speedLimitTemp != 0) 
  {
    abd_speedLimit = abd_speedLimitTemp;
    abd_speedLimitTemp = 0;
  }    
}


void encoders(void *par)
{

  _servoPulseReps = 0;
  //int oneshot = 0;

  OUTA &= ~(1 << abd_sPinL); 
  OUTA &= ~(1 << abd_sPinR); 
  DIRA |= 1 << abd_sPinL; 
  DIRA |= 1 << abd_sPinR; 

  pause(20);
  //pause(1);

  int tempL = 0;
  int tempR = 0;
  interpolate2(&tempL, &tempR);  

  PHSA = 0;
  PHSB = 0;
  FRQA = 1;
  FRQB = 1;
  CTRA  = abd_sPinL | (4 << 26);
  CTRB  = abd_sPinR | (4 << 26);
   
  phsL = (1500 + tempL);
  phsR = (1500 - tempR);
  phsLr = phsL;
  phsRr = phsR;

  int t = CNT;
  int dt1 = 13*(CLKFREQ/1000);
  int dt2 = 7*(CLKFREQ/1000);

  phsL = phsLr;
  phsR = phsRr;
  PHSA = -phsL*abd_us;
  PHSB = -phsR*abd_us;
  //waitcnt(t+=dt1);
  //waitcnt(t+=dt);
  _servoPulseReps++;
  //waitcnt(t+=dt2);
  //while(1);
  //t+=(dt1+dt2);
  low(12);
  low(13);

  pause(20);
  //pause(1);
  PHSA = -phsL*abd_us;
  PHSB = -phsR*abd_us;

  t+=(dt1+dt2);


  int inc = 0;
  int diff = 0;
  int trimAccum = 0;

  int zdirL = 0;
  int zdirR = 0;

  stateL = (INA >> abd_ePinL) & 1;
  stateR = (INA >> abd_ePinR) & 1;

  while(!_servoPulseReps);

  //int dsrL = 400;                                // distance sample rate
  //int dsrR = 394;                                // distance sample rate
  int tdst = CLKFREQ/abd_dsr;                       // time of distance sample
  int td = CNT + tdst;                          // time of distance
  //int tdsn = 0;                                 // time of distance sample number
  _sprOld = _servoPulseReps;

  abd_edL = 0;                                      // error distance left
  abd_edR = 0;                                      // error distance right

  abd_pL = 0;                                       // proportional left
  abd_pR = 0;                                       // proportional right

  abd_iL = 0;                                   // integral left
  abd_iR = 0;                                   // integral right

  int maxIR = 0;
  int maxIL = 0;

  #ifdef test_t_interval
  int n = 0;
  #endif

  // Main control system loop.

  while(1)
  {  
    // Measure left encoder ticks
    if(((INA >> abd_ePinL) & 1) != stateL)
    {
      stateL = (~stateL) & 1;
      if(stateL == 1) 
      {
        if((CNT - tiL) > (CLKFREQ/400))
        {
          tiL = CNT;
        }  
      }
      if(phsL > cntrLval + 1500)
      {
        abd_ticksL++;
        zdirL = 1;
      }
      else if(phsL < cntrLval + 1500)
      {
        abd_ticksL--;
        zdirL = -1;
      }
      else
      {
        abd_ticksL += zdirL;
      }
    }
    
    // Measure right encoder ticks
    if(((INA >> abd_ePinR) & 1) != stateR)
    {
      stateR = (~stateR) & 1;
      if(stateR == 1) 
      {
        if((CNT - tiR) > (CLKFREQ/400))
        {
          tiR = CNT;
        }  
      }
      if(phsR < 1500 - cntrRval)
      {
        abd_ticksR++;
        zdirR = 1;
      }
      else if(phsR > 1500 - cntrRval)
      {
        abd_ticksR--;
        zdirR = -1;
      }
      else
      {
        abd_ticksR += zdirR;
      }
    }
 

    // Calculated distance accumulator

    if((td - CNT) >= tdst) 
    {
      td += tdst;                                     // Reset sample timer         '
      
      #ifdef test_t_interval
        if( (n*4) < (sizeof(rec_t)-8) )
          rec_t[n++] = CNT;  
      #endif

      //  Every sampling rate x per second d*c is the calculated distance:
      //    accumulator add number ot ticks per second you want the wheel to turn
      //    calculated = accumulator / sampling rate
      //  In other words, if you are adding the number of ticks per second you want
      //  at a rate of 400x/second, you'll need to divide that accumulated value by
      //  400.

      // distance calculated (accumulated) += encoder ticks per second requested  
      //abd_dlca += etpsL;                              // + velocityL for dt
      //abd_drca += etpsR;                              // + velocityR for dt
      abd_dlca += abd_speedL;                              // + velocityL for dt
      abd_drca += abd_speedR;                              // + velocityR for dt
      
      // distance calculated = distance calculated (accumulated) / sampling rate
      abd_dlc = abd_dlca/abd_dsr;                     // ticks expected
      abd_drc = abd_drca/abd_dsr;                             


      // Adjust for trim
      
      //#define test_trim_settings_new
      //#ifdef test_trim_settings_new
      if(trimFunction)
      {
        if((((abd_speedL > 0)&&abd_trimFL))||((abd_speedR > 0)&&(abd_trimFR)))
        {
          trimticks = abd_trimticksF;
          dca = abd_dlca*abd_trimFL + abd_drca*abd_trimFR;
        }
        else if((((abd_speedL < 0)&&abd_trimBL))||((abd_speedR < 0)&&(abd_trimBR)))
        {
          trimticks = abd_trimticksB;
          dca = abd_dlca*abd_trimBL + abd_drca*abd_trimBR;
        }
        if((((abd_speedL > 0)&&abd_trimFL))||((abd_speedR > 0)&&(abd_trimFR)))
        {
          if(dca >= trimAccum)
          {
            diff = dca - trimAccum;
            inc = diff/trimticks;
            dca += inc;
            trimAccum += inc;
            trimAccum += (inc*trimticks);         
          }
          abd_dlca += (abd_trimFL*inc);
          abd_drca += (abd_trimFR*inc);
        }
        else if((((abd_speedL < 0)&&abd_trimBL))||((abd_speedR < 0)&&(abd_trimBR)))
        {
          if(dca <= trimAccum)
          {
            diff = dca - trimAccum;
            inc = diff/trimticks;
            dca += inc;
            trimAccum += inc;
            trimAccum += (inc*trimticks);         
          }
          abd_dlca += (abd_trimBL*inc);
          abd_drca += (abd_trimBR*inc);
        }
      }
    }
      


    // Calculate and deliver servo pulses. 
    if((CNT - t) >= (dt1 + dt2))
    {
      t+=(dt1+dt2);
      //oneshot = 0;
      //pulseTime = CNT;
      _sprOld = _servoPulseReps;
      pcount++;


      // Dither on acceleration and velocity coefficients for the sake of not
      // using floating point.  *d terms spend a certain number of 50ths at a 
      // value of 1 proportional to the truncation loss during integer division.
      if((abd_gotoFlagL != 0) || (abd_gotoFlagR != 0)
          || (abd_dvFlagL != 0) || (abd_dvFlagR != 0))
      {
        abd_ditherALa += abd_ditherAL;
        abd_ditherALd = (abd_ditherALa/50) - (abd_ditherALp/50);
        abd_ditherALp = abd_ditherALa;
        
        abd_ditherARa += abd_ditherAR;
        abd_ditherARd = (abd_ditherARa/50) - (abd_ditherARp/50);
        abd_ditherARp = abd_ditherARa;
      }

      if((abd_gotoFlagL != 0) || (abd_gotoFlagR != 0))
      {
        abd_ditherVLa += abd_ditherVL;
        abd_ditherVLd = (abd_ditherVLa/50) - (abd_ditherVLp/50);
        abd_ditherVLp = abd_ditherVLa;
        
        abd_ditherVRa += abd_ditherVR;
        abd_ditherVRd = (abd_ditherVRa/50) - (abd_ditherVRp/50);
        abd_ditherVRp = abd_ditherVRa;
      }


      // Set velocities if executing a goto
      if(abd_gotoFlagL == 1)
      {
        // Calculate velocity and acceleration based on distance remaining.
        if(abd_speedL != 0)
        {
          // dist = v^2 / 2a
          // !!!!! Dithering needs to be absent from abd_speedL here !!!!!!
          //abd_ticksGuardL = (abd_speedL * abs(abd_speedL)) / (100 * abd_rampStepL);
          abd_ticksGuardL = (abd_speedL * abs(abd_speedL)) / (100 * abd_rampStepL);
          //abd_ticksGuardL = abd_speedL/abd_rampStepL;
        }          
        //if(abs(abd_ticksLf - abd_ticksL) > abs(abd_ticksGuardL))    //18
        if(abs(abd_ticksLf - abd_ticksL) > ((abs(abd_ticksGuardL) + abs(abd_ditherVLd))))   //18
        {
          if(abd_ticksLf > abd_ticksL)
          {
            abd_speedLT = abd_speedLimitL + abd_ditherVLd;
          }
          else if(abd_ticksLf < abd_ticksL)
          {
            abd_speedLT = -abd_speedLimitL - abd_ditherVLd;
          }
        }            
        else
        {
          abd_speedLT = 0;
          abd_gotoFlagL = 2;
        }          
      }

      if(abd_gotoFlagR == 1)
      {
        // Calculate velocity and acceleration based on distance remaining.
        if(abd_speedR != 0)
        {
          // dist = v^2 / 2a
          // !!!!! Dithering needs to be absent from abd_speedR here !!!!!!
          //abd_ticksGuardR = (abd_speedR * abs(abd_speedR)) / (100 * abd_rampStepR);
          abd_ticksGuardR = (abd_speedR * abs(abd_speedR)) / (100 * abd_rampStepR);
          //abd_ticksGuardR = abd_speedR / abd_rampStepR;
        }          
        // if(abs(abd_ticksRf - abd_ticksR) > (abs(abd_ticksGuardR)) //18
        if(abs(abd_ticksRf - abd_ticksR) > (abs(abd_ticksGuardR) + (abs(abd_ditherVRd))))  //18 
        {
          if(abd_ticksRf > abd_ticksR)
          {
            abd_speedRT = abd_speedLimitR + abd_ditherVRd;
          }
          else if(abd_ticksRf < abd_ticksR)
          {
            abd_speedRT = -abd_speedLimitR - abd_ditherVRd;
          }
        }            
        else
        {
          abd_speedRT = 0;
          abd_gotoFlagR = 2;
        }          
      }



      // Nudge to final position
      //if((abd_gotoFlagL == 2) && (abd_stopCtrL == 0) && (abd_speedL == 0)) //18
      if((((abd_gotoFlagL == 2) && (abd_stopCtrL == 0) && (abd_speedL == 0) && (abd_speedLold == abd_speedL))) || (((abd_gotoFlagL == 3) && (abd_stopCtrL == 0))))
      {
        abd_distErrorL = abd_ticksLf - abd_ticksL;
        if(abd_distErrorL == 0)
        {
          abd_gotoFlagL = 0;
          abd_nudgeCtrL = 0;
          abd_speedL = 0; //18
        }
        else
        { 
          abd_nudgeCtrL++;
          signL = abs(abd_distErrorL) / abd_distErrorL;
          //abd_speedL = signL * (abd_nudgeIncL + (2 * abd_nudgeCtrL));
          //abd_speedL = signL * (10);
          //abd_speedL = signL * (abd_rampStepL + (abd_rampStepL * abs(abd_distErrorL)));
          //abd_speedL = signL * 35;
          //19 abd_speedL = (signL * 10) + (signL * abd_rampStepL);
          abd_speedL = (signL * 10);
          abd_gotoFlagL = 3; //18
        }          
      }
        
      //18 if((abd_gotoFlagR == 2) && (abd_stopCtrR == 0) && (abd_speedR == 0))
      if((((abd_gotoFlagR == 2) && (abd_stopCtrR == 0) && (abd_speedR == 0) && (abd_speedRold == abd_speedR))) || (((abd_gotoFlagR == 3) && (abd_stopCtrR == 0))))
      {
        abd_distErrorR = abd_ticksRf - abd_ticksR;
        if(abd_distErrorR == 0)
        {
          abd_gotoFlagR = 0;
          abd_nudgeCtrR = 0;
          abd_speedR = 0; //18
        }
        else
        { 
          abd_nudgeCtrR++;
          int signR = abs(abd_distErrorR) / abd_distErrorR;
          //abd_speedR = signR * (abd_nudgeIncR + (2 * abd_nudgeCtrR));
          //abd_speedR = signR * (abd_rampStepR + (abd_rampStepR * abs(abd_distErrorR)));
          //abd_speedR = signR * 35;
          //19 abd_speedR = (signR * 10) + (signR * abd_rampStepR);
          abd_speedR = (signR * 10);
          abd_gotoFlagR = 3; //18
        }          
      }


      // Clamp encoded speed
      if(abd_speedLT > abd_speedLimit) abd_speedLT = abd_speedLimit;
      if(abd_speedLT < -abd_speedLimit) abd_speedLT = -abd_speedLimit;
      if(abd_speedRT > abd_speedLimit) abd_speedRT = abd_speedLimit;
      if(abd_speedRT < -abd_speedLimit) abd_speedRT = -abd_speedLimit;


      // If new abd_speedLT/RT set point, calculate abd_speedL/R step toward each 
      // abd_speedLT/RT in steps.
      //18 if(abd_stopCtrL == 0)
      if((abd_stopCtrL == 0) && (abd_gotoFlagL != 3))
      {
        if(abd_speedLT > (abd_speedL + abd_rampStepL))
        {
          abd_speedL = abd_speedL + abd_rampStepL + abd_ditherALd;
        }          
        else if(abd_speedLT < (abd_speedL - abd_rampStep)) 
        {
          abd_speedL = abd_speedL - abd_rampStepL - abd_ditherALd;
        }          
        else abd_speedL = abd_speedLT;
      }    
      
      //18 if(abd_stopCtrR == 0)
      if((abd_stopCtrR == 0) && (abd_gotoFlagR != 3))
      {
        //if(abd_speedRT > (abd_speedR + abd_rampStep + abd_ditherARd)) 
        if(abd_speedRT > (abd_speedR + abd_rampStepR)) 
        {
          abd_speedR = abd_speedR + abd_rampStepR + abd_ditherARd;
        }          
        //else if(abd_speedRT < (abd_speedR - abd_rampStep - abd_ditherARd)) 
        else if(abd_speedRT < (abd_speedR - abd_rampStepR)) 
        {
          abd_speedR = abd_speedR - abd_rampStepR - abd_ditherARd;
          //abd_speedR = abd_speedR - abd_rampStepR;// - abd_ditherARd;
        }          
        else
        {
          abd_speedR = abd_speedRT;
          //if(abd_speedRT == 128) high(26);
        }          
        
        //sprint(abd_str, "else");
      }  
            
      
      if( (abd_speedLold != abd_speedL) && (abd_speedL == 0) )
      {
        abd_stopCtrL = abd_stopPulseRepsL;
      }        

      if( (abd_speedRold != abd_speedR) && (abd_speedR == 0) )
      {
        abd_stopCtrR = abd_stopPulseRepsR;
      }   
      
      abd_speedLold = abd_speedL;     
      abd_speedRold = abd_speedR;

      // Figure out next drive setting
      int leftTemp  = abd_speedL;
      int rightTemp = abd_speedR;

      interpolate2(&leftTemp, &rightTemp);

      ssiL = leftTemp;                      // servo speed interpolated
      ssiR = -rightTemp;


      // Calculate distance error, then respond with PI control.
      // Distance is accumulated at 400 Hz
      if(encoderFeedback)
      {
        // Error ticks = calculated - measured 
        abd_edL = abd_dlc - abd_ticksL;
        abd_eaL += abd_edL;
        if(abd_speedL != 0)
        {
          //iL += edL;
          if(abd_speedL > 0)
          {
            abd_pL = abd_edL * (3+(abd_speedL/10));  
            if(abd_edL>0)abd_iL+=1; else if(abd_edL<0) abd_iL-=1;
          }
          else if(abd_speedL < 0)
          {
            abd_pL = abd_edL * (-3+(abd_speedL/10));  
            if(abd_edL>0)abd_iL-=1; else if(abd_edL<0) abd_iL+=1;
          }

          maxIL = abd_speedL;
          if(maxIL < 0) maxIL = -maxIL;
          if(abd_iL > maxIL) abd_iL = maxIL;
          if(abd_iL < -maxIL) abd_iL = -maxIL;

          if(abd_speedL > 0)
            driveL = abd_iL + abd_pL + ssiL + 1500;
          if(abd_speedL < 0)
            driveL = -abd_iL - abd_pL + ssiL + 1500;
        }
        else
        {
          driveL = ssiL + 1500;
          abd_iL = 0;
        }

        // Error ticks = calculated - measured 
        abd_edR = abd_drc - abd_ticksR;
        abd_eaR += abd_edR;
        
        // Control system calcs
        if(abd_speedR != 0)
        {
          // Calculate proportional and integral terms
          if(abd_speedR > 0)
          {
            abd_pR = abd_edR * (3+(abd_speedR/10));  
            if(abd_edR>0)abd_iR+=1; else if(abd_edR<0) abd_iR-=1;
          }
          else if(abd_speedR < 0)
          {
            abd_pR = abd_edR * (-3+(abd_speedR/10));  
            if(abd_edR>0)abd_iR-=1; else if(abd_edR<0) abd_iR+=1;
          }

          // Clamp integral term
          maxIR = abd_speedR;
          if(maxIR < 0) maxIR = - maxIR;
          if(abd_iR > maxIR) abd_iR = maxIR;
          if(abd_iR < -maxIR) abd_iR = -maxIR;

          // servoDrive = (servo speed interpolated + 1500) +/- integral +/- proportionial
          if(abd_speedR > 0)
            driveR = -abd_iR - abd_pR + ssiR + 1500;
          if(abd_speedR < 0)
            driveR = abd_iR + abd_pR + ssiR + 1500;
        }
        else
        {
          driveR = ssiR + 1500;
          abd_iR = 0;
        }

        phsLr = driveL; 
        phsRr = driveR; 

      }
      else // if(!encoder_feedback)
      {
        phsLr = ssiL + 1500;
        phsRr = ssiR + 1500;
      }

      phsL = phsLr;
      phsR = phsRr;
      
      if(abd_speedL != 0)
      {
        PHSA = -phsL*abd_us;
      }        
      else
      {
        PHSA = 0;
        if(abd_stopCtrL > 0)
          abd_stopCtrL--;
        if(abd_stopCtrL == 0)
        {
          abd_edL = 0;
          //abd_dlc = 0;
          abd_eaL = 0;
          abd_dlc = abd_ticksL;
          abd_dlca = abd_dlc * 400;
          //abd_gotoFlagL = 0;
        }           
      }         
      if(abd_speedR != 0)
      {
        PHSB = -phsR*abd_us;
      }        
      else
      {
        PHSB = 0;  
        if(abd_stopCtrR > 0)
          abd_stopCtrR--;
        if(abd_stopCtrR == 0)
        {
          abd_edR = 0;
          //abd_drc = 0;
          abd_eaR = 0;
          abd_drc = abd_ticksR;
          abd_drca = abd_drc * 400;
          //abd_gotoFlagR = 0;
        }           
      }
              
      _servoPulseReps++;

      //if(record)
      #ifdef interactive_development_mode
      if(record)
      {
        //rv[ridx] = dlc;
        rv[ridx+0] = speedL;
        rv[ridx+1] = dlc;
        rv[ridx+2] = ticksL;
        rv[ridx+3] = edL;
        rv[ridx+4] = pL;
        rv[ridx+5] = iL;
        //rv[ridx+5] = phsLr;
        rv[ridx+6] = drc;
        rv[ridx+7] = ticksR;
        rv[ridx+8] = edR;
        rv[ridx+9] = pR;
        rv[ridx+10] = iR;
        //rv[ridx+10] = phsRr;
        ridx += 11;
      }
      #endif // interactive_development_mode
    }
  }
}




