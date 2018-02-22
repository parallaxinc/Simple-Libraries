/*

Connect Propeller Plug rx to P5.

Run with one instance of Parallax Serial Terminal on the Propeller COM and another
on the Propeller Plug COM.  Note, Parallax Serial Terminal may need to be configured
so that it does not automatically close the port when it is inactive.

In the PST connected to the Propeller COM, repeatedly tap any key to advance the tests.

Below is what the monitored output should look like.
 

n = 0...
n = 1...abc[D][A][D][A]def[D][A][D][A]abc[D][A][D][A]def[D][A][D][A]abc[D][A][D][A]def[D][A][D][A]
n = 2...abc[D][D]def[D][D]abc[D][D]def[D][D]abc[D][D]def[D][D]
n = 3...abc[A][A]def[A][A]abc[A][A]def[A][A]abc[A][A]def[A][A]
n = 4...abcdefabcdefabcdef
n = 5...abc[D][A][A]def[D][A][A]abc[D][A][A]def[D][A][A]abc[D][A][A]def[D][A][A]
n = 6...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 7...abc[A][A]def[A][A]abc[A][A]def[A][A]abc[A][A]def[A][A]
n = 8...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 9...abc[D][D][A]def[D][D][A]abc[D][D][A]def[D][D][A]abc[D][D][A]def[D][D][A]
n = 10...abc[D][D]def[D][D]abc[D][D]def[D][D]abc[D][D]def[D][D]
n = 11...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 12...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 13...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 14...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 15...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 16...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 17...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 18...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 19...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 20...abcdefabcdefabcdef
n = 21...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 22...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 23...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 24...abcdefabcdefabcdef
n = 25...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 26...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 27...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 28...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 29...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 30...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 31...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 32...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 33...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 34...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 35...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 36...abcdefabcdefabcdef
n = 37...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 38...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 39...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 40...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 41...abc[D][A]def[D][A]abc[D][A]def[D][A]abc[D][A]def[D][A]
n = 42...abc[D]def[D]abc[D]def[D]abc[D]def[D]
n = 43...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 44...abcdefabcdefabcdef
n = 45...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 46...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 47...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 48...abc[A]def[A]abc[A]def[A]abc[A]def[A]
n = 49...abcabcabc
n = 50...abcabcabc
n = 51...abcabcabc
n = 52...abcabcabc
n = 53...abcabcabc
n = 54...abcabcabc
n = 55...abcabcabc
n = 56...abcabcabc
n = 57...abcabcabc
n = 58...abcabcabc
n = 59...abcabcabc
n = 60...abcabcabc
n = 61...abcabcabc
n = 62...abcabcabc
n = 63...abcabcabc
n = 64...abcabcabc
n = 65...[D][A][D][A]x[D][A][D][A]x[D][A][D][A]
n = 66...[D][D][D][D][D][D]
n = 67...[A][A][A][A][A][A]
n = 68...
n = 69...[D][A][A][D][A][A][D][A][A]
n = 70...[D][A][D][A][D][A]
n = 71...[A][A][A][A][A][A]
n = 72...[A][A][A]
n = 73...[D][D][A][D][D][A][D][D][A]
n = 74...[D][D][D][D][D][D]
n = 75...[D][A][D][A][D][A]
n = 76...[D][D][D]
n = 77...[D][A][D][A][D][A]
n = 78...[D][A][D][A][D][A]
n = 79...[D][A][D][A][D][A]
n = 80...[D][A][D][A][D][A]
n = 81...[D][A][D][A][D][A]
n = 82...[D][D][D]
n = 83...[A][A][A]
n = 84...
n = 85...[D][A][D][A][D][A]
n = 86...[D][D][D]
n = 87...[A][A][A]
n = 88...
n = 89...[D][D][D]
n = 90...[D][D][D]
n = 91...[D][D][D]
n = 92...[D][D][D]
n = 93...[D][D][D]
n = 94...[D][D][D]
n = 95...[D][D][D]
n = 96...[D][D][D]
n = 97...[D][A][D][A][D][A]
n = 98...[D][D][D]
n = 99...[A][A][A]
n = 100...
n = 101...[A][A][A]
n = 102...[A][A][A]
n = 103...[A][A][A]
n = 104...[A][A][A]
n = 105...[D][A][D][A][D][A]
n = 106...[D][D][D]
n = 107...[A][A][A]
n = 108...
n = 109...[A][A][A]
n = 110...[A][A][A]
n = 111...[A][A][A]
n = 112...[A][A][A]
n = 113...
n = 114...
n = 115...
n = 116...
n = 117...
n = 118...
n = 119...
n = 120...
n = 121...
n = 122...
n = 123...
n = 124...
n = 125...
n = 126...
n = 127...
n = 128...xx



*/
//#define __test_Andy__
//#define __test_Jeff__
#define __test_text__

