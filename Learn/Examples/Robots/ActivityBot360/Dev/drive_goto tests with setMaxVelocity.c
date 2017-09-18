#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  drive_setMaxVelocity(FOR_GOTO, 96);

  drive_goto(192, 192);
  drive_goto(-28, 28);
  drive_goto(28 * 2, -28 * 2);
  drive_goto(-28, 28);
  drive_goto(-192, -192);
  
  drive_setMaxVelocity(FOR_GOTO, 32);

  drive_goto(192, 128);
  drive_goto(-192, -128);
  drive_goto(128, 192);
  drive_goto(-128, -192);
}