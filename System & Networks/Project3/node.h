/* Darrell Percey && Andrew Boven
 * File: node.h
 * Project 3 || System Network II
 * 
 * This program simulates routers in a network forwarding packets that
 * contain neighbor information to the other routers on the network.
 * this allows the "routers" to build a forwarding table which they can
 * find the fastest pathway to to get to other nodes.
 *
 *
 */
 
#ifndef _NODE_H
#define _NODE_H

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

#define LSIZE 50
#define SIZE 15
#define IPSIZE 16
	
	/* Structures:
	 * Packet - packets that will be used to send across the network
	 * forwardTable - Link listed structure for holding a forwarding table
	 */
	typedef struct forwardTable* forP;

	struct packet{
		char orgSender;
		char currSender;
		int hops;
		char label[SIZE];
		int distance[SIZE];
	} packet;
	
	struct forwardTable{
		char dest;
		int distance;
		char path;
		forP next;
	} forwardTable;
	
/*
* Function:  checkReadyStatus
* 
* Description:
* Waits for the user to enter y to start the routing function
* this gives the user time to boot up all "routers" so they can
* begin passing messages together.
*
*/
	void checkReadyStatus();
	
/*
* Function:  startRouting
*
* Params:
* label - the label of "THIS" router.
* port - the port number used for this "THIS" router
* numRouter - the amount of routers on the network
* file - the file that holds neighbor information for "THIS" router
* topTable - link listed that holds the shortest paths dest/distance/path
*
* Return:
* if a 1 is returned there was an error, otherwise return 0
*
* Description:
* This is the main driver of the program it will set up the socket using 
* various functions and proceed to sending out to the neighbors. Once it recieves
* a "packet" it will decode and forward it to the neighbors.
*
*/
	int startRouting(char label, int port, int numRouter, char* file, forP topTable);
	
/*
* Function:  orginalSenderCheck
*
* Params:
* recv - a packet that was received on the network testing for the orginal sender
* orgSenderList - a list of orginal senders that have received packets from
*
* Return:
* counter - sends the amount of orginal senders
*
* Description:
* This takes a receiveing packet and test if the orignal sender has sent a packet
* to this node before. If it has it will ignore it otherwise it will add it to the
* list and update the counter.
*
*/
	int orginalSenderCheck(struct packet recv, char *orgSenderList);
	
/*
* Function:  printForwardingTable
*
* Params:
*
* Return:
*
* Description:
* Prints the final forwarding table form the link listed.
*
*/
	void printForwardingTable(forP top);

/*
* Function:  generateForwardPacket
*
* Params:
* recv - packet received on the network to transfer to the forwarding packet
* forward - pointer to update the forward packet which will be sent out.
* label - "THIS" routers label for comparison in the received packet
* neighborLabel - list of neighbors labels to "THIS" router.
* neighborAmt - counter for the amount of neighbors "THIS" router has.
* top - pointer to the linked list of the forwarding table.
* 
* Return:
* return a 2 if the hops are out; otherwise return a 0
*
* Description:
* Transfers all the information to the forwarding packet from the receving packet with updated 
* information. This will change the distances before forwarding and will change the current 
* sender to reflect itself.
*
*/
	int generateForwardPacket(struct packet recv, struct packet *forward, char label, char *neighborLabel, int neighborAmt, forP top);
	
/*
* Function:  fillForwardTable
*
* Params:
* label - passed in label from the receving packet
* dist - the distance of the label from 
* path - the path (which neighbor) that needs to be taken to get to label(dest)
* top - pointer to linked list of the forwarding table
* 
* Return:
*
* Description:
* Fills in the forwarding table linked list if it is a new entry then
* make a new node otherwise test the old distance against the newly arrived
* distance. 
*
*/
	void fillForwardTable(char label, int dist, char path, forP top);
	
/*
* Function:  sendNeighbors
*
* Params:
* send - the packet which will be sent (to flood) the network.
* neighborIP - all neighbors IPs
* neighborPort - contains all neighbors ports
* sock - socket used to send to the neighbors
* dest - address information to send over the socket
* addrlen - address lenght for socklen_t
* 
* Return:
* return 1 if there is an error; otherwise return 0
*
* Description:
* Sends the packet that is put in as a parameter "send" to all the neighbor
* routers using the IPs and Port stored in neighborIP and neighborPort
*
*/
	int sendNeighbors(struct packet send, char neighborIP[SIZE][IPSIZE], int *neighborPort, int sock, struct sockaddr_in *dest, socklen_t addrlen);
	
/*
* Function:  makePacket
*
* Params:
* send - the packet which will be sent to neighbors about neighbor information
* top - pointer to linked list of forwarding table
* numRouter - the amount of routers in total on the network
* myLabel - the label of "THIS" router.
* 
* Return:
* return 0 
*
* Description:
* Generated a packet which will be used to flood the network from
* "THIS" router. It will contain the information of the neighbor routers.
*
*/
	int makePacket(struct packet *send, forP top, int numRouter, char myLabel);
	
/*
* Function:  findNeighbors
*
* Params:
* neighborIP - used to store the neighbors' IPs 
* neighborPort - used to store the ports of the neighbors
* neighborLabel - used to store the neighbors Labels 
* file - name of the text file that should be read from
* top - pointer to forwarding table linked list
* 
* Return:
* return 1 if there is an error; otherwise return 0
*
* Description:
* Started by reading a line at a time from the file that was inputed. It will tokenize
* the string into pieces and put each piece into the apporiate spot. Then after it puts
* all the information into label,port, and ip it will then add the neighbors to the forwarding
* table because they are known.
*
*/
	int findNeighbors(char neighborIP[SIZE][IPSIZE],int *neighborPort, char* neighborLabel, char* file, forP top);
	
/*
* Function:  setUpSocket
*
* Params:
* port - the port of "THIS" router.
* my_addr - address information of "THIS" router
* dest - address information of destinations wanted to send to.
* 
* Return:
*
* Description:
* Builds and fills up the address information for my_addr so it can be used to bind
* the socket. Dest is given a family and will be used later in sendNeighbors().
*
*/
	void setUpSocket(int port, struct sockaddr_in *my_addr, struct sockaddr_in *dest);
	
/*
* Function:  findTableEntry
*
* Params:
* top - top of the forwarding table linked list
* label - label of the entry we want to find
* 
* Return:
* returns NULL if node isn't found; otherwise return the Node*
*
* Description:
* Scans through the forwarding table and tries to find the node of
* the label that is passed in. Once found it will return that node*
*
*/
	forP findTableEntry(forP top, char label);
	
/*
* Function:  createNewNode
*
* Params:
* 
* Return:
* returns a pointer to the new node
*
* Description:
* Creates a new node to start the linked list.
*
*/
	forP createNewNode();
	
/*
* Function:  findTableEntry
*
* Params:
* destLabel - the label of the router which is our destination 
* dist - the distance of the router which we want to travel to
* pathLabel - the path (neighbor) we must take to get to destination
* 
* Return:
* returns a pointer to the newly added node
*
* Description:
* This makes a new node and fills in the information so that it can
* be added to the linked list.
*
*/
	forP addNewNode(char destLabel, int dist, char pathLabel);

#endif