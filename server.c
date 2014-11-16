/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: server.h
 * descript: The query flooding protocol server 
 */


#include "network.h"
#include "adt.h"
#include "server.h"
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>


// server worker thread function
// param: arg - argument
void *server_worker(void *arg){
  // init params
  server_arg_t *_arg = (server_arg_t *)arg;

  IDlist_t *IDlist = _arg->IDlist;
  int portno = _arg->portno;
  char *Dir = _arg->Dir;
  neighbors_t *neighbors = _arg->neighbors;
  pthread_mutex_t *lock = _arg->lock;

  // init server socket and packet
  int sockfd = new_udp_sock();
  packet_t packet;
  unsigned long client_ipaddr;

  if ( udp_bind(sockfd, portno) == -1 ){
    ERROR("Could not bind to port\n");
  }

  // main while loop
  while (1){
    // accept new packets
    client_ipaddr = sock_recvfrom(sockfd, (void *)&packet, sizeof(packet));
    unsigned char type = packet.Descript;

    // react accordingly
    if (type == CONNECT){
      server_handle_connect(neighbors, &packet, lock);
    }
    else if (type == QUERY){
      server_handle_query(_arg, &packet);
    }
    else if (type == RESPON){
      server_handle_respon(&packet);
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
    if ( strcmp(filename, dirstruct->d_name) == 0 ){
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
                          packet_t *packet,
                          pthread_mutex_t *lock){

  char *hostname = packet->hostname;
  unsigned long host_in_addr;

  host_in_addr = find_host_addr(hostname);

  pthread_mutex_lock(lock);

  // update the neighbors
  if ( !find_neighbor(host_in_addr, neighbors) ){

    push_neighbor(neighbors, host_in_addr);

    printf( "New neighbor connecting: %s\n", 
            find_host_ip(host_in_addr) );
  }

  pthread_mutex_unlock(lock);
  return 0;
}


// handle query packet
// param: server_arg arg
//        packet received packet
// return: 0 on success -1 on error
int server_handle_query(server_arg_t *args, packet_t *packet){

  packet_t respon_packet;

  char *Dir = args->Dir;
  IDlist_t *IDlist = args->IDlist;
  int portno = args->portno;
  neighbors_t *neighbors = args->neighbors;
  pthread_mutex_t *lock = args->lock;

  unsigned long client_in_addr = find_host_addr(packet->hostname);

  // compare ID, ignore if repetitive query
  pthread_mutex_lock(lock);
  if ( find_in_IDlist(IDlist, packet->ID) == 1 ){
    return 0;
  }
  add_to_IDlist(IDlist, packet->ID);
  pthread_mutex_unlock(lock);

  // if found in folder, then return the msg back to query host
  if ( find_in_dir(Dir, packet->payload_data) == 1 ){
    // shoot the response to initiator of query
    gen_packet(&respon_packet,
               packet->payload_data,
               RESPON,
               0);
    sock_sendto(client_in_addr, portno, &respon_packet, sizeof(packet_t));

    printf ("File %s found, responding to query\n", packet->payload_data);
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
      unsigned long neighbor_addr = neighbors->neighbor_list[i].ip_addr;

      // filter out the sender, avoid loops
      if (neighbor_addr == client_in_addr){
        continue;
      }

      // send to this neighbor
      sock_sendto(neighbor_addr, portno, packet, sizeof(packet_t));

    } // for
  } // else not found, flood to neighbors

  return 0;
}


// handle response packet
// param: packet - the packet to send
// return: 0 on success -1 on error
int server_handle_respon(packet_t *packet){

  // Display info here
  printf ("File %s found on %s\n", packet->payload_data, packet->hostname);
          
  return 0;
}
