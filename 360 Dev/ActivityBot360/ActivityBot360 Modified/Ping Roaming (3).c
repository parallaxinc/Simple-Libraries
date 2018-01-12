/*
  Detect and Turn from Obstacle.c

  Detect obstacles in the ActivityBot's path, and turn a random direction to avoid them.

  http://learn.parallax.com/activitybot/roaming-ultrasound
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive360.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header

int turn;                                     // Navigation variable
int irLeft, irRight;                           // Global variables

//int abd_ticks[2];
//int phs[2];
//int _servoPulseReps;

void botMonitor();



int main()                                    // main function
{
  print("hello\r");
  pause(1000);
  //simpleterm_close();
    
  freqout(4, 2000, 3000);
  drive_speed(0, 0);
  pause(100);
  drive_setRampStep(32);
  drive_setAcceleration(FOR_SPEED, 3600);
  pause(100);
  

  //drive_setRampStep(32);                      // 10 ticks/sec / 20 ms

  //drive_ramp(128, 128);                       // Forward 2 RPS
  //pause(100);
  //cog_run(botMonitor, 256);


  while(1)
  {
    //pause(30);
    // While disatance greater than or equal
    // to 20 cm, wait 5 ms & recheck.
    //drive_ramp(128, 128);                           // Stop & let program end
    drive_speed(128, 128);

    while(1)
    {
      int distance = ping_cm(8);
      pause(1);           // Wait until object in range
      freqout(11, 1, 38000);                      // Left IR LED light
      irLeft = input(10);                         // Check left IR detector
      pause(1);           // Wait until object in range

      freqout(1, 1, 38000);                       // Repeat for right detector
      irRight = input(2);
      pause(1);

      print("%d %d %d\r", irLeft, distance, irRight);
      pause(1);           // Wait until object in range
      if(irLeft == 0 || irRight == 0 || distance <= 25) break;
    }      

  
    //drive_ramp(-64, -64);                           // Then stop
    //pause(100);
  
    // Turn in a random direction
    
    if(irLeft == 0)
    {
      turn = 1;
    }
    else if(irRight == 0)
    {
      turn = 0;
    }
    else
    {            
      turn = rand() % 2;                          // Random val, odd = 1, even = 0
    }    
    
    if(turn == 1)                               // If turn is odd
      drive_speed(128, -128);                     // rotate right
    else                                        // else (if turn is even)
      drive_speed(-128, 128);                     // rotate left
  
    // Keep turning while object is in view
    while(1)
    {
      if(ping_cm(8) > 25) break;
      //if(ping_cm(8) > 20) break;
      pause(1);
    }      
                           // Turn till object leaves view
    //while(irLeft == 0 || irRight == 0 || ping_cm(8) <= 20);                     // Turn till object leaves view
  }    
}


int _servoPulseReps;
volatile int tt[2];
volatile int abd_ticks[2];
volatile int phs[2];

void botMonitor()
{
  int servoPulseRepsOldA;
  simpleterm_open();
  print("hello again\r");
  pause(1000);
  servoPulseRepsOldA = _servoPulseReps;
  while(1)
  {
    //while(servoPulseRepsOldA == _servoPulseReps);
    print("%d %d %d %d %d %d %d\r", 
    _servoPulseReps, tt[0], tt[1], 
    abd_ticks[0], abd_ticks[1], 
    phs[0], phs[1]);
    //pause(10);
    servoPulseRepsOldA = _servoPulseReps;
  }
}

  