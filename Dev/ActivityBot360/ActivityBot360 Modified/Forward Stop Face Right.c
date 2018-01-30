/* 
  Forward Stop Face Right.c

  http://learn.parallax.com/activitybot/go-certain-distances
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  /*
  for(int n = 0; n < 4; n++)
  {
    drive_speed(50, 50);
    pause(200);
    //drive_speed(0, 0);
    //pause(200);
    drive_goto(26, -25);
  }    

  for(int n = 0; n < 4; n++)
  {
    drive_speed(50, 50);
    pause(200);
    drive_speed(0, 0);
    pause(200);
    drive_goto(26, -25);
  }  
  */  

  for(int n = 0; n < 4; n++)
  {
    drive_goto(25, 25);
    drive_speed(-20, 20);
    pause(200);
    drive_speed(0, 0);
    pause(200);
  }    
}