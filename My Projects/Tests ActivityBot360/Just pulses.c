#include "simpletools.h"                      // Include simple tools
#include "servo.h"

int main()                                    // Main function
{

  servo_set(12, 1500);
  servo_set(13, 1500);
  pause(1000);
  servo_set(12, 1600);
  servo_set(13, 1400);
  pause(2500);
  servo_set(12, 1500);
  servo_set(13, 1500);
  pause(1000);
  servo_set(12, 1400);
  servo_set(13, 1600);
  pause(2500);
  servo_set(12, 1500);
  servo_set(13, 1500);
  pause(1000);

  servo_set(12, 1500);
  servo_set(13, 1500);
  pause(1000);
  servo_set(12, 1550);
  servo_set(13, 1450);
  pause(2500);
  servo_set(12, 1500);
  servo_set(13, 1500);
  pause(1000);
  servo_set(12, 1450);
  servo_set(13, 1550);
  pause(2500);
  servo_set(12, 1500);
  servo_set(13, 1500);
  pause(1000);

}
