#include "simpletools.h"  
#include "abdrive360.h"


int main()
{
  //int state = servo360_setMaxSpeed(12, 180);
  //  print("speedLimit = %d\r", speedLimit);
  
  //servo360_setramp(12, 2);
  //  print("rampStep = %d\r", rampStep);
  
  //drive_goto(0, 0);

  pause(100);
  
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 
  
  drive_speed(0, 0);
  pause(1000);
  
  /*
  drive_speed(64, 64);
  pause(2000);
  drive_speed(-64, -64);
  pause(2000);
  drive_speed(0, 0);
  
  pause(2000);
  */

  drive_goto(128, 128);
  drive_goto(-128, -128);
  drive_goto(51, -51);
  drive_goto(-51, 51);
  drive_goto(192, 128);
  drive_goto(-192, -128);
  drive_goto(128, 192);
  drive_goto(-128, -192);
  
  while(1);  


  servo360_connect(12, 14);
  servo360_connect(13, 15);
  
  
  fb360_setRampStep(12, 256); 
  fb360_setRampStep(13, 256); 
  
  fb360_setMaxSpeed(12, 4096);
  fb360_setMaxSpeed(13, 4096);
 
  
  int distL = 720;
  int distR = -540;
  print("All Done!!!");  
  while(1);

  
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 

  servo360_speed(12, 0);
  servo360_speed(13, 0);

  pause(1000); 
   
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif 


  servo360_goto(12, 1080);
  servo360_goto(13, -1080);
  
  pause(5000);

  servo360_goto(12, -1080);
  servo360_goto(13, 1080);
  
  pause(5000);

  servo360_goto(12, 142);
  servo360_goto(13, 142);
  
  pause(3000);

  servo360_goto(12, -142 * 2);
  servo360_goto(13, -142 * 2);
  
  pause(3000);

  servo360_goto(12, 142);
  servo360_goto(13, 142);
  
  #ifdef _console_
    suppressFbDisplay = 1;
  #endif 
  while(1);
  
  int angle0 = fb[0].angle;
  int angleFixed0 = fb[0].angleFixed;
  int pvOffset0 = fb[0].pvOffset;
  print("angle0 = %d, angleFixed0 %d, pvOffset0 %d,\r", angle0, angleFixed0, pvOffset0);
  pause(80);
  angle0 = fb[0].angle;
  angleFixed0 = fb[0].angleFixed;
  pvOffset0 = fb[0].pvOffset;  
  print("angle0 = %d, angleFixed0 %d, pvOffset0 %d,\r", angle0, angleFixed0, pvOffset0);

  int angle1 = fb[1].angle;
  int angleFixed1 = fb[1].angleFixed;
  int pvOffset1 = fb[1].pvOffset;
  print("angle1 = %d, angleFixed1 %d, pvOffset1 %d,\r\r", angle1, angleFixed1, pvOffset1);
  pause(80);
  angle1 = fb[1].angle;
  angleFixed1 = fb[1].angleFixed;
  pvOffset1 = fb[1].pvOffset;
  print("angle1 = %d, angleFixed1 %d, pvOffset1 %d,\r\r", angle1, angleFixed1, pvOffset1);

  /*
  while(1) 
  {
    print("angle0 = %d, angleFixed0 %d, pvOffset0 %d,\r", angle0, angleFixed0, pvOffset0);
    print("angle1 = %d, angleFixed1 %d, pvOffset1 %d,\r\r", angle1, angleFixed1, pvOffset1);
    pause(50);
  }    
  */

  servo360_angle(12, 180);
  pause(20);
  servo360_angle(13, -180);
  
  pause(2000);
  
  servo360_angle(12, -180);
  pause(20);
  servo360_angle(13, 180);
  
  pause(2000);
 
  print("devCount %d\r", devCount);
  print("ctrl %d, fb %d\r", fb[0].pinCtrl, fb[0].pinFb);
  print("ctrl %d, fb %d\r", fb[1].pinCtrl, fb[1].pinFb);
  print("devCount %d\r", devCount);
  
  servo360_speed(12, 0);
  servo360_speed(13, 0);
  //while(1);
  servo360_speed(12, 360);
  servo360_speed(13, -360);
  pause(3000);
  servo360_speed(12, -360);
  servo360_speed(13, 360);
  pause(3000);
  servo360_speed(12, 0);
  servo360_speed(13, 0);
  pause(1000);
  servo360_speed(12, -180);
  servo360_speed(13, -180);
  pause(1000);
  servo360_speed(12, 180);
  servo360_speed(13, 180);
  pause(1000);
  servo360_speed(12, 0);
  servo360_speed(13, 0);
  
  /*
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 
  */
  while(1)
  {
    print("angle = %d\r", fb[0].angle);
    print("angle = %d\r\r", fb[1].angle);
    pause(500);
    #ifdef _console_
      suppressFbDisplay = 0;
    #endif 
  }    
  
  servo360_speed(12,0);
  while(1);

  servo360_speed(12, 180);
  
  pause(100);
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 
  
  //servo360_speed(12, 180);

  pause(2000);
  
  //servo360_speed(12, 180);
  //print("\r\rrequested = %d\r\r", fb[0].speedReq);
  
  //servo360_speed(12, 0);
 
  //print("\r\rcsop = %d\r\r", fb[0].csop);
  pause(2000);
  
  servo360_speed(12, 0);

  while(1)
  {
    pause(500);
    //print("angle: %d\r", fb[0].angle);
  }    

  #ifdef _console_
    console_start();
    suppressFbDisplay = 1;
  #endif 
  //servo360_speed(12, 0);
  //pause(1000);
  servo360_speed(12, 180);
  pause(1000);
  fb[0].speedReq = 2048;
  #ifdef _console_
    suppressFbDisplay = 1;
    pause(1000);
    dprint(term, "\r\rrequested = %d\r\r", fb[0].speedReq);
    dprint(term, "\r\rpinCtrl = %d\r\r", fb[0].pinCtrl);
    dprint(term, "\r\rpinFb = %d\r\r", fb[0].pinFb);
    pause(1000);
    suppressFbDisplay = 1;
  #endif
  pause(1000);
  servo360_speed(12, 0);
  pause(1000);
  #ifdef _console_
    suppressFbDisplay = 1;
  #endif
  while(1);
  
  pause(1000);
  #ifdef _console_
    dprint(term, "speedLimit = %d\r", fb[0].speedLimit);
  #endif
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(1000);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 1080);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(3000);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, -1080);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(4000);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 0);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(1000);  
  
  
  
  #ifdef _console_
    suppressFbDisplay = 1;
  #endif  
  