#include "simpletools.h"
#include "fdserial.h"

fdserial *monitor;

void serial_monitor();

/*
#ifdef __test_text__
#include "simpletext.h"
#endif
*/

/*
char ecListRN[] = {'\r', '\n', 0, 0};    // List of recognized end characters
char ecListR[]  = {'\r',    0, 0, 0};    
char ecListN[]  = {'\n',    0, 0, 0};    

char ecsrn[]  = {'\r', '\n', 0, 0};      // \r\n end character list
char ecsn[]   = {'\n',    0, 0, 0};      // \n character list
char ecsr[]   = {'\r',    0, 0, 0};      // all zero character list
*/

char ecListRN[] = {'\r', '\n', 0};    // List of recognized end characters
char ecListR[]  = {'\r',    0, 0};    
char ecListN[]  = {'\n',    0, 0};    
char ecListZ[]  = {   0,    0, 0};    

char ecsrn[]  = {'\r', '\n', 0};      // \r\n end character list
char ecsr[]   = {'\r',    0, 0};      // \r character list
char ecsn[]   = {'\n',    0, 0};      // \n character list
char ecsz[]   = {   0,    0, 0};            // all zero character list

char str[] = "abcdef\0 ";
int n = 0;

// c is the character string, ec is the list of end characters,
// and ecs is the end character sequence that should tx as soon
// as an ec is detected in c.

#ifdef __test_Andy__
void send_ecs(char *c, char *ec, char *ecs)
{ 
  while(1)
  {
    if( (*c == *ec) || (*c == *(ec+1))  || (*c == *(ec+2))  || (*c == *(ec+3)) )
    {
      while(1)
      {
        if(*ecs == 0 || *c == 0) return;
        putChar(*ecs++);
      }
    }
    putChar(*c++);  
  }
} 
#endif


#ifdef __test_Jeff__
void send_ecs(char *c, char *ec, char *ecs)
{ 
  while(*c)
  {
    if( !( (*c == *ec) || (*c == *(ec+1)) ) )
    {
      putChar(*c++);  
    }
    else
    {
      while(*ecs) {putChar(*ecs++);}
      c++;
    }
  }
}                  
#endif

/*
#ifndef __test_text__
int main()
{
  pause(10);
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListRN, ecsrn);
  send_ecs(str, ecListRN, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListRN, ecsr);
  send_ecs(str, ecListRN, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListRN, ecsn);
  send_ecs(str, ecListRN, ecsn);
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListRN, ecsz);
  send_ecs(str, ecListRN, ecsz);
  memcpy(str, "abcdef\0", 9);
  send_ecs(str, ecListRN, ecsz);
  send_ecs(str, ecListRN, ecsz);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);
  
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListR, ecsrn);
  send_ecs(str, ecListR, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListR, ecsr);
  send_ecs(str, ecListR, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListR, ecsn);
  send_ecs(str, ecListR, ecsn);
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListR, ecsz);
  send_ecs(str, ecListR, ecsz);
  memcpy(str, "abcdef\0", 9);
  send_ecs(str, ecListR, ecsz);
  send_ecs(str, ecListR, ecsz);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);
  
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListN, ecsrn);
  send_ecs(str, ecListN, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListN, ecsr);
  send_ecs(str, ecListN, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListN, ecsn);
  send_ecs(str, ecListN, ecsn);
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListN, ecsz);
  send_ecs(str, ecListN, ecsz);
  memcpy(str, "abcdef\0", 9);
  send_ecs(str, ecListN, ecsz);
  send_ecs(str, ecListN, ecsz);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);
  
  memcpy(str, "abcdef\0", 8);
  send_ecs(str, ecListZ, ecsrn);
  send_ecs(str, ecListZ, ecsrn);
  memcpy(str, "abcdef\r", 8);
  send_ecs(str, ecListZ, ecsr);
  send_ecs(str, ecListZ, ecsr);
  memcpy(str, "abcdef\n", 8);
  send_ecs(str, ecListZ, ecsn);
  send_ecs(str, ecListZ, ecsn);
  memcpy(str, "abcdef\r\n", 9);
  send_ecs(str, ecListZ, ecsz);
  send_ecs(str, ecListZ, ecsz);
  memcpy(str, "abcdef\0", 9);
  send_ecs(str, ecListZ, ecsz);
  send_ecs(str, ecListZ, ecsz);
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);
 
  print("0_n_rn\r");
  memcpy(str, "\0", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("0_n_r\r");
  memcpy(str, "\0", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("0_n_n\r");
  memcpy(str, "\0", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("0_n_z\r");
  memcpy(str, "\0", 9);
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);

  print("r_n_rn\r");
  memcpy(str, "\r", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("r_n_r\r");
  memcpy(str, "\r", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("r_n_n\r");
  memcpy(str, "\r", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("r_n_z\r");
  memcpy(str, "\r", 9);
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);
  
  print("n_n_rn\r");
  memcpy(str, "\n", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("n_n_r\r");
  memcpy(str, "\n", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("n_n_n\r");
  memcpy(str, "\n", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("n_n_z\r");
  memcpy(str, "\n", 9);
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);

  print("rn_n_rn\r");
  memcpy(str, "\r\n", 8);
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  send_ecs(str, ecListN, ecsrn);
  putChar('.');
  print("rn_n_r\r");
  memcpy(str, "\r\n", 8);
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  send_ecs(str, ecListN, ecsr);
  putChar('.');
  print("rn_n_n\r");
  memcpy(str, "\r\n", 8);
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  send_ecs(str, ecListN, ecsn);
  putChar('.');
  print("rn_n_z\r");
  memcpy(str, "\r\n", 9);
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  send_ecs(str, ecListN, ecsz);
  putChar('.');
  putChar('\r');
  putChar('-');
  putChar('-');
  putChar('\r');
  putChar('\r');
  pause(10);
}
#endif

*/


