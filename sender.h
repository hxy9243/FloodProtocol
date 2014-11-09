/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: sender.h
 * descript: Define sender related function
 */


#ifndef __SENDER_H__
#define __SENDER_H__


#define NEIGHBOR_SIZE 8


/*
 * Neighbor address
 */
typedef struct neighbor_addr {
  char hostname[32];
  int portno;
} neighbor_t;


/*
 * Neighbor related functions
 */

// generate sending packet according to params, returns ID
int gen_packet(packet_t *packet, char *filename, int type, int TTL);


// read in neighbor config
int read_neighbor_config(char *filename, neighbor_t *neighbors);




#endif
