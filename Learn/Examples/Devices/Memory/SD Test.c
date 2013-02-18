#include "simpletools.h"                      // Include simpletools header

int DO = 22, CLK = 23, DI = 24, CS = 25;

int main(void)
{
  pause(1000);                                // Delay before console messages

  int erc = sd_mount(DO, CLK, DI, CS);
  
  if(erc)
  {
    printf("Error opening card.");
    printf("error code = %d\n", erc);
  }
  else
  {
    FILE *fp = fopen("test.txt", "w");
    if(fp)
    {
      fprintf(fp, "Test message, hello!\n");
    }
    else
    {
      printf("File did not open.\n");
    }
    fclose(fp);
  
    fp = fopen("test.txt", "r");
  
    char s[80];
    int v;
  
    if(fp)
    {
    fread(s, 1, 21, fp);
    printf("%s", s);
    printf("\n");
    }
    else
    {
      printf("File did not open.\n");
      printf("\n");
    }
    fclose(fp);
  }
}    
            
