//#define __test_Andy__
//#define __test_Jeff__
#define __test_text__

#include "simpletools.h"
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
char ecListZ[]  = {0, 0, 0};    

char ecsrn[]  = {'\r', '\n', 0};      // \r\n end character list
char ecsr[]   = {'\r',    0, 0};      // \r character list
char ecsn[]   = {'\n',    0, 0};      // \n character list
char ecsz[]   = {0, 0, 0};            // all zero character list

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


#ifndef __test_text__
int main()
{
  pause(500);
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
  pause(500);
  
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
  pause(500);
  
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
  pause(500);
  
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
  pause(500);
 
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
  pause(500);

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
  pause(500);
  
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
  pause(500);

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
  pause(500);
}
#endif

//********************************************************************************************************/

#ifdef __test_text__
int main()
{
  /* 0 */ pause(500); print("n = %d...", n++); getChar();

  /*  1  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  2  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  3  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  4  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  5  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  6  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  7  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  8  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  9  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  10  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  11  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  12  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  13  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  14  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  15  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  16  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================



  /*  17  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  18  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  19  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  20  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  21  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  22  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  23  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  24  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  25  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  26  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  27  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  28  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  29  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  30  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  31  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  32  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\r", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================



  /*  33  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  34  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  35  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  36  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  37  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  38  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  39  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  40  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  41  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  42  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  43  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  44  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  45  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  46  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  47  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  48  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\n", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================



  /*  49  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  50  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  51  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  52  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  53  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  54  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  55  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  56  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  57  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  58  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  59  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  60  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  61  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  62  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  63  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  64  */  print("n = %d...", n++); getChar(); memcpy(str, "abcdef\0", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 







// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================
// ==================================================================








  pause(500); 

  /*  65  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str); putChar('x'); putchar('x');
  print("%s", str); putChar('x'); putchar('x');
  print("%s", str);

  /*  66  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  67  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  68  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  69  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  70  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  71  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  72  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  73  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  74  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  75  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  76  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  77  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  78  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  79  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  80  */  print("n = %d...", n++); getChar(); memcpy(str, "\r\n", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================



  /*  81  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  82  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  83  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  84  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  85  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  86  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  87  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  88  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  89  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  90  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  91  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  92  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  93  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  94  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  95  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  96  */  print("n = %d...", n++); getChar(); memcpy(str, "\r", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================



  /*  97  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  98  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  99  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  100  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  101  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  102  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  103  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  104  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  105  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  106  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  107  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  108  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  109  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  110  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  111  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  112  */  print("n = %d...", n++); getChar(); memcpy(str, "\n", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================



  /*  113  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  114  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  115  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  116  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 9);
  set_endChars(simpleterm_pointer(), ecListRN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  117  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  118  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  119  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  120  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 9);
  set_endChars(simpleterm_pointer(), ecListR);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  121  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  122  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  123  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  124  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 9);
  set_endChars(simpleterm_pointer(), ecListN);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 
  


  /*  125  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsrn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  126  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsr);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  127  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 8);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsn);
  print("%s", str);
  print("%s", str);
  print("%s", str);

  /*  128  */  print("n = %d...", n++); getChar(); memcpy(str, "\0", 9);
  set_endChars(simpleterm_pointer(), ecListZ);
  set_endCharSequence(simpleterm_pointer(), ecsz);
  print("%s", str);
  print("%s", str);
  print("%s", str);
  
  pause(500); 

// ==================================================================








}
#endif
