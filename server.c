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

    // scan folder

    // prepare packet


    // if response
    
    // print out to terminal


  }

}


// read directories
// param: Dir - the dir to scan
//        filenames - the pointer to array of filenames 
// return: the num of files, -1 when any error
int read_dir(char *Dir, char *filenames[MAX_STRLEN]){
  DIR *dp;
  struct dirent *dirstruct;
  int num_files = 0;

  if ( (dp = opendir(Dir)) == NULL ){
    return -1;
  }

  while ( (dirstruct = readdir(dp)) != NULL ){
    printf ("%s\n", dirstruct->d_name);

    ++ num_files;
  }

  closedir(dp);

  return num_files;
}

