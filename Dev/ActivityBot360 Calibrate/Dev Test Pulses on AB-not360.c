#include "simpletools.h"
#include "servo.h"

int pulseLeft;
int pulseRight;

int main()
{
  servo_set(12, 1560);
  servo_set(13, 1440);
  while(1)
  {
    pulseLeft = pulse_in(14, 1);
    pulseRight = pulse_in(15, 1);
    print("pulseLeft = %d, pulseRight = %d\r", pulseLeft, pulseRight);
    pause(100);
  }  
}
