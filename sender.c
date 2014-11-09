/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: sender.c
 * descript: Define sender related function
 */


#include "sender.h"
#include "config.h"

#include <string.h>


/*
 * read in the neighbor config from file
 * param: filename 
 * return: neighbor_num
 */
int read_neighbor_config(char *filename, neighbor_t *neighbors){

  FILE *fp;
  char neighbor_name[32];
  int neighbor_port;
  neighbor_t *neighbor;
  int neighbor_num = 0;

  // alloc mem for neighbor structure
  if ( neighbors = (neighbor_t *)malloc(sizeof(neighbor_t) * NEIGHRBOR_SIZE) == NULL ){
    ERROR("ERROR MALLOC MEM");
  }

  // open file
  if ( (fp = fopen(CONFIG_FILE, "r")) == NULL ){
    ERROR("Cannot open config file");
  }

  // read and push new address to array
  while ( fscanf(fp, "%s%d\n", neighbor_name, &neighbor_port) != EOF ){
    neighbor = &neighbors[neighbor_num];

    strcpy(neighbor->hostname, neighbor_name);
    neighbors->portno = neighbor_pot;

    ++ neighbor_num;

    printf ("neighbor: %s : %d\n", neighbor_ip, neighbor_port);
  }

  return neighbor_num;
}

