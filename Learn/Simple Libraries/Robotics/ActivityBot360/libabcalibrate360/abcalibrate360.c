#ifndef ABCALIBRATE360_H
#define ABCALIBRATE360_H

#if defined(__cplusplus)
extern "C" {
#endif


#include "abcalibrate360.h"    
#include "simpletools.h"
#include "servo360.h"


static volatile int abd360_pinCtrlLeft = ABD60_PIN_CTRL_L;
static volatile int abd360_pinCtrlRight = ABD360_PIN_CTRL_R;
static volatile int abd360_pinFbLeft = ABD60_PIN_FB_L;
static volatile int abd360_pinFbRight = ABD360_PIN_FB_R;


void cal_activityBot(void)                    
{
  ee_putStr("AB360cstart", 12, _AB360_EE_Start_);
  
  // Left servo counterclockwise

  servo360_connect(abd360_pinCtrlLeft, abd360_pinFbLeft);
  servo360_feedback(abd360_pinCtrlLeft, 0);
  
  int n, x, angle, angleP; 
  int mVccwL, mVcwL, bVccwL, bVcwL;
  int mVccwR, mVcwR, bVccwR, bVcwR;
  int increases = 0, decreases = 0, diffCount = 0;
  
  servo360_set(abd360_pinCtrlLeft, 1500+240);
  pause(2000);
  x = servo360_getAngle12Bit(abd360_pinCtrlLeft);
  print("x = %d\r", x);
  pause(1000);
  x = servo360_getAngle12Bit(abd360_pinCtrlLeft) - x;
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(abd360_pinCtrlLeft, 1500);
  
  pause(2000);

  angle = servo360_getAngle(abd360_pinCtrlLeft);
  angleP = angle;

  for(n = 0; n < 60; n++)
  {
    servo360_set(abd360_pinCtrlLeft, 1500 + n);
    angle = servo360_getAngle(abd360_pinCtrlLeft);
    print("angle = %d\r", angle);
    if(angle != angleP) increases++;
    if(increases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVccwL = (n - 4) * 10 * 2 / 3;
  print("bVccwL = %d\r", bVccwL); 
  
  servo360_set(abd360_pinCtrlLeft, 1500);

  mVccwL = 1000 * (2200 - bVccwL) / x;

  print("mVccwL = %d\r", mVccwL); 
  
  
  // Left servo clockwise


  servo360_set(abd360_pinCtrlLeft, 1500-240);
  pause(2000);
  x = servo360_getAngle12Bit(abd360_pinCtrlLeft);
  print("x = %d\r", x);
  pause(1000);
  x = abs(servo360_getAngle12Bit(abd360_pinCtrlLeft) - x);
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(abd360_pinCtrlLeft, 1500);
  
  pause(2000);

  angle = servo360_getAngle(abd360_pinCtrlLeft);
  angleP = angle;

  for(n = 0; n > -60; n--)
  {
    servo360_set(abd360_pinCtrlLeft, 1500 + n);
    angle = servo360_getAngle(abd360_pinCtrlLeft);
    print("angle = %d\r", angle);
    if(angle != angleP) decreases++;
    if(decreases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVcwL = abs((n + 4) * 10 * 2 / 3);
  print("bVcwL = %d\r", bVcwL); 
  
  servo360_set(abd360_pinCtrlLeft, 1500);

  mVcwL = 1000 * (2200 - bVcwL) / x;

  print("mVccwL = %d\r", mVcwL); 

  
  // Right servo counterclockwise

  servo360_connect(abd360_pinCtrlRight, abd360_pinFbRight);
  servo360_feedback(abd360_pinCtrlRight, 0);
  
  servo360_set(abd360_pinCtrlRight, 1500+240);
  pause(2000);
  x = servo360_getAngle12Bit(abd360_pinCtrlRight);
  print("x = %d\r", x);
  pause(1000);
  x = servo360_getAngle12Bit(abd360_pinCtrlRight) - x;
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(abd360_pinCtrlRight, 1500);
  
  pause(2000);

  angle = servo360_getAngle(abd360_pinCtrlRight);
  angleP = angle;
  increases = 0;
  
  for(n = 0; n < 60; n++)
  {
    servo360_set(abd360_pinCtrlRight, 1500 + n);
    angle = servo360_getAngle(abd360_pinCtrlRight);
    print("angle = %d\r", angle);
    if(angle != angleP) increases++;
    if(increases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVccwR = (n - 4) * 10 * 2 / 3;
  print("bVccwR = %d\r", bVccwR); 
  
  servo360_set(abd360_pinCtrlRight, 1500);

  mVccwR = 1000 * (2200 - bVccwR) / x;

  print("mVccwR = %d\r", mVccwR); 
  
  
  // Right servo clockwise


  servo360_set(abd360_pinCtrlRight, 1500-240);
  pause(2000);
  x = servo360_getAngle12Bit(abd360_pinCtrlRight);
  print("x = %d\r", x);
  pause(1000);
  x = abs(servo360_getAngle12Bit(abd360_pinCtrlRight) - x);
  print("x1 = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(abd360_pinCtrlRight, 1500);
  
  pause(2000);

  angle = servo360_getAngle(abd360_pinCtrlRight);
  angleP = angle;
  decreases = 0;

  for(n = 0; n > -60; n--)
  {
    servo360_set(abd360_pinCtrlRight, 1500 + n);
    angle = servo360_getAngle(abd360_pinCtrlRight);
    print("angle = %d\r", angle);
    if(angle != angleP) decreases++;
    if(decreases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVcwR = abs((n + 4) * 10 * 2 / 3);
  print("bVcwR = %d\r", bVcwR); 
  
  servo360_set(abd360_pinCtrlRight, 1500);

  mVcwR = 1000 * (2200 - bVcwR) / x;

  print("mVcwR = %d\r", mVcwR); 

  print("\r=== Summary ===\r", mVcwR); 
  print("mVccw = %d\r", mVccwL); 
  print("bVccwL = %d\r", bVccwL); 
  print("mVcwL = %d\r", mVcwL); 
  print("bVcwL = %d\r", bVcwL); 
  print("mVccwR = %d\r", mVccwR); 
  print("bVccwR = %d\r", bVccwR); 
  print("mVcwR = %d\r", mVcwR); 
  print("bVcwR = %d\r", bVcwR); 
  
  ee_putInt(mVccwL, _AB360_EE_Start_ + _AB360_EE_mVccwL_);
  ee_putInt(bVccwL, _AB360_EE_Start_ + _AB360_EE_bVccwL_);
  ee_putInt(mVcwL, _AB360_EE_Start_ + _AB360_EE_mVcwL_);
  ee_putInt(bVcwL, _AB360_EE_Start_ + _AB360_EE_bVcwL_);

  ee_putInt(mVccwR, _AB360_EE_Start_ + _AB360_EE_mVccwR_);
  ee_putInt(bVccwR, _AB360_EE_Start_ + _AB360_EE_bVccwR_);
  ee_putInt(mVcwR, _AB360_EE_Start_ + _AB360_EE_mVcwR_);
  ee_putInt(bVcwR, _AB360_EE_Start_ + _AB360_EE_bVcwR_);
  
  ee_putStr("AB360      ", 12, _AB360_EE_Start_);
  
  ee_putInt(0, 0);
}


void cal_servoPins(int servoPinLeft, int servoPinRight) 
{
  int eeAddr = _AB360_EE_Start_  + _AB360_EE_Pins_;
  unsigned char pinInfo[8] = {'s', 'p', 'L', 12, ' ', 'R', 13, ' '};  
  pinInfo[3] = (char) servoPinLeft;
  pinInfo[6] = (char) servoPinRight;

  ee_putStr(pinInfo, 8, eeAddr);

  abd360_pinCtrlLeft = servoPinLeft;
  abd360_pinCtrlRight = servoPinRight;
}


void cal_encoderPins(int encPinLeft, int encPinRight)
{
  int eeAddr = 8 + _AB360_EE_Start_  + _AB360_EE_Pins_;
  unsigned char pinInfo[8] = {'e', 'p', 'L', 14, ' ', 'R', 15, ' '};  
  pinInfo[3] = (char) encPinLeft;
  pinInfo[6] = (char) encPinRight;

  ee_putStr(pinInfo, 8, eeAddr);

  abd360_pinFbLeft = encPinLeft;
  abd360_pinFbRight = encPinRight;
}

int cal_getEepromPins()
{
  int eeAddr = _AB360_EE_Start_  + _AB360_EE_Pins_;
  unsigned char pinInfo[16];

  for(int i = 0; i < 16; i++) 
  {
    pinInfo[i] = ee_getByte(eeAddr + i);
    /*
    if(pinInfo[i] <= 'z' && pinInfo[i] >= ' ')
    {
      print("%c", pinInfo[i]);
    }
    else
    {
      print("[%d]", pinInfo[i]);
    }
    */
  }    
  
  print("I/O pins\r");
  print("===================================\r"); 
  print("Control pins:\r");
  print("-----------------------------------\r"); 

  if(pinInfo[0] == 's' && pinInfo[1] == 'p' && pinInfo[2] == 'L' && pinInfo[5] == 'R')
  {
    //abd360_pinCtrlLeft = (int) pinInfo[3];
    //abd360_pinCtrlRight = (int) pinInfo[6];
    print("Left servo: P%d\r", pinInfo[3]);    
    print("Right servo: P%d\r", pinInfo[6]);    
  }
  //
  else
  {
    print("Control pin settings not found.  Defaults of \r");
    print("P12 (left) and P13 (right) will be used. \r");
  }  
  //  
    
  print("\rFeedback pins:\r");
  print("-----------------------------------\r"); 
  if(pinInfo[8] == 'e' && pinInfo[9] == 'p' && pinInfo[10] == 'L' && pinInfo[13] == 'R')
  {
    //abd360_pinFbLeft = (int) pinInfo[11];
    //abd360_pinFbRight = (int) pinInfo[14];
    print("Left servo: P%d\r", pinInfo[11]);    
    print("Right servo: P%d\r", pinInfo[14]);    
  }
  //
  else
  {
    print("Feedback pin settings not found.  Defaults of \r");
    print("P14 (left) and P15 (right) will be used. \r\r");
  } 
  //print("===================================\r\r"); 
}


void cal_displayData(void)
{
  //if(!abd_us) abd_us = CLKFREQ/1000000; 
  
  unsigned char str[12];
  ee_getStr(str, 12, _AB360_EE_Start_);
  str[11] = 0;
  
  if(!strcmp(str, "AB360      "))
  {
    //print("!!! AB360 SETTINGS NOT FOUND, RETURNING !!!\r");
    //return -1;
    print("Calibration record found.\r\r\r");
    
    cal_getEepromPins();
    
    int mVccwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVccwL_);
    int bVccwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVccwL_); 
    int mVcwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVcwL_); 
    int bVcwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVcwL_); 
  
    int mVccwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVccwR_); 
    int bVccwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVccwR_); 
    int mVcwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVcwR_); 
    int bVcwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVcwR_); 
    
    print("\r\rInverse Transfer Function Constants\r");
    print("for y = mx + b\r");
    print("===================================\r"); 
    print("Left Servo, Counterclockwise\r");
    print("m = %d\r", mVccwL); 
    print("b = %d\r", bVccwL); 
    print("\rLeft Servo, Clockwise\r");
    print("m = %d\r", mVcwL); 
    print("b = %d\r", bVcwL); 
    
    print("\rRight Servo, Counterclockwise\r");
    print("m = %d\r", mVccwR); 
    print("b = %d\r", bVccwR); 
    print("\rRight Servo, Clockwise\r");
    print("m = %d\r", mVcwR); 
    print("b = %d\r", bVcwR); 

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
    for(int a = _AB360_EE_Start_; a < _AB360_EE_End_; a++)
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
  
  //pause(100); 
  
  print("\r\rCalibration data stored in EEPROM:\r");
  print("===================================\r"); 
  pause(100); 
  
  for(int a = _AB360_EE_Start_; a < _AB360_EE_End_; a++)
  {
    char c = ee_getByte(a);
    if((c >= ' ') && (c <= 'z'))
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

void cal_displayResults(void)
{
  //if(!abd_us) abd_us = CLKFREQ/1000000; 
  
  unsigned char str[12];
  ee_getStr(str, 12, _AB360_EE_Start_);
  str[11] = 0;
  
  if(!strcmp(str, "AB360      "))
  {
    print("The last calibration completed successfully.\r");
    //return -1;
  }   
  else if(!strcmp(str, "AB360cstart"))
  {
    print("Calibration started but did not complete.\r");
    print("Verify the servo and encoder connections\r");
    print("against the ones in the diagrams and try\r");
    print("again. Follow the instructions carefully.\r");
    //return -1;
  }   
  else if(!strcmp(str, "ActivityBot"))
  {
    print("There is a non-servo360 ActivityBot calibration.\r");
    print("in the EEPROM.  Make sure to follow the instructions\r");
    print("for calibrating the ActivityBot360.\r");
    //return -1;
  }   
  else 
  {
    print("Calibration records not found.  Follow instructions\r");
    print("for calibrating your ActivityBot360.\r");
    //return -1;
  }   
  //
  
  print("\rTry cal_displayData() for more detailed info.\r\r");
  
  //
    
  int mVccwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVccwL_);
  int bVccwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVccwL_); 
  int mVcwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVcwL_); 
  int bVcwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVcwL_); 

  int mVccwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVccwR_); 
  int bVccwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVccwR_); 
  int mVcwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVcwR_); 
  int bVcwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVcwR_); 
  
  /*
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VM_CCW, mVccwL);
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VB_CCW, bVccwL);
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VM_CW, mVcwL);
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VB_CW, -bVcwL );

  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VM_CCW, mVccwR );
  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VB_CCW, bVccwR);
  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VM_CW, mVcwR);
  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VB_CW, -bVcwR);
  */

  /*
  print("Inverse Transfer Function Constants\r");
  print("for y = mx + b\r");
  print("y: Offset from 15,000 in 0.1 us units\r");
  print("m: Slope in 1.0 us / 4096 increments\r");
  print("x: Desired speed in 4096ths of a revolution/second\r");
  print("b: Number of 0.1 us increments added to 15000\r");
  print("\r===================================\r"); 
  print("\rLeft Servo, Counterclockwise\r");
  print("m = %d\r", mVccwL); 
  print("b = %d\r", bVccwL); 
  print("\rLeft Servo, Clockwise\r");
  print("m = %d\r", mVcwL); 
  print("b = %d\r", bVcwL); 
  
  print("\rRight Servo, Counterclockwise\r");
  print("m = %d\r", mVccwR); 
  print("b = %d\r", bVccwR); 
  print("\rRight Servo, Clockwise\r");
  print("m = %d\r", mVcwR); 
  print("b = %d\r", bVcwR);  
  */ 
}


void cal_clear(void)
{
  for(int addr = _AB360_EE_Start_; addr <_AB360_EE_End_; addr++)
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

