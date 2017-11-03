/****************************************************************/
/* Darrell Percey	&& Andrew Boven	                           	*/
/* bbclient.c                                                   */
/* Project 1 || System Networks II							   	*/
/*               											   	*/
/*	This is the client program. It will either connect to a		*/
/*  server or a peer to establish a ring connection so that     */
/*  it can operate on a shared file making a bullentin board    */
/*                                                             	*/
/****************************************************************/

#ifndef bbclient_h
#define bbclient_h
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
#define SIZE 100
#define TOK 4


	struct sockaddr_in serv_addr, my_addr;
	socklen_t socklen = 0;
	pthread_mutex_t mutex;
	int len = sizeof(serv_addr);
	int sockfd = 0, listenSock = 0;
	int listenPort = 0;
	char fileName[SIZE];
	//Token 0 = false, 1 = true
	int token = -1;
	//0 = false 1 = true
	int quitToken = 0;
	
	
	/*
* Function:  joinRing()
* 
* Description:
* Called when the user wants to join a ring
* that is already created. This directly connects
* to another peer and ask them the information to
* join the ring.
*
*/
	void joinRing(char* ip, char* port);
	
	/*
* Function:  executeUserAction()
* 
* Description:
* depending on the code that is passed in from act
* this function will execute the need I/O on the file
* assuming the user has the token to do so.
*
*/
	void executeUserAction(int act, char* file, char* inputS, int inputD);
	
	/*
* Function:  checkUserInput()
* 
* Description:
* This verifies that the user put a number from the menu
* either 1-4 for one of the acts that the user can request.
*
*/
	int checkUserInput(char* input);
	
	/*
* Function:  exitFunction()
* 
* Description:
* This notifies the peer that is sending to this peer
* that it is exiting the ring so it passed the information of
* it's sender to the recevier.
*
*/
	void exitFunction();
	
	/*
* Function:  printUserMenu()
* 
* Description:
* prints the menu for the user to read.
* this is done every rotation so that the user
* doesn't have to remember the commands.
*
*/
	void printUserMenu();
	
	/*
* Function:  recvFunc()
* 
* Description:
* This is the second thread that handles all recvfrom calls
* so that the user can choose their action or write to the bullentin
* before receiveing the token. This also allows for other users to
* join/exit while the user is doing Input for the file.
*
*/
	void *recvFunc();
	
	/*
* Function:  connectToServer()
* 
* Description:
* If the -new option is put on the command line
* it calls this function so that the user will connect
* to the server to get information about it's peers.
*
*/
	void connectToServer(char *argv[]);
	
	/*
* Function:  createRingSocket()
* 
* Description:
* Builds the socket for the ring depending on the 
* information that was provided by the server.
*
*/
	void createRingSocket(char* ip, char* port);
	
	/*
* Function:  makeListenSocket()
* 
* Description:
* Creates the socket for the client to listen on.
*
*/
	int makeListenSocket(char* port);
	
	/*
* Function:  generateToken()
* 
* Description:
* Generates two random number and adds them together
* generating two numbers lessens the chance that the same
* token generation number will be picked. Once they generateToken
* they then find the highest token to decide who gets the first token.
*
*/
	int generateToken();
	
	/*
* Function:  findFirstToken()
* 
* Description:
* Passes around values till the highest value is found.
* Once found it is passed around and whoever matches that
* value is the first token.
*
*/
	void findFirstToken(int tokCode);

#endif