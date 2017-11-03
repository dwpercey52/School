/****************************************************************/
/* Darrell Percey	&&  Andrew Boven                           	*/
/* bbfile.c                                           		    */
/* Project 1 || System Networks II							   	*/
/*               											   	*/
/*	This program handles all the file operations done to the	*/
/*  shared file or "bullentin board". None of these actions 	*/
/*  can be executed till the user has the token in their 		*/
/*  possension												    */
/*                                                             	*/
/****************************************************************/
#ifndef bbfile_h
#define bbfile_h
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


/*
* Function:  writeToFile()
* 
* Description:
* This opens the file and writes to the file a new 
* input from the user. It will find out how many lines
* are in the documents and place the header and footer on it.
*
*/
	void writeToFile(char* file, char* input);
	
/*
* Function:  readMessage()
* 
* Description:
* Reads the message of the # the person wants.
* If there are no messages in the board it will inform
* the user, if there are messages but the user picked a
* number that was to high, it will tell how many.
*
*/
	void readMessage(char* file, int messageNum);
	
/*
* Function:  listMessages()
* 
* Description:
* Post all messages to the stdout for the user
*
*/
	void listMessages(char* file);
	
/*
* Function:  findMessageAmount()
* 
* Description:
* Goes through the entire file to find the
* number of messages in the file. This is called by
* readMessage and writeToFile functions.
*
*/
	int findMessageAmount(char* file);


#endif