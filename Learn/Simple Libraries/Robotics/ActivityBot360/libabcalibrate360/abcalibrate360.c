// [  ] Update for pins listed in EEPROM

#ifndef ABCALIBRATE360_H
#define ABCALIBRATE360_H

#if defined(__cplusplus)
extern "C" {
#endif


#include "abcalibrate360.h"    
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

/*
static volatile int abd360_pinCtrlLeft = ABD60_PIN_CTRL_L;
static volatile int abd360_pinCtrlRight = ABD360_PIN_CTRL_R;
static volatile int abd360_pinFbLeft = ABD60_PIN_FB_L;
static volatile int abd360_pinFbRight = ABD360_PIN_FB_R;
*/

void get_pulse_left();
void get_pulse_right();
int *cogPulseLeft;
int *cogPulseRight;
volatile int pulseLeft;
volatile int pulseRight;

                                               //
#define AB360_ERROR_NONE                 0     //
#define AB360_ERROR_CABLE_SWAP          -1     //
#define AB360_ERROR_NO_ENC_SIG_BOTH     -2     //
#define AB360_ERROR_NO_ENC_SIG_LEFT     -3     //
#define AB360_ERROR_NO_ENC_SIG_RIGHT    -4     //
#define AB360_ERROR_NO_MOTION_LEFT      -5     //
#define AB360_ERROR_NO_MOTION_RIGHT     -6     //
#define AB360_ERROR_NO_MOTION_BOTH      -7     //
#define AB360_ERROR_BATTERIES_TOO_LOW   -8
#define AB360_ERROR_BATTERIES_TOO_HIGH  -9
#define AB360_ERROR_XFER_OUT_OF_RANGE   -10
#define AB360_ERROR_CONDITION_UNKNOWN   -11


/*
  VM_CCW = 180
  VB_CCW 200
  VM_CCW = 180
  VB_CW -200
*/


static int errorVal = AB360_ERROR_CONDITION_UNKNOWN;

void playNotes(float tempo, float beatVal, int *note, float *hold);

enum {  C6 = 1047, D6b = 1109,  D6 = 1175, E6b = 1245,  E6 = 1319, F6 = 1397, 
       G6b = 1480,  G6 = 1568, A6b = 1661,  A6 = 1760, B6b = 1865, B6 = 1976,  
        C7 = 2093, D7b = 2219,  D7 = 2349, E7b = 2489,  E7 = 2637, F7 = 2794, 
       G7b = 2960,  G7 = 3136, A7b = 3322,  A7 = 3520, B7b = 3729, B7 = 3951, 
        C8 = 4186 };
        
void playNotes(float tempo, float beatVal, int *note, float *hold)
{
  float msBeat = 60000.0 / tempo;
  float tFullNote = msBeat * beatVal;               

  int t, i = 0;
  
  while(note[i] != 'Q')
  {
    t = (int) (hold[i] * tFullNote);
    freqout(4, t - 20, note[i]);
    pause(20);
    i++;
  }    
}

void cal_fail_dance(void);

void get_pulse_left()
{
  pulseLeft = pulse_in(14, 1);
  while(1);
}  

  
void get_pulse_right()
{
  pulseRight = pulse_in(15, 1);
  while(1);
}  


void cal_activityBot(void)                    
{
  //ee_putStr("AB360      ", 12, _AB360_EE_Start_);
  
  cog_run(get_pulse_left, 128);
  cog_run(get_pulse_right, 128);
  
  int dt = CLKFREQ * 2;
  int t = CNT;
  
  //int errorVal = AB360_ERROR_CABLE_SWAP;

  while((CNT-t) < dt)
  {
    if
    (
      (pulseLeft  < 1200) 
       &&
      (pulseLeft  > 25) 
       &&
      (pulseRight < 1200) 
       &&
      (pulseRight > 25) 
    )
    {
      errorVal = 0;
      break;
    }
  }
  

  if
  (
    (
      (pulseLeft  > 1200) 
       ||
      (pulseLeft  < 25) 
    )
     &&
    (
      (pulseRight > 1200) 
       ||
      (pulseRight < 25) 
    )
  )
  {
    errorVal = AB360_ERROR_NO_ENC_SIG_BOTH;
  }
  else if
  (
    (
      (pulseLeft  > 1200) 
       ||
      (pulseLeft  < 25) 
    )
  )
  {
    errorVal = AB360_ERROR_NO_ENC_SIG_LEFT;
  }
  else if
  (
    (
      (pulseRight > 1200) 
       ||
      (pulseRight < 25) 
    )
  )
  {
    errorVal = AB360_ERROR_NO_ENC_SIG_RIGHT;
  }


  print("pulseLeft = %d, pulseRight = %d \r", pulseLeft, pulseRight);
  print("errorVal = %d \r", errorVal);
  
  
  int brad12bitL, brad12bitR;
  if(errorVal == 0)
  {
    servo360_connect(abd360_pinCtrlLeft, abd360_pinFbLeft);
    servo360_feedback(abd360_pinCtrlLeft, 0);
    servo360_connect(abd360_pinCtrlRight, abd360_pinFbRight);
    servo360_feedback(abd360_pinCtrlRight, 0);
    
    pause(100);  
    
    brad12bitL = servo360_getAngle12Bit(abd360_pinCtrlLeft);
    brad12bitR = servo360_getAngle12Bit(abd360_pinCtrlRight);
      
    servo360_set(abd360_pinCtrlLeft, 1500+120);
    servo360_set(abd360_pinCtrlRight, 1500-120);
    pause(500);
    servo360_set(abd360_pinCtrlLeft, 1500);
    servo360_set(abd360_pinCtrlRight, 1500);
    pause(500);

    brad12bitL = servo360_getAngle12Bit(abd360_pinCtrlLeft) - brad12bitL;
    brad12bitR = servo360_getAngle12Bit(abd360_pinCtrlRight) - brad12bitR;

    print("brad12bitL = %d, brad12bitR = %d \r", brad12bitL, brad12bitR);
    
    if
    (
      (brad12bitL  > 1000) 
       &&
      (brad12bitL  < 3000) 
       &&
      (brad12bitR  < -1000) 
       &&
      (brad12bitR  > -3000) 
    )
    {
      errorVal = 0;
    }
    else if
    (
      (brad12bitR  > 1000) 
       &&
      (brad12bitR  < 3000) 
       &&
      (brad12bitL  < -1000) 
       &&
      (brad12bitL  > -3000) 
    )
    {
      errorVal = AB360_ERROR_CABLE_SWAP;
    }
    else if
    (
      (
        (brad12bitL  < 1000) 
         &&
        (brad12bitL  > -1000) 
      )
       &&
      (
        (brad12bitR  < 1000) 
         &&
        (brad12bitR  > -1000) 
      )  
    )
    {
      errorVal = AB360_ERROR_NO_MOTION_BOTH;
    }
    else if
    (
      (brad12bitL  < 1000) 
       &&
      (brad12bitL  > -1000) 
    )
    {
      errorVal = AB360_ERROR_NO_MOTION_LEFT;
    }
    else if
    (
      (brad12bitR  < 1000) 
       &&
      (brad12bitR  > -1000) 
    )
    {
      errorVal = AB360_ERROR_NO_MOTION_RIGHT;
    }

    print("errorVal = %d \r", errorVal);

  }   
  
  if(errorVal == 0)
  {

    ee_putStr("AB360cstart", 12, _AB360_EE_Start_);
    
    // Left servo counterclockwise
  
    
    int n, x, angle, angleP; 
    int mVccwL, mVcwL, bVccwL, bVcwL;
    int mVccwR, mVcwR, bVccwR, bVcwR;
    int increases = 0, decreases = 0, diffCount = 0;
    
    servo360_set(abd360_pinCtrlLeft, 1500+240);
    pause(1000);
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
    //
    if
    (
      (mVccwL > (S360_VM_CCW * 3)) 
       || 
      (mVccwL < (S360_VM_CCW / 3)) 
       ||        
      (mVcwL > (S360_VM_CW * 3)) 
       || 
      (mVcwL < (S360_VM_CW / 3)) 
       ||        
      (mVccwR > (S360_VM_CCW * 3)) 
       || 
      (mVccwR < (S360_VM_CCW / 3)) 
       ||        
      (mVcwR > (S360_VM_CW * 3)) 
       || 
      (mVcwR < (S360_VM_CW / 3)) 
       ||   
      (bVccwL > (S360_VB_CCW + (S360_VB_CCW * 3))) 
       || 
      (bVccwL < (S360_VB_CCW - (S360_VB_CCW * 3))) 
       ||        
      (bVcwL < (S360_VB_CCW - (S360_VB_CCW * 3))) 
       || 
      (bVcwL > (S360_VB_CCW + (S360_VB_CCW * 3))) 
       ||        
      (bVccwR > (S360_VB_CCW + (S360_VB_CCW * 3))) 
       || 
      (bVccwR <  (S360_VB_CCW - (S360_VB_CCW * 3))) 
       ||        
      (bVcwL < (S360_VB_CCW - (S360_VB_CCW * 3))) 
       || 
      (bVcwL > (S360_VB_CCW + (S360_VB_CCW * 3))) 
    )
    {
      errorVal = AB360_ERROR_XFER_OUT_OF_RANGE;
    }
    else
    {
      ee_putInt(mVccwL, _AB360_EE_Start_ + _AB360_EE_mVccwL_);
      ee_putInt(bVccwL, _AB360_EE_Start_ + _AB360_EE_bVccwL_);
      ee_putInt(mVcwL, _AB360_EE_Start_ + _AB360_EE_mVcwL_);
      ee_putInt(bVcwL, _AB360_EE_Start_ + _AB360_EE_bVcwL_);
    
      ee_putInt(mVccwR, _AB360_EE_Start_ + _AB360_EE_mVccwR_);
      ee_putInt(bVccwR, _AB360_EE_Start_ + _AB360_EE_bVccwR_);
      ee_putInt(mVcwR, _AB360_EE_Start_ + _AB360_EE_mVcwR_);
      ee_putInt(bVcwR, _AB360_EE_Start_ + _AB360_EE_bVcwR_);
      
      ee_putStr("AB360      ", 12, _AB360_EE_Start_);
      
      //drive_speed(48, 48);
      
      int   chargeNotes[] = {  G6,   C7,   E7,    G7,   E7,   G7,  'Q'};
      // float chargeHolds[] = {0.25, 0.25, 0.25, 0.375, 0.25, 0.50,   0 };
      float chargeHolds[] = {0.125, 0.125, 0.125, 0.187, 0.125, 0.50,   0 };
      
      servo360_end();
      pause(100);
      
      //servo360_feedback(abd360_pinCtrlLeft, 1);
      //servo360_feedback(abd360_pinCtrlRight, 1);

      //playNotes(108.0, 4.0, chargeNotes, chargeHolds);
      playNotes(128.0, 4.0, chargeNotes, chargeHolds);
      
      

      //drive_speed(-48, -48);

      //playNotes(108.0, 4.0, chargeNotes, chargeHolds);
      
      //drive_speed(0, 0);
    } 
  }    

  //
  if(errorVal != 0)
  {
    char str[] = "AB360      ";
    sprint(&str[6], "%d", errorVal);
    print("str = %s", str);
    ee_putStr(str, 12, _AB360_EE_Start_);
    cal_fail_dance();
  }           

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
    print("right servo: P%d\r", pinInfo[6]);    
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
    print("right servo: P%d\r", pinInfo[14]);    
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
    pause(50);                               
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

    pause(50);                               
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
  
  pause(50);                               

  print("\r\rCalibration data stored in EEPROM:\r");
  print("===================================\r"); 
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
  else if(!strncmp(str, "AB360", 5))
  {
    sscan(&str[6], "%d", &errorVal);
    print("errorVal = %d\r", errorVal);
                                                            //         
    print("=== ATTENTION ===\r\r");
    print("You might have made a wiring orother mistake\r");
    print("while putting your ActivityBot 360 together.\r\r");
    print("Check the Details section below for more info.\r\r");

    print("For best results, carefully re-check the\r");
    print("ActivityBot 360 setup instructions you followed,\r");
    print("and make sure you did every detail correctly.\r\r");

    print("Each time you think you've got all the mistakes\r");
    print("found and fixed, re-run the calibration program.\r");
    print("Then, re-run this program to find out if the\r"); 
    print("calibration was successful.\r\r");

    print("=== Details === \r\r");

    switch(errorVal)
    {
      case AB360_ERROR_CABLE_SWAP:
        print("One pair of cables has been plugged in correctly,\r");
        print("but the other pair is swapped.\r\r");
        print("Check these details:\r\r");
        print("  o Left servo (closer to servo ports)\r");
        print("     - 3-wire power/control cable to P12 servo port\r");
        print("     - Yellow feedback wire to P14 servo port\r");
        print("  o Right servo (closer to PWR switch)\r");
        print("     - 3-wire power/control cable to P13 servo port\r");
        print("     - Yellow feedback wire to P15 servo port\r");
        break;
      case AB360_ERROR_NO_ENC_SIG_BOTH:
        print("The Propeller is not receiving feedback signals from\r");
        print("the yellow wires that shold be connected to P14 and P15.\r\r");

        print("  o When you start the calibration, move the PWR switch\r"); 
        print("    from 0 to 2 (not 1).\r");
        print("  o Yellow wires should be firmly plugged onto the \r");
        print("    P14 and P15 pins.\r");
        print("  o If you see resistors connecting P14 and P15 to 3.3V,\r");
        print("    remove them.\r");
        print("  o Check to the left of the P12/P13 servo ports.  There\r");
        print("    should be a jumper tab covering the upper 2 pins.\r");
        print("  o Make sure each 3-wire cable's white wire is connected \r");
        print("    to the pin that's closest to the P12/P13 labels and\r");
        print("    the edge of the Activity Board.\r");
        break;
      case AB360_ERROR_NO_ENC_SIG_LEFT:
        print("The Propeller is not receiving feedback signals from\r");
        print("the yellow wire that shold be connected to P14.\r\r");

        print("  o Yellow wire should be firmly plugged onto the \r");
        print("    P14 pin.\r");
        print("  o Make sure The P12 3-wire cable's white wire is connected\r");
        print("    to the pin that's closest to the P12 label and\r");
        print("    the edge of the Activity Board.\r");
        break;
      case AB360_ERROR_NO_ENC_SIG_RIGHT:
        print("The Propeller is not receiving feedback signals from\r");
        print("the yellow wire that shold be connected to P15.\r\r");

        print("  o Yellow wire should be firmly plugged onto the \r");
        print("    P15 pin.\r");
        print("  o Make sure The P13 3-wire cable's white wire is connected\r");
        print("    to the pin that's closest to the P12 label and\r");
        print("    the edge of the Activity Board.\r");
        break;
      case AB360_ERROR_NO_MOTION_LEFT:
        print("Something is preventing the left wheel from turning.\r\r");
        break;
      case AB360_ERROR_NO_MOTION_RIGHT:
        print("Something is preventing the right wheel from turning.\r\r");
        break;
      case AB360_ERROR_NO_MOTION_BOTH:
        print("Something is preventing the both wheels from turning.\r\r");
        break;
      case AB360_ERROR_BATTERIES_TOO_LOW:
        print("Battery voltage is too low.  Use new or freshly recharged\r");
        print("batteries.  It is also possible that one is plugged into the\r");
        print("battery holder backwards.\r");
        break;
      case AB360_ERROR_BATTERIES_TOO_HIGH:
        print("Battery voltage is too high.  Are you using 5 AA batteries.\r");
        break;
      case AB360_ERROR_XFER_OUT_OF_RANGE:
        print("The values the calibration generated are not in the correct\r");
        print("ranges.\r");
        break;
    }        
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


void cal_fail_dance(void)
{

  //cog_run(cal_fail_song, 128);
  for(int i = 0; i < 3; i++)
  {
    freqout(4, 175, 1275);
    pause(150);
    freqout(4, 500, 850);
    pause(100);
    //print("i = %d\r", i);
    for(int j = 0 ; j < 3; j++)
    {
      // print("j = %d\r", j);
      servo360_set(abd360_pinCtrlLeft, 1500+80);
      servo360_set(abd360_pinCtrlRight, 1500+80);
      pause(125);
      servo360_set(abd360_pinCtrlLeft, 1500-80);
      servo360_set(abd360_pinCtrlRight, 1500-80);
      pause(125);
    }
    servo360_set(abd360_pinCtrlLeft, 1500);
    servo360_set(abd360_pinCtrlRight, 1500);

    pause(125);
    
    for(int j = 0 ; j < 3; j++)
    {
      //print("j = %d\r", j);
      for(int k = 0; k < 5; k++)
      {
        // print("k = %d\r", k);
        high(26); high(27);
        pause(5);
        low(26); low(27);
        pause(50);
      }        
      pause(120);
    }
  }      
}  

  


#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif
/* ABCALIBRATE360_H */  

