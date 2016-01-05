/*
   Store and Retrieve Info.c
   
   IMPORTANT: Erase EEPROM with 01 Erase Badge EEPROM.side before running 
   this.

   The badgetools library has a feature to store and retrieve non string 
   data like integer and floating point variables.  It also works for 
   multiple strings.  This example program has a number AND a name.   
   Instead of stored, store and retrieve, use eeprinted, eeprint, and 
   eescan.  They utilize format strings, just like print, and scan to 
   convert data to character strings and back again.  This example also
   uses contact_count to find out how many addresses were stored in EEPROM.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

//   badge      num   name                   // Numbers and names
int fredNum = 123;
char fredName[] = "Fred Flintstone";

int wilmaNum = 456;
char wilmaName[] = "Wilma Flintstone";

int num;
char name[32];
int exist, contacts;

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  text_size(SMALL);
  oledprint("Use SimpleIDE\nTerminal.");
  
  // Check if fred's info is already in EEPROM.  If not
  // eeprint it.
  exist = eeprinted("%03d\n%32s\n", fredNum, fredName);
  if(!exist) 
    eeprint("%03d\n%32s\n", fredNum, fredName);
    
  // Repeat for wilma
  exist = eeprinted("%03d\n%32s\n", wilmaNum, wilmaName);
  if(!exist) 
    eeprint("%03d\n%32s\n", wilmaNum, wilmaName);
    
  // Retrieve and display the data
  contacts = contacts_count();
  for(int record = 0; record < contacts; record++)
  {
    eescan(record, "%d%s", &num, &name);
    print("record %d = %d, %s\n", record, num, name);
  }  
}  
