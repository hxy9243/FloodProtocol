/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: adt.c
 * descript: Define datatypes and data manipulation functions
 */


#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "network.h"
#include "adt.h"
#include "config.h"


// generate a random ID for each payload 
int gen_ID(){
  srand(time(NULL));
  return rand();
}


// generate sending packet according to params, returns ID
// return 0 on success -1 on error
int gen_packet(packet_t *packet, char *filename, int type, int TTL){
  char hostname[MAX_STRLEN];

  packet->ID = gen_ID();
  packet->TTL = (unsigned char)TTL;
  packet->Descript = (unsigned char)type;
  
  gethostname(hostname, MAX_STRLEN);

  strcpy(packet->hostname, hostname);

  if (filename != NULL){
    strcpy(packet->payload_data, filename);
  }

  return 0;
}


/* 
 * ID list related functions
 */
// init IDlist
int init_IDlist(IDlist_t *IDlist){
  IDlist->num = 0;
}

// Add to ID list
int add_to_IDlist(IDlist_t *IDlist, int ID){
  int index = IDlist->num;
  IDlist->IDs[index] = ID;

  ++ IDlist->num;
  if (ID >= MAX_IDSIZE){
    return -1;
  }
  return IDlist->num;
}


// find in ID list
// return 1 on found, 0 on not found
int find_in_IDlist(IDlist_t *IDlist, int ID){
  int num = IDlist->num;
  int i;

  for (i = 0; i < num; ++ i){
    if (IDlist->IDs[i] == ID){
      return 1;
    }
  }

  return 0;
}


// init neighbor structure
// param: neighbors - reference to neighbors
// return: 0 on success -1 on error
int init_neighbors(neighbors_t *neighbors){
  neighbors->num_neighbors = 0;

  printf("Num of neighbors inited to %d\n", neighbors->num_neighbors);

  return 0;
}


// push a new neighbor into the neighbor data structure
// param: neighbors - the neighbors info data struct
//       neighbor_host_in_addr - host inet addr
//       sockfd - the corresponding sock to neighbor
// return: the total num of neighbors after push
//        -1 if any failure
int push_neighbor(neighbors_t *neighbors, unsigned long host_in_addr){
  int index = neighbors->num_neighbors;
  unsigned long new_ip;
  int new_sockfd;
  neighbor_t *new_neighbor = &(neighbors->neighbor_list[index]);
  
  neighbors->num_neighbors ++;
  

  printf("Num of neighbors is now: %d\n", index);

  // TODO: alloc new mem for neighbor instead of dropping
  if (neighbors->num_neighbors >= MAX_NEIGHBOR){
    WARN("Exceeds max neighbor number\n");
    return -1;
  }


  // find out about neighbor ip
  // new_sockfd = new_udp_sock(new_ip);
  
  // push to neighbor struct
  new_neighbor->ip_addr = new_ip;
  // new_neighbor->sockfd = new_sockfd;

  return index;
}


/*
 * establish connection to all neighbors
 * param: neighbors - the neighbors info data struct
 * return: 0 on success, -1 otherwise
 */
int connect_neighbors(neighbors_t *neighbors, int portno){

  int i;
  packet_t packet;
  int num_neighbors = neighbors->num_neighbors;
  neighbor_t *neighbor;

  printf ("%d neighbors to connect\n", num_neighbors);

  // send to all neighbors
  for (i = 0; i < num_neighbors; ++i){

    // gen packet
    gen_packet(&packet,
               NULL,
               CONNECT,
               0);
               
    // send to the neighbor
    neighbor = &neighbors->neighbor_list[i];
    sock_sendto(neighbor->ip_addr, portno, 
                (void *)&packet, sizeof(packet));

    printf("Connected to neighbor %s\n",
	   find_host_ip(neighbor->ip_addr));

  }
  
  return 0;
}


// find neighbor in neighbors
// param: host_in_addr - bin ip
//        neighbors 
// return: 1 on found, 0 on not found
int find_neighbor(unsigned long host_in_addr, neighbors_t *neighbors){
  int i;

  for (i = 0; i < neighbors->num_neighbors; ++ i){
    if (neighbors->neighbor_list[i].ip_addr == host_in_addr){
      return 1;
    }
  }
  return 0;
} 
