/*
  Arlo - Serial through arlodrive.c
*/

#include "simpletools.h"                      // Include simple tools
#include "arlodrive.h"

char *reply;

int main()                                    // Main function
{
  print("SPEED & DISTANCE\n\n");
  print("To DHB-10         From DHB-10\n");
  print("-------------     ----------------\n");

  print("RST\\r             ");
  reply = dhb10_com("RST\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  print("gospd 32 32\\r     ");
  reply = dhb10_com("gospd 32 32\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  pause(2000);

  print("gospd 0 0\\r       ");
  reply = dhb10_com("gospd 0 0\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  // Display distance reply as text
  print("dist\\r            ");
  reply = dhb10_com("dist\r");
  if(*reply == '\r') print("\\r\n"); 
  else print("%s", reply);

  print("-------------     ----------------\n");

  // Convert distance reply text to numeric values to use in 
  // calculations, and display the results stored by int variables.
  int countLeft, countRight;
  print("\nVARIABLE VALUES\n", reply);
  sscan(reply, "%d%d", &countLeft, &countRight);
  print("countLeft = %d, countright = %d\n", countLeft, countRight);
}