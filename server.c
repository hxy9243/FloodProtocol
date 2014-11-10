/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: server.h
 * descript: The query flooding protocol server 
 */


#include "network.h"
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
  server_arg *_arg = (server_arg *)arg;

  IDlist_t *IDlist = _arg->IDlist;
  int portno = _arg->portno;
  char *Dir = _arg->Dir;
  neighbors_t *neighbors = _arg->neighbors;

  // init socket and packet
  int sockfd = bind_socket(portno);
  packet_t packet;
  unsigned long client_ipaddr;

  // main while loop
  while (1){
    // accept new packets
    sock_recvfrom_addr(sockfd, (void *)&packet, sizeof(packet), &client_ipaddr);
    int type = packet.Descript;

    // react accordingly
    if (type == CONNECT){
      server_handle_connect(neighbors);
    }
    else if (type == QUERY){
      server_handle_query(Dir, 
                          neighbors, 
                          packet, 
                          IDlist,
                          client_ipaddr);
    }
    else if (type == RESPON){
      server_handle_respon();
    }

  } // while loop

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


// handle connect packet
// param:
// return:
int server_handle_connect(neighbors_t *neighbors,
                          packet_t *packet){

  // update the neighbors


}


// handle query packet
// param:
// return:
int server_handle_query(char *Dir, 
                        neighbors_t *neighbors, 
                        packet_t *packet,
                        IDlist_t *IDlist
                        unsigned long client_ipaddr){

  packet_t packet;

  // compare ID, ignore if repetitive query
  if (find_in_IDlist(IDlist, packet->ID) == 1){
    return 0;
  }

  // if found in folder, then return the msg back to query host
  if ( find_in_dir(Dir, packet->filename) == 1){
    // shoot the response to initiator of query
    gen_packet(respon_packet,
               packet->filename,
               RESPON,
               0);

    sock_sendto(packet->hostname, packet);
  }
  // not found, flood to neighbors
  else {
    // gen packet
    // TODO

    // shoot the packet
    int i;
    int num_neighbors;
    for (i = 0; i < num_neighbors; ++1){
      unsigned long neighbor_addr;

      // filter out the sender, avoid loops
      if (neighbor_addr != client_ipaddr){

        // send to this neighbor

      }
    }

  }

  return 0;

}


// handle response packet
// param:
// return:
int server_handle_respon(packet_t *packet){


}
