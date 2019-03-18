/*
  File: ActivityBot 360 Robot Control for Parallaxy.side
  
  Authors: Based on https://letsrobot.tv driver for Telly robot obtained 
  from
  https://github.com/runmyrobot/ParallaxBot/tree/rl-feedback360/parallaxScripts
  Modified by Parallax Inc for use with Parallaxy robot and updated 
  ActivityBot and Servo360 libraries.
  
  Version 1.0
  
  Copyright (C) Parallax Inc. 2018. All Rights MIT Licensed.  See end of file.
*/

#include "simpletools.h"
#include "fdserial.h"
#include "abdrive360.h"
#include "ws2812.h"

#define LED_PIN 8
#define LED_COUNT 18

void motor_controller();
void neopixel_controller();
void set_motor_controller(int leftSpeed, int rightSpeed);

void eyes_blink();
void refresh_eyes();
void change_brightness(int change_amount);

int ledColors[LED_COUNT];
int dim_array[LED_COUNT];

ws2812 *driver;

int brightness = 10;
int eye_color = 0xFFFFFF;

// enables full-duplex serilization of the terminal
// (In otherwise, 2 way signals between this computer and the robot)
fdserial *term;

volatile int current_leftspd = 0;
volatile int current_rightspd = 0;
volatile int motor_flag = 0;

int defaultStraightSpeed = 60;
int defaultTurnSpeed = 15;

int main() {
  drive_setAcceleration(FOR_SPEED, 150);
  servo360_couple(12, 13);
  servo360_setCoupleScale(12, 13, 2000);

  servo360_setControlSys(12, S360_SETTING_KPV, 2000); // KPV
  servo360_setControlSys(13, S360_SETTING_KPV, 2000); // KPV

  //close the SimpleIDE terminal
  simpleterm_close();

  //set full-duplex serialization for the terminal
  term = fdserial_open(31, 30, 0, 9600);

  cog_run(motor_controller, 128);

  // load the LED driver
  driver = ws2812b_open();

  pause(500);
  eyes_blink();

  int inputStringLength = 20;
  char inputString[inputStringLength];

  int sPos = 0;

  while (1) {
    if (fdserial_rxReady(term) != 0) {

      // Get the character entered from the terminal
      char c = fdserial_rxChar(term);

      if (c != -1) {
        dprint(term, "%d", (int) c);
        if (c == 13 || c == 10) {
          dprint(term, "received line:");
          dprint(term, inputString);
          dprint(term, "\n");
          if (strcmp(inputString, "l") == 0) {
            dprint(term, "left");
            set_motor_controller(-defaultTurnSpeed, defaultTurnSpeed);
          }
          if (strcmp(inputString, "r") == 0) {
            dprint(term, "right");
            set_motor_controller(defaultTurnSpeed, -defaultTurnSpeed);
          }
          if (strcmp(inputString, "f") == 0) {
            dprint(term, "forward");
            set_motor_controller(defaultStraightSpeed, defaultStraightSpeed);
          }
          if (strcmp(inputString, "b") == 0) {
            dprint(term, "back");
            set_motor_controller(-defaultStraightSpeed, -defaultStraightSpeed);
          }
          if (strcmp(inputString, "l_up") == 0) {
            dprint(term, "left_stop");
            drive_speed(0, 0);
          }
          if (strcmp(inputString, "r_up") == 0) {
            dprint(term, "right_stop");
            drive_speed(0, 0);
          }
          if (strcmp(inputString, "f_up") == 0) {
            dprint(term, "forward_stop");
            drive_speed(0, 0);
          }
          if (strcmp(inputString, "b_up") == 0) {
            dprint(term, "back_stop");
            drive_speed(0, 0);
          }
          if (strcmp(inputString, "brightness_up") == 0) {
            change_brightness(10);
            dprint(term, "brightness increased");
          }
          if (strcmp(inputString, "brightness_down") == 0) {
            change_brightness(-10);
            dprint(term, "brightness decreased");
          }
          if (strncmp(inputString, "led", 3) == 0) {
            int pixel;
            int color;
            sscanAfterStr(inputString, "led", "%d%x", &pixel, &color);
            dprint(term, "%d\n", color);
            if (pixel < LED_COUNT) {
              ledColors[pixel] = color;
              refresh_eyes();
            }
          }
          if (strncmp(inputString, "leds", 4) == 0) {
            int color;
            sscanAfterStr(inputString, "leds", "%x", &color);
            dprint(term, "%d\n", color);
            for (int i = 0; i < LED_COUNT; ++i) {
              ledColors[i] = color;
            }
            refresh_eyes();
          }
          sPos = 0;
          inputString[0] = 0; // clear string
        }
        else if (sPos < inputStringLength - 1) {
          // record next character
          inputString[sPos] = c;
          sPos += 1;
          inputString[sPos] = 0; // make sure last element of string is 0
          dprint(term, inputString);
          dprint(term, " ok \n");
        }
      }
    }
  }
}

void set_motor_controller(int leftSpeed, int rightSpeed) {
  current_leftspd = leftSpeed;
  current_rightspd = rightSpeed;
  motor_flag = 1;
}

void motor_controller() {
  while (1) {
    if (motor_flag == 1) {
      drive_speed(current_leftspd, current_rightspd);
      motor_flag = 0;
      pause(500);
    }
    else
    {
      drive_speed(0, 0);
    }
    pause(10);
  }
}

void refresh_eyes() {
  for (int j = 0; j < LED_COUNT; ++j) {
    int red = (ledColors[j] >> 16) & 0xFF;
    red = red * brightness / 255;

    int green = (ledColors[j] >> 8) & 0xFF;
    green = green * brightness / 255;

    int blue = (ledColors[j]) & 0xFF;
    blue = blue * brightness / 255;

    dim_array[j] = (red << 16) + (green << 8) + (blue);
  }
  ws2812_set(driver, LED_PIN, dim_array, LED_COUNT);
}

void change_brightness(int change_amount) {
  brightness = constrainInt(brightness + change_amount, 2, 255);
  refresh_eyes();
}

void eyes_blink() {
  int doot = 0;

  while (doot < LED_COUNT) {
    if (doot == 4 || doot == 13)
      ledColors[doot] = 0x000000;
    else
      ledColors[doot] = eye_color;
    doot++;
  }
  refresh_eyes();

  doot = 0;
  pause(400);

  while (doot < LED_COUNT) {
    if ((doot >= 3 && doot <= 5) || (doot >= 12 && doot <= 14))
      ledColors[doot] = eye_color;
    else
      ledColors[doot] = 0x000000;
    doot++;
  }
  refresh_eyes();

  doot = 0;
  pause(400);

  while (doot < LED_COUNT) {
    if (doot == 4 || doot == 13)
      ledColors[doot] = 0x000000;
    else
      ledColors[doot] = eye_color;
    doot++;
  }
  refresh_eyes();
}

/**
TERMS OF USE: MIT License

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/