/****************************************************************/
/* Darrell Percey	&&  Andew Boven		                       	*/
/* rdtNetwork.h                                                 */
/* Project 2 || System Networks II							   	*/
/*               											   	*/
/*	Header file for RDT network. Simulates the network			*/
/* to cause artifical corruption, delay, and lost of packets.	*/
/* This allows us to create our own	environment for				*/
/*  testing our RDT 3.0 sender and receiver.     				*/
/*                                                             	*/
/****************************************************************/

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


//Packet struct used by all three programs
//The segment is only 10bytes as per project assignment
// 1byte-sequence# 2bytes-checksum 7bytes-message = 10bytes
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


/*
* Function:  controlNetwork
* 
* Description:
* Receives packets and forwards them to the 
* destIP/destPort in the packet. It will also
* emulate a network by sometimes corrupting
* losting and delaying packets.
*
*/
int controlNetwork (int localPort, int lost, int delay, int corrupt);

/*
* Function:  createSocketInfo
* 
* Description:
* Takes in the information provided and finds the
* hostname of self address. Then it applies this
* information to the sockaddr_in struct to be used
* by the socket.
*
*/
void createSocketInfo(int localPort,struct sockaddr_in *my_addr, struct sockaddr_in *source_addr);
#endif