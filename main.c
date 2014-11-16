/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: main.c
 * descript: The main function
 */

#include "adt.h"
#include "sender.h"
#include "server.h"
#include "network.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


/* The main function */
int 
main(int argc, char **argv){

  // read in port_no, TTL, DIR, neighbors from args
  int portno;
  int TTL;
  char Dir[128];
  neighbors_t neighbors;
  pthread_mutex_t lock;
  
  if (argc < 4){
    ERROR("Usage: ./query_flood PORTNO TTL DIR [NEIGHBOR_HOST, ...]\n");
  }
  if (argc > 4){
    int i;
    for (i = 4; i < argc; ++ i){
      // save neighbors to data structure
      unsigned long host_in_addr = find_host_addr(argv[i]);
      if (host_in_addr < 0){
        ERROR("Could not find host\n");
      }
      push_neighbor(&neighbors, host_in_addr);
    }
  }
  portno = atoi(argv[1]);
  TTL = atoi(argv[2]);
  strcpy(Dir, argv[3]);

  // contact neighbors and establish connection
  connect_neighbors(&neighbors, portno);

  // create server config arg
  IDlist_t IDlist;
  server_arg_t server_arg;

  // push values to server args
  server_arg.IDlist = &IDlist;
  server_arg.portno = portno;
  server_arg.Dir = Dir;
  server_arg.lock = &lock;

  // spawn threads to handle server work 
  pthread_t thread;
  if ( pthread_mutex_init (&lock, NULL) != 0 ){
    ERROR ("Error creating mutex\n");
  }

  if ( pthread_create(&thread, NULL, server_worker, (void *)&server_arg) < 0 ){
    ERROR("Error creating receiver thread\n");
  }

  // main thread while loop: sender work 
  while (1){
    // read input from user
    char input[MAX_STRLEN];

    printf ("Search in network: \n");

    fgets(input, MAX_STRLEN, stdin);
    // strip trailing '\n'
    int len = strlen(input);
    if (input != NULL && input[len - 1] == '\n'){
      input[len - 1] = '\0';
    }

    // generate packet and add new ID to list
    // use mutex to protect this area
    packet_t packet;
    int packetID;

    packetID = gen_packet(&packet,
                         input,
                         QUERY,
                         TTL);
    pthread_mutex_lock(&lock);
    add_to_IDlist(&IDlist, packetID);
    pthread_mutex_unlock(&lock);
    
    // send request in UDP to all neighbors
    if ( flood_request(&neighbors, portno, &packet, sizeof(packet_t)) < 0 ){
      ERROR("Error sending request");
    }
  }


}
