/*
 * This is a file for unit tests
 */


#include "server.h"
#include "adt.h"
#include "config.h"

#include <stdio.h>

int main(int argc, char **argv){

  char Dir[128] = ".";
  char *filename[MAX_STRLEN];


  read_dir(Dir, filename);



  return 0;
}
