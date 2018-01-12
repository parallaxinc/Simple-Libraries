#ifndef ABCALIBRATE360_H
#define ABCALIBRATE360_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"
#include "servocalibrate360.h"
//#include "servo360.h"


void cal_servo360(int pinControl, int pinFeedback)                    
{
  
  
  /*
    Add pin finding code here
  */ 
  int offset = pinControl * _SERVO_CAL_360_EE_Cal_Rec_Length_;
  

  
  // ee_putStr("S360", 4, _SERVO_CAL_360_EE_Start_ + offset);
  
  // Left servo counterclockwise

  servo360_connect(pinControl, pinFeedback);
  servo360_feedback(pinControl, 0);
  
  int n, x, angle, angleP; 
  int mVccw, mVcw, bVccw, bVcw;
  int increases = 0, decreases = 0, diffCount = 0;
  
  servo360_set(pinControl, 1500 + 240);
  pause(2000);
  x = servo360_getAngle12Bit(pinControl);
  print("x = %d\r", x);
  pause(1000);
  x = servo360_getAngle12Bit(pinControl) - x;
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(pinControl, 1500);
  
  pause(2000);

  angle = servo360_getAngle(pinControl);
  angleP = angle;

  for(n = 0; n < 60; n++)
  {
    servo360_set(pinControl, 1500 + n);
    angle = servo360_getAngle(pinControl);
    print("angle = %d\r", angle);
    if(angle != angleP) increases++;
    if(increases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVccw = (n - 4) * 10 * 2 / 3;
  print("bVccwL = %d\r", bVccw); 
  
  servo360_set(pinControl, 1500);

  mVccw = 1000 * (2200 - bVccw) / x;

  print("mVccwL = %d\r", mVccw); 
  
  
  // Left servo clockwise


  servo360_set(pinControl, 1500-240);
  pause(2000);
  x = servo360_getAngle12Bit(pinControl);
  print("x = %d\r", x);
  pause(1000);
  x = abs(servo360_getAngle12Bit(pinControl) - x);
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(pinControl, 1500);
  
  pause(2000);

  angle = servo360_getAngle(pinControl);
  angleP = angle;

  for(n = 0; n > -60; n--)
  {
    servo360_set(pinControl, 1500 + n);
    angle = servo360_getAngle(pinControl);
    print("angle = %d\r", angle);
    if(angle != angleP) decreases++;
    if(decreases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVcw = abs((n + 4) * 10 * 2 / 3);
  print("bVcw = %d\r", bVcw); 
  
  servo360_set(pinControl, 1500);

  mVcw = 1000 * (2200 - bVcw) / x;

  print("mVccwL = %d\r", mVcw); 

  print("\r=== Summary ===\r"); 
  print("mVccw = %d\r", mVccw); 
  print("bVccw = %d\r", bVccw); 
  print("mVcw = %d\r", mVcw); 
  print("bVcw = %d\r", bVcw); 
  
  ee_putInt(pinControl, _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_PinCTRL_ + offset);
  ee_putInt(pinFeedback, _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_PinFB_ + offset);
  ee_putInt(mVccw, _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_mVccw_ + offset);
  ee_putInt(bVccw, _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_bVccw_ + offset);
  ee_putInt(mVcw, _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_mVcw_ + offset);
  ee_putInt(bVcw, _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_bVcw_ + offset);

  ee_putStr("S360", 4, _SERVO_CAL_360_EE_Start_ + offset);
  
  ee_putInt(0, 0);
}


void cal_displayData(int controlPin)
{
  int offset = controlPin * _SERVO_CAL_360_EE_Cal_Rec_Length_;
  //if(!abd_us) abd_us = CLKFREQ/1000000; 
  
  unsigned char str[5];
  ee_getStr(str, 4, _SERVO_CAL_360_EE_Start_ + offset);
  str[4] = 0;
  
  print("\r\rstr = %s\r\r", str);
  
  if(!strcmp(str, "S360"))
  {
    //print("!!! AB360 SETTINGS NOT FOUND, RETURNING !!!\r");
    //return -1;
    print("Calibration record found.\r\r\r");
    
    //cal_getEepromPins();
    
    int mVccw = ee_getInt(_SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_mVccw_ + offset);
    int bVccw = ee_getInt(_SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_bVccw_ + offset); 
    int mVcw = ee_getInt(_SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_mVcw_ + offset); 
    int bVcw = ee_getInt(_SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_bVcw_ + offset); 
  
    print("\r\rInverse Transfer Function Constants\r");
    print("for y = mx + b\r");
    print("===================================\r"); 
    print("Servo, Counterclockwise\r");
    print("m = %d\r", mVccw); 
    print("b = %d\r", bVccw); 
    print("\rServo, Clockwise\r");
    print("m = %d\r", mVcw); 
    print("b = %d\r", bVcw); 
    
    print("\rNotes:\r");
    print("y: Offset from 15,000 in 0.1 us units\r");
    print("m: Slope in 1.0 us / 4096 increments\r");
    print("x: Desired speed in 4096ths of a revolution/second\r");
    print("b: Number of 0.1 us increments added to 15000\r");
  }   
  else
  {
    print("Calibration data either not found or has errors.\r");
    print("Try cal_displayResults() for more info.\r");
    print("\rRaw data from EEPROM:\r\r");
    for(int a = _SERVO_CAL_360_EE_Start_ + offset; 
    a < _SERVO_CAL_360_EE_Start_ + offset + _SERVO_CAL_360_EE_Cal_Rec_Length_; 
    a++)
    {
      char c = ee_getByte(a);
      if(c >= ' ' && c <= 'z')
      {
        print("%c", c);
      }
      else
      {
        print("[%d]", c);
      }
    }                      
    return;
  }    
  
  print("\r\rCalibration data stored in EEPROM:\r");
  print("===================================\r"); 
    for(int a = _SERVO_CAL_360_EE_Start_ + offset; 
    a < _SERVO_CAL_360_EE_Start_ + offset + _SERVO_CAL_360_EE_Cal_Rec_Length_; 
    a++)
  {
    char c = ee_getByte(a);
    if(c >= ' ' && c <= 'z')
    {
      print("%c", c);
    }
    else
    {
      print("[%d]", c);
    }
  }                      
  return;
}

void cal_displayResults(int controlPin)
{
  int offset = controlPin * _SERVO_CAL_360_EE_Cal_Rec_Length_;

  unsigned char str[5];
  ee_getStr(str, 4, _SERVO_CAL_360_EE_Start_ + offset);
  str[4] = 0;
  
  print("\r\rstr = %s\r\r", str);
  
  if(!strcmp(str, "S360"))
  {
    print("The last calibration completed successfully.\r");
    //return -1;
  }   
  else 
  {
    print("Calibration records not found.  Follow instructions\r");
    print("for calibrating your Feedback 360 Servo.\r");
    //return -1;
  }   
  //
  
  print("\rTry cal_displayData() for more detailed info.\r\r");
  
}


void cal_clear(int controlPin)
{
  int offset = controlPin * _SERVO_CAL_360_EE_Cal_Rec_Length_;
  for(int addr = _SERVO_CAL_360_EE_Start_ + offset; 
      addr < _SERVO_CAL_360_EE_Start_ + _SERVO_CAL_360_EE_Cal_Rec_Length_ + offset; 
      addr++)
  {
    ee_putByte(0xFF, addr); 
  }    
}  
  


#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif
/* ABCALIBRATE360_H */  

