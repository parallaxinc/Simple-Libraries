/*
  libpwm2ch.c

  Drive a pair of DC motors at 6/10 of full speed.
  
  http://learn.parallax.com/propeller-c-tutorials
*/

#include "simpletools.h"
#include "pwm2ch.h"

pwm2ch *pwmA;
pwm2ch *pwmB;

int main()                                    
{
  // Start PWM process.  Frequency = 1 kHz -> pulse period = 1 ms.
  pwmA = pwm2ch_start(1000);   
  pwmB = pwm2ch_start(1200);   
  //high(27);                         
  
  // Turn motors counterclockwise for 3 s.
  pwm2ch_set(pwmA, 3, 0, 300);
  pwm2ch_set(pwmA, 4, 1, 600);
  pwm2ch_set(pwmB, 5, 0, 100);
  pwm2ch_set(pwmB, 6, 1, 200);
  pause(3000);

  // Stop signals on P3 and P5 -> inputs
  pwm2ch_set(pwmA, 3, 0, -1);
  pwm2ch_set(pwmB, 5, 0, -1);
  //low(3);
  pause(1000);
  //input(3);
  
  pwm2ch_set(pwmA, 3, 0, 100);
  pwm2ch_set(pwmB, 5, 0, 50);
  pause(1000);
  
  pwm2ch_set(pwmA, 3, 0, -1);
  pwm2ch_set(pwmB, 5, 0, -1);
  pause(1000);
  
  pwm2ch_set(pwmA, 3, 1, 600);
  pwm2ch_set(pwmB, 5, 1, 600);
  pause(1000);
  
  pwm2ch_set(pwmA, 4, 0, 300);
  pwm2ch_set(pwmB, 6, 0, 300);
  pause(1000);  







  // Stop for 1 second.
  pwm2ch_set(pwmA, 3, 0, 0);
  pwm2ch_set(pwmA, 4, 1, 0);
  pwm2ch_set(pwmB, 5, 0, -1);
  pwm2ch_set(pwmB, 6, 1, -1);
  pause(1000);

  // Turn motors counterclockwise for 3 s.
  pwm2ch_set(pwmA, 5, 0, 600);  
  pwm2ch_set(pwmA, 6, 1, 600);
  pause(3000);

  // Stop again
  pwm2ch_set(pwmA, 5, 0, -1);
  pwm2ch_set(pwmA, 6, 1, -1);
  
  // End the pwm2ch process
  pwm2ch_stop(pwmA);
  pwm2ch_stop(pwmB);
}  

