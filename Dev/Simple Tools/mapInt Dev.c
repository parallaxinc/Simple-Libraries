#include "simpletools.h"



int main()
{
  int val;
  
  int result = mapInt(3, 0, 10, 0, 100);
  print("%d,  \r\r", result);
  
  float fresult = mapFloat(3.0, 0, 10.0, 0, 100.0);
  print("%f,  \r\r", fresult);
  
  fresult = 2.0/3.0;
  print("%f,  \r\r", fresult);
  
  
  
  
  for(val = 0; val <=5; val++)
  {
    int result = mapInt(val, 0, 5, 0, 20);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 5; val >= 0; val--)
  {
    int result = mapInt(val, 5, 0, 20, 0);
    print("%d,  ", result);
  } 
  print("\r");
  for(val = 0; val >= -5; val--)
  {
    int result = mapInt(val, 0, -5, 0, -20);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = -5; val <= 0; val++)
  {
    int result = mapInt(val, -5, 0, -20, 0);
    print("%d,  ", result);
  }    
  print("\r\r\r");
  pause(10);
  
  
  
  
  
  for(val = 0; val <=5; val++)
  {
    int result = mapInt(val, 0, 5, 0, 19);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 0; val <= 5; val++)
  {
    int result = mapInt(val, 0, 5, 19, 0);
    print("%d,  ", result);
  } 
  print("\r");
  for(val = 0; val <= 5; val++)
  {
    int result = mapInt(val, 0, 5, 0, -19);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 0; val <= 5; val++)
  {
    int result = mapInt(val, 0, 5, -19, 0);
    print("%d,  ", result);
  }    
  print("\r\r\r");
  pause(10);
  
  
  
  for(val = 0; val <=5; val++)
  {
    int result = mapInt(val, 0, 5, 0, 19);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 0; val <= 5; val++)
  {
    int result = mapInt(val, 0, 5, 19, 0);
    print("%d,  ", result);
  } 
  print("\r");
  for(val = 0; val <= 5; val++)
  {
    int result = mapInt(val, 0, 5, 0, -19);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 0; val <= 5; val++)
  {
    int result = mapInt(val, 0, 5, -19, 0);
    print("%d,  ", result);
  }    
  print("\r\r\r");
  pause(10);
  
  
  
  for(val = 10; val <=15; val++)
  {
    int result = mapInt(val, 10, 15, 10, 29);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 10; val <= 15; val++)
  {
    int result = mapInt(val, 10, 15, 29, 10);
    print("%d,  ", result);
  } 
  print("\r");
  for(val = 10; val <= 15; val++)
  {
    int result = mapInt(val, 10, 15, -10, -29);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 10; val <= 15; val++)
  {
    int result = mapInt(val, 10, 15, -29, -10);
    print("%d,  ", result);
  }    
  print("\r\r\r");
  pause(10);
  
  
  
  for(val = 10; val <=15; val++)
  {
    int result = mapInt(val, 10, 15, 10, 29);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = 15; val >= 10; val--)
  {
    int result = mapInt(val, 15, 10, 29, 10);
    print("%d,  ", result);
  } 
  print("\r");
  for(val = -10; val >= -15; val--)
  {
    int result = mapInt(val, -10, -15, -10, -29);
    print("%d,  ", result);
  }    
  print("\r");
  for(val = -15; val <= -10; val++)
  {
    int result = mapInt(val, -15, -10, -29, -10);
    print("%d,  ", result);
  }    
  print("\r\r\r");
  pause(10);
  
  
  
}

