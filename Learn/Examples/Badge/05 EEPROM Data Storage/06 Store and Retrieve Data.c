/*
   Store and Retrieve Data.c
   Programs can also use structures to organize and manipulate data.  So, 
   here is an exaample of storing and retrieving data with structures.  
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

typedef struct info_st                       // Structure for the data
{
  int num;
  char name[32];
} info;

info fred  = { 123, "Fred Flintstone" };     // Declare fred & wilma 
info wilma = { 456, "Wilma Flintstone" };

info their;                                  // For getting values from EEPROM

int exist, contacts;

void main() 
{
  badge_setup();
  text_size(SMALL);
  oledprint("Use SimpleIDE\nTerminal.");
  
  // Check if fred's info is already in EEPROM.  If not
  // eeprint it.
  exist = eeprinted("%03d\n%32s\n", fred.num, fred.name);
  if(!exist) 
    eeprint("%03d\n%32s\n", fred.num, fred.name);

  // Repeat for wilma
  exist = eeprinted("%03d\n%32s\n", wilma.num, wilma.name);
  if(!exist) 
    eeprint("%03d\n%32s\n", wilma.num, wilma.name);
    
  //contacts_displayAll();
  
  // Retrieve and display the data
  contacts = contacts_count();
  for(int record = 0; record < contacts; record++)
  {
    eescan(record, "%d%s", &their.num, &their.name);
    print("record %d = %d, %s\n", record, their.num, their.name);
  }  
}  
