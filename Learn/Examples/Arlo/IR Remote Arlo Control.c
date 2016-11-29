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
#include "sirc.h"
#include "arlodrive.h"

#define BACK 1
#define RIGHT 3
#define FRONT 0
#define LEFT 2

fdserial *term;

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
      break;
    }
  }          
  low(26);
}  

int main(void)
{
  //drive_pins(12, 13);
  sirc_setTimeout(60);
  simpleterm_close();
  pause(100);
  term = fdserial_open(31, 30, 0, 115200);
  pause(100);
  drive_open();
  while(1)
  {
    dprint(term, "%c", CLS);
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
            break;
          case CH_DN:
            //drive_speed(-100, -100);
            drive_speed(-smul, -smul);
            break;
          case VOL_DN:
            //drive_speed(-100, 100);
            drive_speed(-smul, smul);
            break;
          case VOL_UP:
            //drive_speed(100, -100);
            drive_speed(smul, -smul);
            break;
          default:
            //drive_speed(0, 0);
            drive_speed(0, 0);
          break;
        }
        break; 
      case 1:
        for(int i = 0; i < 4; i++)
        {
          dist[i] = ping_cm(14+i);
          //dprint(term, "%d=%03d\n", i, dist[i]);
          pause(10);
        }

        speedL = 0;
        speedR = 0;

        if(dist[BACK] < 30)
        {
          speedL += 100;
          speedR += 100;
        }
        if(dist[FRONT] < 30)
        {
          speedL -= 100;
          speedR -= 100;
        }
        if(dist[LEFT] < 30)
        {
          if(speedL == 0)
            speedL -= 100;
          else if(speedL < 0)
            //speedR += 200;  
            speedR += 50;  
          else if(speedL > 0)
            //speedR -= 200;  
            speedR -= 50;  
        }
        if(dist[RIGHT] < 30)
        {
          if(speedR == 0)
            speedR -= 100;
          else if(speedR < 0)
            //speedL += 200;  
            speedL += 50;  
          else if(speedR > 0)
            //speedL -= 200;  
            speedL -= 50;  
        }
        drive_speed(speedL, speedR);
        pause(100);
        break;
      case 2:
        smul = 50;
        mode = 0;
        break;
      case 3:
        smul = 100;
        mode = 0;
        break;
      /*  
      case 4:
        val = get_val();
        dprint(term, "val = %d\n", val);
        pause(3000);
      break;
      */
    }  
  }    
}      

