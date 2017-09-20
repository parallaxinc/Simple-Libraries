#define _console_

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  
  //
  #ifdef _console_
    drive_speed(0, 0);
    console_start();
    suppressFbDisplay = 0;
  #endif 
  //
  
  //drive_goto(0, 0);
  pause(500);
  
  drive_goto(1, 1);
  pause(1500);
  
  drive_goto(-1, -1);
  pause(1500);
  
  drive_goto(-1, -1);
  pause(1500);
  
  drive_goto(1, 1);
  pause(1500);
  
  drive_goto(1, 1);
  pause(1500);
  
  drive_goto(-1, -1);
  pause(1500);
  
  #ifdef _console_
  suppressFbDisplay = 1;
  #endif
  while(1);

  drive_goto(64, 64);
  pause(1500);
  drive_goto(64, 64);
  pause(1500);
  drive_goto(64, 64);
  pause(1500);
  drive_goto(-64, -64);
  pause(1500);
  drive_goto(-64, -64);
  pause(1500);
  drive_goto(-64, -64);
  pause(1500);


  while(1);








  drive_goto(192, 192);
  pause(1500);
  drive_goto(-28, 28);
  pause(1500);
  drive_goto(28 * 2, -28 * 2);
  pause(1500);
  drive_goto(-28, 28);
  pause(1500);
  drive_goto(-192, -192);
  pause(1500);
  
  drive_goto(192, 128);
  pause(1500);
  drive_goto(-192, -128);
  pause(1500);
  drive_goto(128, 192);
  pause(1500);
  drive_goto(-128, -192);
  pause(1500);
}