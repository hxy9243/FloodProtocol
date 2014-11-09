/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: server.h
 * descript: The query flooding protocol server 
 */


#include "adt.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>


// server worker thread function
// param: arg - argument
void server_worker(void *arg){

  // init params

  // main while loop
  while (1){

    // accept new packets

    
    // if request
    
    // compare ID

    // scan and find in folder

    // prepare packet


    // if response
    
    // print out to terminal


  }

}


// read directories
// param: Dir - the dir to scan
//        filename - the filename to find
// return: 1 if hit, 0 if not, -1 if error
int find_in_dir(char *Dir, char *filename){
  DIR *dp;
  struct dirent *dirstruct;

  if ( (dp = opendir(Dir)) == NULL ){
    return -1;
  }

  // loop in dir, search for the filename
  while ( (dirstruct = readdir(dp)) != NULL ){

    if ( strcmp(filenames, dirstruct->d_name) == 0 ){
      return 1;
    }

  }

  closedir(dp);

  return 0;
}

