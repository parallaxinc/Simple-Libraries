/*
  Arlo - Control System Adjustments.c
*/

#include "simpletools.h"
#include "arlodrive.h"

char *reply;

int main()
{
  print("CHECK CONSTANTS\n\n");
  print("To DHB-10      From DHB-10\n");
  print("-----------    ----------------\n");

  print("KI\\r           ");
  reply = dhb10_com("KI\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);
  
  print("DZ\\r           ");
  reply = dhb10_com("DZ\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  print("\n\nSET CONSTANTS\n\n");
  print("To DHB-10      From DHB-10\n");
  print("-----------    ----------------\n");
  
  print("KI 65\\r        ");
  reply = dhb10_com("KI 65\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s\n", reply);
  
  print("DZ 1\\r         ");
  reply = dhb10_com("DZ 1\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s\n", reply);

  
  print("\n\nSTORE CONSTANTS\n\n");
  print("To DHB-10      From DHB-10\n");
  print("-----------    ----------------\n");

  print("STORE KI\\r     ");
  reply = dhb10_com("STORE KI\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s\n", reply);
  
  print("STORE DZ\\r     ");
  reply = dhb10_com("STORE DZ\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s\n", reply);
  
  print("\nAll done!\n");
}