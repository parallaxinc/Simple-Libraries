#include "simpletools.h"

int ping(int pin)
{
  low(pin);
  pulseOut(pin, 10);
  return pulseIn(pin, 1);
}

int ping_cm(int pin)
{
  long tEcho = ping(pin);
  int cmDist = tEcho / 58;
  return cmDist;
}

int ping_inches(int pin) 
{
  long tEcho = ping(pin);
  int inDist = tEcho / 148;
  return inDist;
}