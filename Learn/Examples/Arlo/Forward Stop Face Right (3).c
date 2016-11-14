/*
Forward Stop Face Right.c

http://learn.parallax.com/activitybot/go-certain-distances
*/

#include "simpletools.h"
//#include "abdrive.h"                        // <- Comment out this line
#include "arlodrive.h"                        // <- Replace it with this line
#include "fdserial.h"

fdserial *term;

int main()
{
  drive_goto(0, 0);

  dhb10_terminalMode(term);

  drive_goto(124, 124);
  drive_goto(-124, 124);
  drive_goto(124, -124);
  drive_goto(-124, -124);
  drive_goto(-124, -124);
  drive_goto(124, -124);
  drive_goto(-124, 124);
  drive_goto(124, 124);
  
  //fdserial *com = fdserial_open(9, 8, 0, 9600);
  dhb10_terminalMode(term);

  drive_goto(1024, 1024);
  drive_goto(-1024, 1024);
  drive_goto(1024, -1024);
  drive_goto(-1024, -1024);
  drive_goto(-1024, -1024);
  drive_goto(1024, -1024);
  drive_goto(-1024, 1024);
  drive_goto(1024, 1024);

  dhb10_terminalMode(term);
}