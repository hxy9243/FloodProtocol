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


// recv from a socket
int sock_recvfrom(int sockfd, void *buffer, int size);

// recv to a socket
int sock_sendto(int sockfd, void *buffer, int size);

// find hostname binary ip form
unsigned long find_host_ip(char *hostname);

// create new udp socket
int new_udp_sock(unsigned long ip_addr);


#endif
