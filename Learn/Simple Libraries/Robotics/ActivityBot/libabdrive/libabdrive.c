/*
 * @brief Test harness for abdrive library. 
 *
 * See learn.parallax.com/activitybot for more info.
 */


#include "simpletools.h" 
#include "abdrive.h"
//#define stop_it
//#define test_t_interval
//#define test_speed
#define track_variables


//#define test_distance

#ifdef test_t_interval
volatile int rec_t[8000 / 4];
#endif  

volatile int abd_speedL;                                   // Incremented servo speed left
volatile int abd_speedR;                                   // Incremented servo speed right
volatile int abd_ticksL;
volatile int abd_ticksR;
volatile int abd_ticksGuardL;
volatile int abd_ticksGuardR;
volatile int abd_speedLT;                                   // Target speed left/right
volatile int abd_speedRT;                                   
//volatile int abd_speedL;                                    // Current requested speed
//volatile int abd_speedR;                                   
//volatile int abd_speedLT;                                   // Target speed left/right
//volatile int abd_speedRT;                                   
volatile int abd_gotoFlagL;
volatile int abd_gotoFlagR;
volatile unsigned int _servoPulseReps;                     // Servo pulse counter
volatile int abd_ticksL;                                // Measured distance left/right
volatile int abd_ticksR;
volatile int abd_ticksLi;
volatile int abd_ticksLf;

volatile int abd_ticksRi;
volatile int abd_ticksRf;
volatile int abd_stopCtrL;
volatile int abd_stopCtrR;
volatile int signL;
volatile int signR;

volatile int abd_rampStepR;
volatile int abd_ditherARd;
volatile int abd_rampStepL;
volatile int abd_ditherALd;

int main()                     
{
  //print("hello");
  //while(1);
  //drive_pins(14, 15, 12, 13); 
  //  drive_goto(100, 100);
  
  #ifdef stop_it
  drive_speed(0, 0);
  while(1);
  #endif 
  
  #ifdef test_speed
  drive_speed(100, 100);
  pause(2000);
  drive_speed(-50, -50);
  pause(3000);
  drive_speed(0, 0);
  #endif
  //pause(1000);
  
  #ifdef test_distance
  //drive_goto(256, 256);
  //pause(3000);
  //drive_goto(-128, -128);
  //pause(3000);
  #endif
    
  #ifdef test_t_interval
    drive_goto(512, 512);
    for(int n = 1; ((n*4) < ((sizeof(rec_t) - 8))); n++)
    {
      print("n = %d,  rec_t = %d,  dt = %d \n", n, rec_t[n], rec_t[n] - rec_t[n-1]);
    }  
    while(1);  
  #endif  
    
  //drive_speed(0, 0);
  pause(100);
  
  #ifdef track_variables

  int n = _servoPulseReps;
  print("\rdrive_goto(192, 128)\r\r");
  //drive_goto(-32, 64);
  drive_goto(192, 128);
  while(1)
  {
    /*
    if(_servoPulseReps > 600)
    {
      drive_goto(0, 0);
      while(1);
    }
    */      
    //  
    //if(_servoPulseReps == 10) 
    if(_servoPulseReps == 350)
    {
      //print("\rdrive_goto(-256, -256)\r\r");
      drive_goto(-256, -256);
    }      

    if(_servoPulseReps == 800)
    {
      //print("\rdrive_goto(-64, 65)\r\r");
      //drive_goto(-62, 65);
      drive_goto(-67, 65);
    }      

    if(_servoPulseReps == 1100)
    {
      drive_speed(40, 40);
      pause(2000);
      drive_speed(-40, 40);
      pause(2000);
      drive_speed(40, -40);
      pause(2000);
      drive_speed(40, 40);
      pause(2000);
      drive_speed(0, 0);
      while(1);
    }     
    //
    
    
    
    
     
    //drive_goto(0, -0);
    if(_servoPulseReps == 900) drive_goto(0, 0);
    if(_servoPulseReps == 1200) drive_goto(0, 0);
    if(_servoPulseReps == 1300) while(1);
    //n++;
    while(1)
    {
      if(_servoPulseReps != n)
      {
        n = _servoPulseReps;
        break;
      }
    }              
      
    print("n%d\r"\
          "dLf%d dL%d sLT%d sL%d tgL%d gtfL%d scL%d"\
          " | "\
          "dRf%d dR%d sRT%d sR%d tgR%d gtfR%d scR%d\r"\
          "rsl%d dald%d | rsr%d dalr%d\r",
          _servoPulseReps, 
          abd_ticksLf, abd_ticksL, abd_speedLT, abd_speedL, abd_ticksGuardL, abd_gotoFlagL, abd_stopCtrL, 
          abd_ticksRf, abd_ticksR, abd_speedRT, abd_speedR, abd_ticksGuardR, abd_gotoFlagR, abd_stopCtrR, 
          abd_rampStepL, abd_ditherALd, abd_rampStepR, abd_ditherARd);
    
    if(n >= 1999) break;
    //pause(18);
  }  
#endif //track_variables
    

  #ifdef interactive_development_mode
  drive_record(1);
  #endif
  pause(300);
  drive_speed(20, 20);
  pause(1600);
  #ifdef interactive_development_mode
  drive_record(0);
  #endif
  pause(6400);
  #ifdef interactive_development_mode
  drive_record(1);
  #endif
  pause(1600);
  drive_speed(0, 0);
  #ifdef interactive_development_mode
  drive_record(0);
  #endif

  #ifdef interactive_development_mode
  drive_displayControlSystem(0, 2500/11);
  #endif

  while(1);
}



