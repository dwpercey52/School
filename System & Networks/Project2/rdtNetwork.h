
#ifndef _RDT_NETWORK_H
#define _RDT_NETWORK_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <netdb.h>

#define SIZE 1000
#define IPSIZE 16


typedef struct packet* pack;

struct packet{
	char destIP[IPSIZE];
	int destPort;
	char srcIP[IPSIZE];
	int srcPort;
	//Segment 10bytes below
	int8_t seqNumber;   //8-bits for 1 byte
	uint16_t checkSum;		//2bytes for short (unsigned for overflow)
	char data[7];		//remaining 7 bytes for data "segment"
} packet;


int controlNetwork (int localPort);
void createSocketInfo(int localPort,struct sockaddr_in *my_addr, struct sockaddr_in *source_addr);
#endif