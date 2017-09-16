#include "simpletools.h"  
#include "servo360.h"

#define ABD60_PIN_CTRL_L 12
#define ABD60_PIN_FB_L 14

#define ABD360_PIN_CTRL_R 13
#define ABD360_PIN_FB_R 15

#define ABD360_UNITS_REV 64

#define ABD360_GOTO_BUSY 1
#define ABD360_GOTO_CLEAR 0

#define ABD360_GOTO_BLOCK 0
#define ABD360_GOTO_SET_FORGET 1

#define ABD_RAMP_STEP 12
#define ABD_SPEED_LIMIT 128
#define ABD_GOTO_SPEED_LIMIT 64
#define ABD_GOTO_RAMP_STEP 4

#define AB360_NEITHER 0
#define AB360_LEFT 1
#define AB360_RIGHT 2

//#define ABD_NUDGE_SPEED 4
//#define ABD_STOP_50ths 5

#define FOR_GOTO 1
#define FOR_SPEED 0
#define OFF 0
#define ON  1
#define SIDE_LEFT 0
#define SIDE_RIGHT 1
#define SIDE_BOTH 2


// Functions drafted
void drive_goto(int distLeft, int distRight);
void drive_speed(int left, int right); 

void drive_getTicks(int *left, int *right);

void drive_calibrationResults(void);

void drive_getTicksCalc(int *left, int *right);

int drive_gotoStatus(int side);

void drive_encoderPins(int encPinLeft, int encPinRight);

void drive_feedback(int enabled); 

void drive_gotoMode(int mode);

void drive_servoPins(int servoPinLeft, int servoPinRight);

void drive_setAcceleration(int forGotoOrSpeed, int ticksPerSecSq);

void drive_setErrorLimit(int maxDistDiffTicks);

void drive_setMaxSpeed(int speed);

void drive_setMaxVelocity(int forGotoOrSpeed, int ticksPerSec);

void drive360_ticksPerRev(int units);

void drive_setRampStep(int stepsize);

void drive_rampStep(int left, int right);

void drive_ramp(int left, int right);

