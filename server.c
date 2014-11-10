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

  // init socket
  int sockfd = init_socket(portno);

  // main while loop
  while (1){

    packet_t *packet;

    // accept new packets
    sock_recvfrom(sockfd, (void *)packet);
    
    // if query request
    if (packet->Descript == QUERY){
      // compare ID, ignore if repetitive query
      if (find_in_IDlist(IDlist, packet->ID) == 1){
        continue;
      }

      // if found in folder, then return the msg back to query host
      if ( find_in_dir(Dir, packet->filename) == 1){
        // shoot the response to initiator of query
        packet_t *respon_packet;

        gen_packet(respon_packet, 
                   packet->filename, 
                   RESPON,
                   0);

        sock_sendto(packet->hostname, packet);
      }
      // not found, flood to neighbors
      else {
        // prepare packet
        if (update_packet(packet) <= 0){
          continue;
        }

        // read neighbor config
        read_neighbor_config(CONFIG_FILE, neighbors);
        
        // update neighbors
        
        

        // shoot the packet
                
        
      }
    } // if query packet

      // else if response
    else if (packet->Descript == RESPON){
        

    }

    free(packet);

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

