/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: main.c
 * descript: The main function
 */

/* #include "packet.h" */
/* #include "sender.h" */
/* #include "server.h" */
/* #include "network.h" */


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "main.h"

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
  FILE *fp;
  char neighbor_ip[16];
  int neighbor_port;
  if ( (fp = fopen(CONFIG_FILE, "r")) == NULL ){
    ERROR("Cannot open config file");
  }
  while ( fscanf(fp, "%s%d\n", neighbor_ip, &neighbor_port) != EOF ){

    printf ("neighbor: %s : %d\n", neighbor_ip, neighbor_port);

  }

  // create server config arg
  


  // spawn threads to handle server work 
  if ( pthread_create(&thread, NULL, recv_worker, (void *)args) < 0 ){
    ERROR("Error creating receiver thread\n");
  }

  // main while loop: sender work 
  while (1){
    // TODO: read input


    // generate packet
  
  
    // send request in UDP

  }

}
