#include "abdrive.h"

volatile int abd_ticksL;
volatile int abd_ticksR;
volatile int abd_dlc;      // distance left calculated
volatile int abd_drc;      // distance right calculated

void drive_getTicks(int *left, int *right)
{
  *left = abd_ticksL;
  *right = abd_ticksR;
}

void drive_getTicksCalc(int *left, int *right)
{
  *left = abd_dlc;
  *right = abd_drc;
}
