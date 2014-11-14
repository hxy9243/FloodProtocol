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

#include "network.h"
#include "adt.h"
#include "config.h"


// generate a random ID for each payload 
int gen_ID();

// generate sending packet according to params, returns ID
int gen_packet(packet_t *packet, char *filename, int type, int TTL);

// update packet, return TTL
int update_packet(packet_t *packet);


/* 
 * ID list related functions
 */
// init IDlist
int init_IDlist(IDlist_t *IDlist);

// Add to ID list
void add_to_IDlist(IDlist_t *IDlist, int ID); 

// find in ID list
int find_in_IDlist(IDlist_t *IDlist, int ID);

// free IDlist
void free_IDlist(IDlist_t *IDlist);


/*
 * push a new neighbor into the neighbor data structure
 * param: neighbors - the neighbors info data struct
 *        neighbor_hostname - hostname
 * return: the total num of neighbors after push
 *         -1 if any failure
 */
int push_neighbor(neighbor_t *neighbors, char *neighbor_hostname){

  int index = ++ neighbor->num_neighbors;
  unsigned long new_ip;
  int new_sockfd;
  neighbor_t *new_neighbor = &neighbors->neighbor_list[index];

  // TODO: alloc new mem for neighbor instead of dropping
  if (index >= MAX_NEIGHBOR){
    WARN("Exceeds max neighbor number");
    return -1;
  }

  // find out about neighbor ip
  new_ip = find_host_ip(neighbor_hostname);
  // new_sockfd = new_udp_sock(new_ip);

  // push to neighbor struct
  strcpy(new_neighbor->hostname, neighbor_hostname);
  new_neighbor->ip_addr = new_ip;
  // new_neighbor->sockfd = new_sockfd;

  return index;
}


/*
 * establish connection to all neighbors
 * param: neighbors - the neighbors info data struct
 * return: 0 on success, -1 otherwise
 */
int connect_neighbors(neighbors_t *neighbors){

  int i;
  packet_t packet;
  int num_neighbors = neighbors->num_neighbors;
  neighbor_t *neighbor;

  // send to all neighbors
  for (i = 0; i < num_neighbors; ++){
    // gen packet
    gen_packet(&packet,
               NULL,
               CONNECT,
               0);
               
    // send to the neighbor
    neighbor = &neighbors->neighbor_list[i];
    sendto(neighbor->fd, (void *)packet, sizeof(packet));

  }
  
  return 0;

}
