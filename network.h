/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: network.h
 * descript: Define network interface for send, recv
 */



#ifndef __NETWORK_H__
#define __NETWORK_H__


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


// find hostname binary ip form
unsigned long find_host_addr(char *hostname);

// find hostname char readable form
char *find_host_ip(unsigned long host_in_addr);

// create new udp socket
int new_udp_sock(unsigned long ip_addr);

// recv from a socket, return bin ip addr
unsigned long sock_recvfrom(int sockfd, void *buffer, int size);

// send to a socket
int sock_sendto(unsigned long ip_addr, void *buffer, int size);


#endif
