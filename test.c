/*
 * This is a file for unit tests
 */


#include "server.h"
#include "adt.h"
#include "config.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

  char Dir[128] = ".";
  char *filename[MAX_STRLEN];


  while(1){
    char input[32];
    scanf("%s", input);

    printf ("strlen is %d\n", (int) strlen(input));

    puts(input);
  }
  return 0;
}
