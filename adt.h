/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: adt.h
 * descript: Define datatypes and data manipulation functions
 */


#ifndef __ADT_H__
#define __ADT_H__


#include "config.h"

// define packet type
#define CONNECT 0
#define QUERY 1
#define RESPON 2


/*
 * Sender packet format
 */
typedef struct packet {
  // ID to avoid handling same packet twice 
  int ID; 
  
  // Descriptor: what type of packet
  unsigned char Descript;

  // Time To Live 
  unsigned char TTL;
  
  // Query or responder host ip
  char hostname[MAX_STRLEN];
  
  // payload, the name of the search string 
  char payload_data[MAX_STRLEN];

} packet_t;


/*
 * ID list - a list for query ID history
 */
typedef struct IDlist {
  // an array for all IDs 
  int IDs[MAX_IDSIZE];

  // num of all IDs 
  int num;
} IDlist_t;


/*
 * Neighbor information
 */
typedef struct neighbor_addr {
  // neighbors hostname 
  char hostname[MAX_STRLEN];

  // the binary addr, load with inet_ntop
  unsigned long ip_addr;
  
  // socket file
  int sockfd;

} neighbor_t;


typedef struct neighbors {
  // the array of neighbors
  neighbor_t *neighbor_list;

  // the num of neighbors
  int num_neighbors;
} neighbors_t;


/*
 * Query packet related functions
 */
// generate a random ID for each payload 
int gen_ID();

// generate sending packet according to params, returns ID
int gen_packet(packet_t *packet, char *filename, int type, int TTL);


/* 
 * ID list related functions
 */
// init IDlist
int init_IDlist(IDlist_t *IDlist);

// Add to ID list
int add_to_IDlist(IDlist_t *IDlist, int ID); 

// find in ID list
int find_in_IDlist(IDlist_t *IDlist, int ID);


/*
 * Neighbor related functions
 */
// push in a new neighbor
int push_neighbor(neighbors_t *neighbors, unsigned long host_in_addr);

// read in neighbor config
int read_neighbor_config(char *filename, neighbors_t *neighbors);

// connect to all neighbors
int connect_neighbors(neighbors_t *neighbors, int portno);

// find neighbor in neighbors
int find_neighbor(unsigned long host_in_addr, neighbors_t *neighbors); 


#endif
