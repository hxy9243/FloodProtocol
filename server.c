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
    client_ipaddr = sock_recvfrom(sockfd, (void *)&packet, sizeof(packet));
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
// param: neighbors - the neighbors structure
//        packet - the received packet
// return: 0 on success -1 on error
int server_handle_connect(neighbors_t *neighbors,
                          packet_t *packet){

  int host_in_addr = packet->host_in_addr;

  // TODO: get new sockfd from ip address
  int sockfd = new_udp_sock(host_in_addr);

  // update the neighbors
  if ( !find_neighbor(host_in_addr, neighbors) ){
    push_neighbor(neighbors, host_in_addr);

    // TODO: display info here
  }

  return 0;
}


// handle query packet
// param: Dir - the dir to search
//        neighbors - the adt for all neighbors
//        packet - the received packet
//        IDlist - list of IDs 
//        client_ipaddr - the sender's ip addr
// return: 0 on success -1 on error
int server_handle_query(char *Dir, 
                        neighbors_t *neighbors, 
                        packet_t *packet,
                        IDlist_t *IDlist
                        unsigned long client_ipaddr){

  packet_t respon_packet;

  // compare ID, ignore if repetitive query
  if ( find_in_IDlist(IDlist, packet->ID) == 1 ){
    return 0;
  }

  // if found in folder, then return the msg back to query host
  if ( find_in_dir(Dir, packet->filename) == 1 ){
    // shoot the response to initiator of query
    gen_packet(&respon_packet,
               packet->filename,
               RESPON,
               0);

    sock_sendto(packet->host_in_addr, &respon_packet);
  }
  // not found, flood to neighbors
  else {
    // update packet, update TTL, return if TTL hits 0
    if (-- packet->TTL <= 0){
      return 0;
    }

    // shoot the packet
    int i;
    int num_neighbors = neighbors->num_neighbors;
    neighbor_t *neighbor_list = neighbors->neighbor_list;

    for (i = 0; i < num_neighbors; ++ i){
      unsigned long neighbor_addr = neighbors->neighbor_list[i].;

      // filter out the sender, avoid loops
      if (neighbor_addr == client_ipaddr){
        continue;
      }

      // send to this neighbor
      sock_sendto(sockfd,
                  packet);

    } // for
  } // else not found, flood to neighbors

  return 0;
}


// handle response packet
// param: packet - the packet to send
// return: 0 on success -1 on error
int server_handle_respon(packet_t *packet){

  unsigned long host_in_addr = packet->host_in_addr;
  char host_ip[16];

  // TODO: translate hostname
  
  // Display info here
  printf ("File %s found on %s\n", packet->payload_data, hostname);
          
  return 0;
}
