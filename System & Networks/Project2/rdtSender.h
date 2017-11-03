/**
 * This file describes the function(s) to be implemented by an RDT sender.
 *
 * @author Thomas Reichherzer
 * @date 2/22/2017
 * @info Systems and Networks II
 * @info Project 2
 *
 */

#ifndef _RDT_SENDER_H
#define _RDT_SENDER_H

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
#include <sys/select.h>
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
 * Sends a message to an RDT receiver on a specified host and port using a network simulator
 * program for transporting messages to the receiver.
 * 
 * @param localPort - the local port to bind the socket
 * @param netwHost  - the name of the host that runs the network simulator
 * @param netwPort  - the number of the port on which the network simulator listens
 * @param destHost  - the name of the host that runs the receiver
 * @param destPort  - the number of the port on which the receiver listens
 * @param message   - the entire text message to be sent to the receiver; the message is \0 terminated
 *
 * @return 0, if no error; otherwise, a negative number indicating the error
 */
int sendMessage (int localPort, char* netwhost, int netwPort, char* desthost, int destPort, char* message);
void findDestIP(char* dest, char *desthost);
int makePacket(pack curr, pack prev, int localPort, char* desthost, int destPort, struct sockaddr_in addr, char* seg, int* strCntr, int8_t seq);
int generateChecksum(char* seg);
void getUserInput(char *message);
void createSocketInfo(int localPort,char *netwhost,int netwPort,struct sockaddr_in *my_addr, struct sockaddr_in *network);
#endif

