/*
  @file libabdrive360.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


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
  
  #ifdef _servo360_monitor_
    servo360_monitor_start();
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
  
  
  servo360_setRampStep(12, 256); 
  servo360_setRampStep(13, 256); 
  
  servo360_setMaxSpeed(12, 4096);
  servo360_setMaxSpeed(13, 4096);
 
  
  int distL = 720;
  int distR = -540;
  print("All Done!!!");  
  while(1);

  
  #ifdef _servo360_monitor_
    servo360_monitor_start();
    suppressFbDisplay = 0;
  #endif 

  servo360_speed(12, 0);
  servo360_speed(13, 0);

  pause(1000); 
   
  #ifdef _servo360_monitor_
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
  
  #ifdef _servo360_monitor_
    suppressFbDisplay = 1;
  #endif 
  while(1);
  
  int angle0 = _fbs[0].angle;
  int angleFixed0 = _fbs[0].angleFixed;
  int pvOffset0 = _fbs[0].pvOffset;
  print("angle0 = %d, angleFixed0 %d, pvOffset0 %d,\r", angle0, angleFixed0, pvOffset0);
  pause(80);
  angle0 = _fbs[0].angle;
  angleFixed0 = _fbs[0].angleFixed;
  pvOffset0 = _fbs[0].pvOffset;  
  print("angle0 = %d, angleFixed0 %d, pvOffset0 %d,\r", angle0, angleFixed0, pvOffset0);

  int angle1 = _fbs[1].angle;
  int angleFixed1 = _fbs[1].angleFixed;
  int pvOffset1 = _fbs[1].pvOffset;
  print("angle1 = %d, angleFixed1 %d, pvOffset1 %d,\r\r", angle1, angleFixed1, pvOffset1);
  pause(80);
  angle1 = _fbs[1].angle;
  angleFixed1 = _fbs[1].angleFixed;
  pvOffset1 = _fbs[1].pvOffset;
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
 
  print("devCount %d\r", _fb360c.devCount);
  print("ctrl %d, fb %d\r", _fbs[0].pinCtrl, _fbs[0].pinFb);
  print("ctrl %d, fb %d\r", _fbs[1].pinCtrl, _fbs[1].pinFb);
  print("devCount %d\r", _fb360c.devCount);
  
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
  #ifdef _servo360_monitor_
    servo360_monitor_start();
    suppressFbDisplay = 0;
  #endif 
  */
  while(1)
  {
    print("angle = %d\r", _fbs[0].angle);
    print("angle = %d\r\r", _fbs[1].angle);
    pause(500);
    #ifdef _servo360_monitor_
      suppressFbDisplay = 0;
    #endif 
  }    
  
  servo360_speed(12,0);
  while(1);

  servo360_speed(12, 180);
  
  pause(100);
  #ifdef _servo360_monitor_
    servo360_monitor_start();
    suppressFbDisplay = 0;
  #endif 
  
  //servo360_speed(12, 180);

  pause(2000);
  
  //servo360_speed(12, 180);
  //print("\r\rrequested = %d\r\r", _fbs[0].speedReq);
  
  //servo360_speed(12, 0);
 
  //print("\r\rcsop = %d\r\r", _fbs[0].csop);
  pause(2000);
  
  servo360_speed(12, 0);

  while(1)
  {
    pause(500);
    //print("angle: %d\r", _fbs[0].angle);
  }    

  #ifdef _servo360_monitor_
    servo360_monitor_start();
    suppressFbDisplay = 1;
  #endif 
  //servo360_speed(12, 0);
  //pause(1000);
  servo360_speed(12, 180);
  pause(1000);
  _fbs[0].speedReq = 2048;
  #ifdef _servo360_monitor_
    suppressFbDisplay = 1;
    pause(1000);
    dprint(term, "\r\rrequested = %d\r\r", _fbs[0].speedReq);
    dprint(term, "\r\rpinCtrl = %d\r\r", _fbs[0].pinCtrl);
    dprint(term, "\r\rpinFb = %d\r\r", _fbs[0].pinFb);
    pause(1000);
    suppressFbDisplay = 1;
  #endif
  pause(1000);
  servo360_speed(12, 0);
  pause(1000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 1;
  #endif
  while(1);
  
  pause(1000);
  #ifdef _servo360_monitor_
    //dprint(term, "speedLimit = %d\r", _fbs[0].speedLimit);
  #endif
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(1000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 1080);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(3000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, -1080);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(4000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 0);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(1000);  
  
  
  
  #ifdef _servo360_monitor_
    suppressFbDisplay = 1;
  #endif  
  
/*  
  int state = servo360_setMaxSpeed(12, 180);
//  print("speedLimit = %d\r", speedLimit);
  
  servo360_setramp(12, 2);
//  print("rampStep = %d\r", rampStep);
  
  #ifdef _servo360_monitor_
    servo360_monitor_start();
  #endif 
  pause(1000);
  #ifdef _servo360_monitor_
    dprint(term, "speedLimit = %d\r", _fbs[0].speedLimit);
  #endif
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(1000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 1080);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(3000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, -1080);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(4000);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  servo360_speed(12, 0);
  #ifdef _servo360_monitor_
    suppressFbDisplay = 0;
  #endif
  pause(1000);  
  
  
  
  #ifdef _servo360_monitor_
    suppressFbDisplay = 1;
  #endif
*/

  //fb360_run();
  /*
  servo360_monitor_start(); 
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
  servo360_monitor_start(); 
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
  servo360_monitor_start(); 
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
  servo360_monitor_start(); 
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



/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
