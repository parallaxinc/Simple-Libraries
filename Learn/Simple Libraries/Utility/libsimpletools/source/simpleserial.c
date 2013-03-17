#include "simpletools.h"

extern _Driver _SimpleSerialDriver;

FILE* sser_setTxRx(int pinTxOut, int pinRxIn, int baudRate)
{
  _driverlist[0] = &_SimpleSerialDriver;
  char str[20] = {"SSER:"};
  char tmp[6] = {0, 0, 0, 0, 0, 0};  
  char mode[3] = {"r+"};

  if(pinTxOut < 0){
    pinTxOut = pinRxIn;
    strcpy(mode, "r");
  }
  else if(pinRxIn < 0){
    pinRxIn = pinTxOut;
  }
  strcat(str, itoa(baudRate, tmp, 10));
  strcat(str, ",");
  strcat(str, itoa(pinRxIn, tmp, 10));
  strcat(str, ",");
  strcat(str, itoa(pinTxOut, tmp, 10));
  FILE *f = fopen(str, mode);
  setvbuf(f, NULL, _IONBF, 0);
  f->_flag &= ~_IOCOOKED;
  return f;
}

FILE* sser_setTx(int pinTxOut, int baudRate)
{
  FILE *f = sser_setTxRx(pinTxOut, -1, baudRate);
  return f;
}

FILE* sser_setRx(int pinRxIn, int baudRate)
{
  FILE *f = sser_setTxRx(-1, pinRxIn, baudRate);
  return f;
}

int sser_close(FILE* peripheral)
{
  int result = fclose(peripheral);
  return result;
}

