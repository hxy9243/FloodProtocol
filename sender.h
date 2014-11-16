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
 * Neighbor related functions
 */
// sender flood requets to all neighbors
int flood_request(neighbors_t *neighbors, int portno, packet_t *packet, int size);


#endif
