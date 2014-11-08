/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: adt.h
 * descript: Define datatypes and data manipulation functions
 */


#ifndef __ADT_H__
#define __ADT_H__


/*
 * Sender packet format
 */
typedef packet {
  /* ID to avoid handling same packet twice */
  unsigned short ID; 
  
  /* Descriptor: what type of packet */
  unsigned char Descript;

  /* Time To Live */
  unsigned char TTL;
  
  /* Sender Host IP */
  int IP;

  /* Query data */
  char QueryData[32];

} packet_t;


/* generate a random ID for each payload */
unsigned short gen_ID();


#endif
