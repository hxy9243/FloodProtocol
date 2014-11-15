/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: sender.c
 * descript: Define sender related function
 */


#include "sender.h"
#include "config.h"
#include "network.h"

#include <string.h>

// sender flood requets to all neighbors
// param:
// return: 0 on success -1 on error
int flood_request(neighbors_t *neighbors, packet_t *packet, int size){
  int i;
  int num_neighbors = neighbors->num_neighbors;
  unsigned long ip_addr;
    
  for (i = 0; i < num_neighbors; ++ i){
    ip_addr = neighbors->neighbor_list[i].ip_addr;

    if (sock_sendto(ip_addr, packet, size) < 0) {
      return -1;
    }
  }
  return 0;
}
