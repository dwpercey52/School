/**
 * This file describes the functions to be implemented by an RDT receiver.
 *
 * @author Thomas Reichherzer
 * @date 2/22/2017
 * @info Systems and Networks II
 * @info Project 2
 *
 */

 #ifndef _RDT_RECEIVER_H
 #define _RDT_RECEIVER_H
 
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

/**
 * Receives a message from an RDT sender on a specified port.
 *
 * @param port - the number of the port on which the receiver listens to receive messages
 *
 * @return the complete text message received by a sender or NULL if an error occurred
 */
char* receiveMessage (int port);
void generateAck(pack recvPacket);
int generateChecksum(char* seg);
void createSocketInfo(int localPort,struct sockaddr_in *my_addr);


#endif
