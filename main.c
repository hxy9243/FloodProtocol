/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: main.c
 * descript: The main function
 */

#include "packet.h"
#include "sender.h"
#include "server.h"
#include "network.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


/* The main function */
int 
main(int argc, char **argv){

  // read in port_no, TTL, DIR
  int portno;
  int TTL;
  char Dir[128];

  if (argc != 4){
    ERROR("Usage: query_flood [PORTNO] [TTL] [DIR]");
  }
  portno = atoi(argv[1]);
  TTL = atoi(argv[2]);
  strcpy(Dir, argv[3]);


  // read in neighbor config file
  int neighbor_num;
  neighor_t *neighbors;

  neighbor_num = read_neighbor_config(CONFIG_FILE, neighbors);


  // create server config arg
  IDlist_t *IDlist = init_IDlist();
  server_arg_t server_arg;
  char *filenames[MAX_STRLEN];

  // read in dir files
  if ( read_dir(Dir, filenames) == -1 ){
    ERROR("Error reading in target DIR\n");
  }
  // push values to server args
  server_arg.IDlist = IDlist;
  server_arg.portno = portno;
  server_arg.filenames = filenames;

  
  // spawn threads to handle server work 
  if ( pthread_create(&thread, NULL, server_worker, (void *)args) < 0 ){
    ERROR("Error creating receiver thread\n");
  }


  // main thread while loop: sender work 
  while (1){
    // TODO: read input


    // generate packet
  
  
    // send request in UDP

  }

}
