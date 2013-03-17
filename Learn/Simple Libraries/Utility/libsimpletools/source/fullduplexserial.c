#include "simpletools.h"

extern _Driver _FullDuplexSerialDriver;

int fdserDriverIndex = -1; 

FILE* fdser_start(int pinTxOut, int pinRxIn, int baudRate, int mode)
{

  if(fdserDriverIndex == -1){
    add_driver(&_FullDuplexSerialDriver);  
    //fdserDriverIndex = findInIntArray(NULL, _driverlist, 16);
    //_driverlist[fdserDriverIndex] = &_FullDuplexSerialDriver;  
    //printf("fdser index = %d\n", fdserDriverIndex);
    fdserDriverIndex = 1;
  }
/*
  if fdserDriverIndex == -1;
  {
    fdserDriverIndex = findIntInArray(NULL, _driverlist, 1);
    _driverlist[fdserDriverIndex] = &_FullDuplexSerialDriver;  
  }  
*/    
  char str[20] = {"FDS:"};
  char tmp[6] = {0, 0, 0, 0, 0, 0};  
  char sermode[3] = {"r+"};

  strcat(str, itoa(baudRate, tmp, 10));
  strcat(str, ",");
  strcat(str, itoa(pinRxIn, tmp, 10));
  strcat(str, ",");
  strcat(str, itoa(pinTxOut, tmp, 10));
  FILE *f = fopen(str, sermode);
//  pause(1000);
  printf(str);
  printf("      ");
  setvbuf(f, NULL, _IONBF, 0);
  return f;
}

int fdser_stop(FILE* peripheral)
{
  int result = fclose(peripheral);
  return result;
}

