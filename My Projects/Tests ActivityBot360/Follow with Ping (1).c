/*
  Follow with Ping.c

  Maintain a constant distance between ActivityBot and object.

  http://learn.parallax.com/activitybot/follow-objects-ultrasound
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive360.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header  

int _distance, _setPoint, _errorVal, _kp, _speed;  // Navigation variables

int main()                                    // main function
{
  /*
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 
  */

  _setPoint = 20;                              // Desired cm distance
  _kp = -3;                                   // Proportional control

  drive_setRampStep(2);                       // 7 ticks/sec / 20 ms

  while(1)                                    // main loop
  {
    _distance = ping_cm(8);                    // Measure distance
    //print("dist: %d\r", distance);
    _errorVal = _setPoint - _distance;           // Calculate error
    _speed = _kp * _errorVal;                    // Calculate correction speed

    if(_speed > 32) _speed = 32;              // Limit top speed
    if(_speed < -32) _speed = -32;

    drive_rampStep(_speed, _speed);             // Use result for following
    //pause(20);
  }
}

