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