//********************************************************************************************************/

#ifdef __test_text__
int main()
{
  
  cog_run(serial_monitor, 1024);
  
  /* 0 */ pause(10); print("n = %d...", n++); getChar();

  /*  1  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  2  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  3  */  print("n = 3...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  /*  3  */  //print("n = %d...", n++); getChar(); memcpy(str, "abcndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  pause(1);
  putStr("abc\r\ndef\r\n");
  putStr("abc\r\ndef\r\n");
  putStr("abc\r\ndef\r\n");
  //print("%s", str);
  //print("%s", str);
  //print("%s", str);

  /*  4  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  
#if 1

  /*  5  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  6  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  7  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  8  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  9  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  10  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  11  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  12  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  13  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  14  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  15  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  16  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\r\ndef\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 

// ==================================================================



  /*  17  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  18  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  19  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  20  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  21  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  22  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  23  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  24  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  25  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  26  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  27  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  28  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  29  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  30  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  31  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  32  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\rdef\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 

// ==================================================================



  /*  33  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  34  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  35  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  36  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  37  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  38  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  39  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  40  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  41  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  42  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  43  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  44  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  45  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  46  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  47  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  48  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\ndef\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 

// ==================================================================



  /*  49  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  50  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  51  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  52  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  53  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  54  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  55  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  56  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  57  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  58  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  59  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  60  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  61  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  62  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  63  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  64  */  print("n = %d...", n++); getChar(); memcpy(str, "abc\0def\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 







// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================



//#if 0




  pause(10); 

  /*  65  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str); putChar('x'); putchar('x');
  print("%s", str); putChar('x'); putchar('x');
  print("%s", str);

  /*  66  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  67  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  68  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  69  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  70  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  71  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  72  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  73  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  74  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  75  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  76  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  77  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  78  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  79  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  80  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 

// ==================================================================



  /*  81  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  82  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  83  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  84  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  85  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  86  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  87  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  88  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  89  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  90  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  91  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  92  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  93  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  94  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  95  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  96  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 

// ==================================================================



  /*  97  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  98  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  99  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  100  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  101  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  102  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  103  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  104  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  105  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  106  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  107  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  108  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  109  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  110  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  111  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  112  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 

// ==================================================================



  /*  113  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  114  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  115  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  116  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', '\n');
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  117  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  118  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  119  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  120  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\r', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  121  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  122  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  123  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  124  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), '\n', 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  


  /*  125  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', '\n');
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  126  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\r', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  127  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), '\n', 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  128  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 13);
  set_endChars(simpleterm_pointer(), 0, 0);
  set_endCharSequence(simpleterm_pointer(), 0, 0);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(10); 
  
#endif  

// ==================================================================

}
#endif




//
void serial_monitor()
{
  char hexDig[] = "0123456789ABCDEF";
  monitor = fdserial_open(30, 5, 0, 115200);
  
  while(1)
  {
    if(fdserial_rxReady(monitor))
    {
      char c = fdserial_rxChar(monitor);
      if(c == 'n') fdserial_txChar(monitor, '\r');
      if(c >= ' ' && c <= 'z')
      {
        fdserial_txChar(monitor, c);
      }
      else
      {
        fdserial_txChar(monitor, '[');
        if(c <= 15) fdserial_txChar(monitor, hexDig[c]);
        else fdserial_txChar(monitor, '!');
        fdserial_txChar(monitor, ']');
      }
    }              
  }
}  
//