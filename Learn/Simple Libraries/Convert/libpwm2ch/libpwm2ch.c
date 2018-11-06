/*
  libpwm2ch.c

  Test harness for the pwm2ch library.
*/

#include "simpletools.h"
#include "pwm2ch.h"

pwm2ch *pwmA;
pwm2ch *pwmB;

int main()                                    
{
  // Start PWM process A.  Frequency = 1 kHz -> pulse period = 1 ms.
  // Start PWM process B.  Frequency = 1.2 kHz -> pulse period = 0.8333.. ms.
  pwmA = pwm2ch_start(1000);   
  pwmB = pwm2ch_start(1200);   
  
  // Set all four available channels.
  pwm2ch_set(pwmA, 3, 0, 300);
  pwm2ch_set(pwmA, 4, 1, 600);
  pwm2ch_set(pwmB, 5, 0, 100);
  pwm2ch_set(pwmB, 6, 1, 200);
  pause(3000);

  // Stop signals on P3 and P5 -> inputs
  pwm2ch_set(pwmA, 3, 0, -1);
  pwm2ch_set(pwmB, 5, 0, -1);
  pause(1000);

  // Re-start channels with different duty cycles.  
  pwm2ch_set(pwmA, 3, 0, 100);
  pwm2ch_set(pwmB, 5, 0, 50);
  pause(1000);
  
  // Turn off channels again 
  pwm2ch_set(pwmA, 3, 0, -1);
  pwm2ch_set(pwmB, 5, 0, -1);
  pause(1000);
  
  // Move signals from other channels to P3 and P5 
  pwm2ch_set(pwmA, 3, 1, 600);
  pwm2ch_set(pwmB, 5, 1, 600);
  pause(1000);
  
  // Move channels that were disabled to the ones just 
  // vacated. 
  pwm2ch_set(pwmA, 4, 0, 300);
  pwm2ch_set(pwmB, 6, 0, 300);
  pause(1000);  

  // Set A process channels low.
  // Set B process channels to inputs.
  pwm2ch_set(pwmA, 3, 0, 0);
  pwm2ch_set(pwmA, 4, 1, 0);
  pwm2ch_set(pwmB, 5, 0, -1);
  pwm2ch_set(pwmB, 6, 1, -1);
  pause(1000);

  // Restart A channels in B channels that were just vacated.
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

