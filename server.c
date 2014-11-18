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
    ERROR("[DEBUG] Could not bind to port\n");
  }

  printf("[DEBUG] Successfully bind to port %d\n", portno);

  // main while loop
  while (1){
    // accept new packets
    client_ipaddr = sock_recvfrom(sockfd, (void *)&packet, sizeof(packet_t));
    unsigned char type = packet.Descript;

    printf("[DEBUG] Received new packet: ");

    switch(type){
    case 0: printf("CONNECT package\n"); break;
    case 1: printf("QUERY package\n"); break;
    case 2: printf("RESPON package\n"); break;
    default: printf("WTF package?\n"); break;
    }

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
  if ( !if_find_neighbor(host_in_addr, neighbors) ){

    push_neighbor(neighbors, host_in_addr);

    printf( "[INFO] New neighbor connecting request. From IP: %s\n", 
            find_host_ip(host_in_addr) );
  }

  pthread_mutex_unlock(lock);

  printf("[INFO] New neighbor connected!\n");
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
    printf("[INFO] Packet with duplicate ID flooding back. Ignoring\n");
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

    printf("[INFO] File %s found, responding to query.\n", packet->payload_data);
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
      unsigned long neighbor_addr = neighbors->neighbor_list[i].inaddr;

      // filter out the sender, avoid loops
      if (neighbor_addr == client_in_addr){
        continue;
      }

      // send to this neighbor
      sock_sendto(neighbor_addr, portno, packet, sizeof(packet_t));

      printf("[INFO] Not found, flooding to next neighbor IP: %s\n", find_host_ip(neighbor_addr));
    } // for

  } // else not found, flood to neighbors

  return 0;
}


// handle response packet
// param: packet - the packet to send
// return: 0 on success -1 on error
int server_handle_respon(packet_t *packet){

  // Display info here
  printf("\n[INFO] File %s found on %s, with IP: %s\n\n", 
         packet->payload_data, 
         packet->hostname, 
         find_host_ip(find_host_addr(packet->hostname)) );
          
  return 0;
}
