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
#define QUERY 0
#define RESPON 1


/*
 * Sender packet format
 */
typedef struct packet {
  /* ID to avoid handling same packet twice */
  unsigned int ID; 
  
  /* Descriptor: what type of packet */
  unsigned char Descript;

  /* Time To Live */
  unsigned char TTL;
  
  /* Query or responder hostname */
  char hostname[MAX_STRLEN];

  /* payload, the name of the search string */
  char payload_data[MAX_STRLEN];

} packet_t;


/*
 * ID list - a list for query ID history
 */
typedef struct IDlist {
  /* an array for all IDs */
  unsigned int *IDs;

  /* num of all IDs */
  int num;
} IDlist_t;


/*
 * Query packet related functions
 */
// generate a random ID for each payload 
unsigned short gen_ID();



/* 
 * ID list related functions
 */
// init IDlist
int init_IDlist(IDlist_t *IDlist);

// Add to ID list
void add_to_IDlist(IDlist_t *IDlist, int ID); 

// search in ID list
int search_in_IDlist(IDlist_t *IDlist, int ID);

// free IDlist
void free_IDlist(IDlist_t *IDlist);


/*
 * Helper functions
 */



#endif
