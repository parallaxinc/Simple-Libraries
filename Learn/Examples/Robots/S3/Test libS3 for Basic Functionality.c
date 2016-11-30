/*
  This file just verifies basic functionality of the library.
  For lots of C code examples, start by creating a Scribbler 
  Robot Blockly project at http://blockly.parallax.com.  Then, 
  click View and select Propeller C.  Note: If the View menu 
  only offers Spin as an alternate option to the blocks, then 
  the feature has not yet been implemented.
*/ 

#include "simpletools.h"
#include "s3.h"

void main(void)
{
  s3_setup();
  s3_setLED(S3_LEFT, S3_COLOR_FF0000);
  s3_setLED(S3_CENTER, S3_COLOR_FF0000);
  s3_setLED(S3_RIGHT, S3_COLOR_FF0000);
  s3_simpleDrive(S3_STRAIGHT, 127);
  pause(2000);
  s3_simpleStop();
  s3_setLED(S3_LEFT, S3_COLOR_00FF00);
  s3_setLED(S3_CENTER, S3_COLOR_00FF00);
  s3_setLED(S3_RIGHT, S3_COLOR_00FF00);
}

