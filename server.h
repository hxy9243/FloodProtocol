/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: server.h
 * descript: The query flooding protocol server 
 */


#ifndef __SERVER_H__
#define __SERVER_H__


#include "config.h"
#include "adt.h"

#include <sys/types.h>
#include <unistd.h>

/*
 * Define params required for server 
 */
typedef struct server_arg {

  // ID list for query history
  IDlist_t *IDlist;

  // server port number
  int portno;

  // Dir to read
  char *Dir;

  // neighbor info
  neighbors_t *neighbors;

  // mutex
  pthread_mutex_t *lock;

} server_arg_t;


// server thread worker function
void *server_worker(void *arg);

// find in directories
int find_in_dir(char *Dir, char *filename);

// handle connect packet
int server_handle_connect(neighbors_t *neighbors,
                          packet_t *packet,
                          pthread_mutex_t *lock);

// handle query packet
int server_handle_query(server_arg_t *args, packet_t *packet);

// handle response packet
int server_handle_respon(packet_t *packet);



#endif
