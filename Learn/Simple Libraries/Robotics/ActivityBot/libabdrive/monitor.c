#include "abdrive.h"                   // Include servo lib funct defs
#include "simpletools.h"
#include "simpletext.h"
#include "fdserial.h"
#include <string.h>

//#define _monitor_


#ifdef _monitor_
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
volatile int abd_trimticksF;
volatile int abd_trimticksB;
int abd_eeAddr;

volatile int abd_aL;                                        // Acceleration in ticks/(s^2)
volatile int abd_aR;

volatile int abd_speedLold;
volatile int abd_speedRold;
volatile int abd_stopCtrL;
volatile int abd_stopCtrR;
volatile int abd_stopPulseRepsL;
volatile int abd_stopPulseRepsR;

// drive_goto
volatile int abd_ticksL;                                // Measured distance left/right
volatile int abd_ticksR;
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


volatile int abd_rampStep;
volatile int abd_rampStepL;
volatile int abd_rampStepR;
volatile int abd_speedLimit;
volatile int abd_speedLimitL;
volatile int abd_speedLimitR;
volatile int abd_ticksGuardL;
volatile int abd_ticksGuardR;


volatile int abd_zeroDelay;

volatile int abd_dlc;                                      // distance left calculated
volatile int abd_drc;                                      // distance right calculated
volatile int abd_dlca;                                 // distance left calculated (accumulated)
volatile int abd_drca;                                 // distance right calculated (accumulated)
volatile int abd_dsr;                                // Distance sampling rate


volatile int abd_edL;                                      // error distance left
volatile int abd_edR;                                      // error distance right
volatile int abd_pL;                                       // proportional left
volatile int abd_pR;                                       // proportional right
volatile int abd_iL;                                       // integral left
volatile int abd_iR;                                       // integral right
volatile int abd_eaL;                                  // Accumulated errors L/R
volatile int abd_eaR;
volatile unsigned int _servoPulseReps;                     // Servo pulse counter

// servoPins
volatile int abd_sPinL, abd_sPinR;   // Global variables
volatile int abd_ePinL, abd_ePinR;
volatile int abd_us;
int abd_intTabSetup;

// debug
volatile int abd_record;               // Record values to an array

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

static int cog;
//static int servoCog2 = 0;
static unsigned int stack[44 + 252];
//static unsigned int servoStack[(160 + (150 * 4)) / 4];


//static int a = 0;
static int r;

//static int intTabSetup = 0;
//static int eeStarted = 0;

static volatile int trimctr;
static volatile int dca, trimticks;

static volatile int leftPrev;
static volatile int  rightPrev;

static volatile int kp[6];

static volatile int tcL;
static volatile int tcR;
static volatile int tiL;


static volatile int ridx;


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

static int trimFunction;
static int encoderFeedback;

static volatile int speedLprev;
static volatile int speedRprev;

volatile int nudgeIncL;
volatile int nudgeIncR;

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

volatile int abd_blockGoto;

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

static int reps;
void monitor(void *par);

void monitor_start(int monitorReps)
{
  reps = monitorReps;
  cog = 1 + cogstart(monitor, NULL, stack, sizeof(stack)-1);
  simpleterm_close();
  pause(10);
}

void monitor_stop()
{
  cogstop(cog - 1);
}

void monitor(void *par)
{
  pause(100);
  simpleterm_open();
  int n = _servoPulseReps;
  while(n < reps)
  {
    while(1)
    {
      if(n != _servoPulseReps)
      {
        n = _servoPulseReps;
        break;
      }
    }      
    if(abd_str[0])
    {
      print("%s", abd_str);
      abd_str[0] = 0;
    }                
    print("n%d\r"\
        "dLf%d dLc%d dL%d sLT%d sL%d tgL%d gtfL%d scL%d"\
        " | "\
        "dRf%d dRc%d dR%d sRT%d sR%d tgR%d gtfR%d scR%d\r"\
        "rsl%d dald%d | rsr%d dalr%d\r",
        _servoPulseReps, 
        abd_ticksLf, abd_dlc, abd_ticksL, abd_speedLT, abd_speedL, abd_ticksGuardL, abd_gotoFlagL, abd_stopCtrL, 
        abd_ticksRf, abd_drc, abd_ticksR, abd_speedRT, abd_speedR, abd_ticksGuardR, abd_gotoFlagR, abd_stopCtrR, 
        abd_rampStepL, abd_ditherALd, abd_rampStepR, abd_ditherARd);
    if(n >= reps) cogstop(cog);    
  }    
}      
#endif
