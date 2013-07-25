/*
* @file libservo.c
*
* @author Andy Lindsay
*
* @copyright
* Copyright (C) Parallax, Inc. 2013. All Rights MIT Licensed.
*
* @brief Project and test harness for the servo library for standard servos.
*/


#include "servo.h"
#include "simpletools.h"

int main()
{
  servo_angle(4, 90);
  while(1);
}