/*  
  int state = servo360_setMaxSpeed(12, 180);
//  print("speedLimit = %d\r", speedLimit);
  
  servo360_setramp(12, 2);
//  print("rampStep = %d\r", rampStep);
  
  #ifdef _console_
    console_start();
  #endif 
  pause(1000);
  #ifdef _console_
    dprint(term, "speedLimit = %d\r", fb[0].speedLimit);
  #endif
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(1000);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 1080);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(3000);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, -1080);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(4000);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 0);
  #ifdef _console_
    suppressFbDisplay = 0;
  #endif
  pause(1000);  
  
  
  
  #ifdef _console_
    suppressFbDisplay = 1;
  #endif
*/

  //fb360_run();
  /*
  console_start(); 
  suppressFbDisplay = 0;
  servo360_speed(12, 0);
  pause(500);
  servo360_angle(12, 0); 
  pause(500);
  servo360_speed(12, 120);
  pause(1500);
  servo360_angle(12, 150);
  pause(1500);
  servo360_speed(12, -120);
  pause(1500);
  servo360_angle(12, 0);
  pause(1500);
  
  suppressFbDisplay = 1;
  */


  /*
  console_start(); 
  suppressFbDisplay = 0;
  servo360_speed(12, 0);
  pause(500);
  servo360_goto(12, 720);
  while(csop == GOTO); 
  pause(500);
  servo360_goto(12, 0);
  while(csop == GOTO); 
  pause(500);
  suppressFbDisplay = 1;
  */


  /*
  servo360_speed(12, 0);
  console_start(); 
  suppressFbDisplay = 0;
  pause(1000);
  suppressFbDisplay = 0;
  servo360_speed(12, 180);
  suppressFbDisplay = 0;
  pause(3000);
  suppressFbDisplay = 0;
  servo360_speed(12, 0);
  suppressFbDisplay = 0;
  pause(1000);
  suppressFbDisplay = 0;
  servo360_speed(12, -180);
  suppressFbDisplay = 0;
  pause(3000);
  suppressFbDisplay = 0;
  servo360_speed(12, 0);
  suppressFbDisplay = 0;
  pause(1000);  
  
  
  
  suppressFbDisplay = 1;
  */


  
  /*
  servo360_speed(12, 0);
  console_start(); 
  suppressFbDisplay = 0;
  pause(1000);
  suppressFbDisplay = 0;
  servo360_speed(12, 180);
  suppressFbDisplay = 0;
  pause(3000);
  suppressFbDisplay = 0;
  servo360_speed(12, -180);
  suppressFbDisplay = 0;
  pause(4000);
  suppressFbDisplay = 0;
  servo360_speed(12, 0);
  suppressFbDisplay = 0;
  pause(1000);  
  */
  
  
  //
  
  
  //servo360_setramp(12, 2);
  
  
  //


  
  /*
  servo360_speed(12, -180);
  suppressFbDisplay = 0;
  pause(3000);
  suppressFbDisplay = 0;
  servo360_speed(12, 0);
  suppressFbDisplay = 0;
  pause(100);
  suppressFbDisplay = 1;
  
  /*
  servo360_angle(12, 90);
  pause(2000);
  servo360_angle(12, 0);
  pause(2000);
  servo360_speed(12, 0);
  pause(2000);
  servo360_speed(12, 120);
  pause(2000);
  servo360_speed(12, -120);
  pause(2000);
  servo360_speed(12, 0);
  */  

  //while(1);
} 










