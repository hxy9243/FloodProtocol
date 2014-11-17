/*
 * cs257 Assignment 4
 * Implement query flooding protocol
 *
 * filename: main.h
 * descript: Main helper functions
 */

#include <stdio.h>


#ifndef __MAIN_H__
#define __MAIN_H__


#define ERROR(x) fprintf(stderr, x);exit(1)
#define WARN(x) fprintf(stderr, x)
#define INFO(x) fprintf(stdout, x)

#define CONFIG_FILE "config"

#define MAX_NEIGHBOR 16
#define MAX_STRLEN 32
#define MAX_IDSIZE 64

#endif

