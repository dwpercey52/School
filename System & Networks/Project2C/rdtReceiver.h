/**
 * This file describes the functions to be implemented by an RDT receiver.
 *
 * @author Thomas Reichherzer
 * @date 2/22/2017
 * @info Systems and Networks II
 * @info Project 2
 *
 */
 /****************************************************************/
/* Darrell Percey	&&  Andew Boven		                       	*/
/* rdtReceiver.h                                                */
/* Project 2 || System Networks II							   	*/
/*               											   	*/
/*	This program allows us to implement a 3.0 RDT receiver. 	*/
/*  This will allow for realiable transfer across the network 	*/
/*  even if the packets are lost, delayed, or corrupted.   		*/
/*                                                             	*/
/****************************************************************/

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

/**
 * Receives a message from an RDT sender on a specified port.
 *
 * @param port - the number of the port on which the receiver listens to receive messages
 *
 * @return the complete text message received by a sender or NULL if an error occurred
 */
 
 /*
* Function:  receiveMessage
* 
* Description:
* Main part of the program that receives messages and
* replies using RDT 3.0 protocol. It will ACK packets that
* have the wrong seq number to alert the sender, and it will
* drop corrupt packets. This allows for the sender to respond
* properly
*
*/
char* receiveMessage (int port);

/*
* Function:  generateACK
* 
* Description:
* Takes the source address and port and switches
* it with the destination address and port. This
* sends back an ACK that it received that packet.
*
*/
void generateAck(pack recvPacket);

/*
* Function:  generateChecksum
* 
* Description:
* Generates a checksum so the receiver and
* sender have a comparision for testing if 
* the packet is corrupt or not.
*
*/
int generateChecksum(char* seg);

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
void createSocketInfo(int localPort,struct sockaddr_in *my_addr);

#endif
