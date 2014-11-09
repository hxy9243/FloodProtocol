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
  IDlist_t *IDlist;
  server_arg_t server_arg;
  char *filenames[MAX_STRLEN];

  init_IDlist(IDlist);

  // push values to server args
  server_arg.IDlist = IDlist;
  server_arg.portno = portno;
  server_arg.Dir = Dir;

  
  // spawn threads to handle server work 
  if ( pthread_create(&thread, NULL, server_worker, (void *)args) < 0 ){
    ERROR("Error creating receiver thread\n");
  }


  // param init for sender
  // TODO: init something else
  init_network();

  // main thread while loop: sender work 
  while (1){

    char input[MAX_STRLEN];

    // TODO: read input
    printf ("Search in network: ");

    fgets(input, MAX_STRLEN, stdin);
    // strip trailing \n
    int len = strlen(input);
    if (input != NULL && input[len - 1] == '\n'){
      input[len - 1] = '\0';
    }

    // generate packet and add new ID to list
    packet_t *packet;
    int packetID;

    packetID = gen_packt(packet,
                         filename,
                         QUERY,
                         TTL);
    add_to_IDlist(IDlist, packetID);
    
    // send request in UDP
    send_request(packet, sizeof(packet_t));

  }

}
