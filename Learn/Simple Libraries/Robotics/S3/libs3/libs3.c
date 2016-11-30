#include "s3.h"

int main(void)
{
  s3_setup();
  s3_setLED(S3_LEFT, S3_COLOR_FF0000);
  s3_setLED(S3_CENTER, S3_COLOR_FF0000);
  s3_setLED(S3_RIGHT, S3_COLOR_FF0000);
  s3_motorSet(100, 100, 3000);
  s3_setLED(S3_LEFT, S3_COLOR_00FF00);
  s3_setLED(S3_CENTER, S3_COLOR_00FF00);
  s3_setLED(S3_RIGHT, S3_COLOR_00FF00);
}