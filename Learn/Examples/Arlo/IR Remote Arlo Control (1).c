/*
  Connect P12 to CH1 and P13 to CH2
  Pings 14-back
        15-right
        16-front
        17-left
*/  

#include "simpletools.h" 
#include "ping.h"
#include "fdserial.h"
//#include "servo.h"
#include "sirc.h"
//#include "servodiffdrive.h"
#include "arlodrive.h"

#define BACK 1
#define RIGHT 3
#define FRONT 0
#define LEFT 2

fdserial *sterm;

int offset = 0, increment = 1, cycles = 0;

static int dist[4];
static int button;
static int mode = 0;
static int speedL = 0, speedR = 0;
static int val;
static int smul = 50;

int get_val(void)
{
  int val = 0;
  button = -1;
  //high(26);
  //freqout(4, 100, 4000);
  //low(26);
  pause(250);
  while(1)
  {
    val *= 10;
    button = sirc_button(10);
    if(button == ENTER)
    {
      if(val > 500) val = 500;
      if(val < -500) val = -500;
      button = -1;
      break;
    }
    else if(button != -1)
    {
      high(26);
      freqout(4, 100, 4000);
      low(26);
      if(button >= 0 && button <= 9)
        val += button;
      pause(250); 
      button = -1; 
    }      
  }          
  low(26);
  return val;
}  

void set_mode(void)
{
  button = -1;
  high(26);
  freqout(4, 100, 4000);
  pause(250);
  while(button == -1)
  {
    button = sirc_button(10);
    if(button != -1)
      freqout(4, 100, 4000);
    if(button >-1 && button < 10)
    {
      mode = button;
      dprint(sterm, "mode = %d\n", mode);     
      break;
    }
  }     
  low(26);
}  

int main(void)
{
  //drive_pins(12, 13);
  sirc_setTimeout(100);
  simpleterm_close();
  pause(100);
  sterm = fdserial_open(31, 30, 0, 115200);
  pause(100);
  drive_open();
  //drive_speedBlocking(0);
  while(1)
  {
    //dprint(sterm, "%c", CLS);
    button = sirc_button(10);
    if(button == PWR)
    {
      set_mode();
    } 
    switch(mode)
    {
      case 0:  
        switch(button)
        {
          case CH_UP:
            //drive_speed(100, 100);
            drive_speed(smul, smul);
            dprint(sterm, "u");
            break;
          case CH_DN:
            //drive_speed(-100, -100);
            drive_speed(-smul, -smul);
            dprint(sterm, "b");
            break;
          case VOL_DN:
            //drive_speed(-100, 100);
            drive_speed(-smul, smul);
            dprint(sterm, "l");
            break;
          case VOL_UP:
            //drive_speed(100, -100);
            drive_speed(smul, -smul);
            dprint(sterm, "r");
            break;
          default:
            //drive_speed(0, 0);
            dprint(sterm, "s");
            drive_speed(0, 0);
          break;
        }
        break; 
      case 1:
        for(int i = 0; i < 4; i++)
        {
          dist[i] = ping_cm(14+i);
          //dprint(sterm, "%d=%03d\n", i, dist[i]);
          pause(10);
        }

        speedL = 0;
        speedR = 0;

        if(dist[BACK] < 30)
        {
          speedL += smul;
          speedR += smul;
        }
        if(dist[FRONT] < 30)
        {
          speedL -= smul;
          speedR -= smul;
        }
        if(dist[LEFT] < 30)
        {
          if(speedL == 0)
            speedL -= smul;
          else if(speedL < 0)
            //speedR += 200;  
            speedR += smul / 2;  
          else if(speedL > 0)
            //speedR -= 200;  
            speedR -= smul / 2;  
        }
        if(dist[RIGHT] < 30)
        {
          if(speedR == 0)
            speedR -= smul;
          else if(speedR < 0)
            //speedL += 200;  
            speedL += smul / 2;  
          else if(speedR > 0)
            //speedL -= 200;  
            speedL -= smul / 2;  
        }
        drive_speed(speedL, speedR);
        pause(20);
        break;
      case 2:
        smul = 50;
        dprint(sterm, "smul = %d\n", smul);
        mode = 0;
        break;
      case 3:
        smul = 100;
        dprint(sterm, "smul = %d\n", smul);
        mode = 0;
        break;
      case 4:
        smul = 200;
        dprint(sterm, "smul = %d\n", smul);
        mode = 0;
        break;
      /*  
      case 4:
        val = get_val();
        dprint(sterm, "val = %d\n", val);
        pause(3000);
      break;
      */
    }  
  }    
}      

