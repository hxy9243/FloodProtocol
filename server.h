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

} server_arg_t;


// server thread worker function
void server_work(void *arg);


// find in directories
int find_in_dir(char *Dir, char *filename);



#endif
