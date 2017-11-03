/****************************************************************/
/* Darrell Percey	&&  Andew Boven		                       	*/
/* rdtReceiver.c                                                */
/* Project 2 || System Networks II							   	*/
/*               											   	*/
/*	This program allows us to implement a 3.0 RDT receiver. 	*/
/*  This will allow for realiable transfer across the network 	*/
/*  even if the packets are lost, delayed, or corrupted.   		*/
/*                                                             	*/
/****************************************************************/
#include "rdtReceiver.h"


int main(int argc, char *argv[]){
	//Checks for the one port arguement
	if(argc <= 1){
			printf("Please input arguements: port \n");
			return 1;
	} 
	//writes the message to the screen.
	char *message = malloc(SIZE*sizeof(char));
	message = receiveMessage (atoi(argv[1]));
	printf("Complete Message: [%s] \n",message);
	
	free(message);
	return 0;
}


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
char* receiveMessage (int port){
	int finish = 0;		//When a FIN is received
	int8_t seq = 0;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	char *completeString = malloc(SIZE*sizeof(char));
	//Socket Information
	struct packet recvPacket;
	struct sockaddr_in my_addr;
	socklen_t addrlen = sizeof(my_addr);
	
	createSocketInfo(port, &my_addr);
	printf("---The message will display below as packets are received--- \n");
	
	if(bind(sockfd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 0;
	}
	
	while(finish == 0){
		recvfrom(sockfd,&recvPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, &addrlen);
	
	
		if(recvPacket.seqNumber == 2){
			//Sequence number of 2 is a FIN request
			finish = 1;
			recvPacket.seqNumber = 2;
			sendto(sockfd,&recvPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, addrlen);
		}
		else{
			//If not corrupt and the right sequence number then add to the string and ACK it
			if(recvPacket.checkSum - generateChecksum(recvPacket.data) == 0  &&  seq == recvPacket.seqNumber){
				strcat(completeString,recvPacket.data);
				generateAck(&recvPacket);
				if(seq == 0)
					seq = 1;
				else
					seq = 0;
				
				sendto(sockfd,&recvPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, addrlen);
				printf("Message: %s \n",completeString);
			}
			else if(recvPacket.checkSum - generateChecksum(recvPacket.data) != 0){
				//Corrupted packet was received
				printf("Received corrupt packet \n");
			}
			else if(recvPacket.checkSum - generateChecksum(recvPacket.data) == 0 && seq != recvPacket.seqNumber){
				//ACK to the packet but don't edit the string because it's the wrong sequence number
				generateAck(&recvPacket);
				sendto(sockfd,&recvPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, addrlen);
				printf("Message: %s \n",completeString);
			}
		}
	}
	//Return the completed string to the main for printing
	return completeString;
}


/*
* Function:  generateACK
* 
* Description:
* Takes the source address and port and switches
* it with the destination address and port. This
* sends back an ACK that it received that packet.
*
*/
void generateAck(pack recvPacket){
	char temp[IPSIZE];
	int tempPort;
	
	strcpy(temp,recvPacket->srcIP);
	tempPort = recvPacket->srcPort;
	strcpy(recvPacket->srcIP,recvPacket->destIP);
	recvPacket->srcPort = recvPacket->destPort;
	strcpy(recvPacket->destIP,temp);
	recvPacket->destPort = tempPort;
}


/*
* Function:  generateChecksum
* 
* Description:
* Generates a checksum so the receiver and
* sender have a comparision for testing if 
* the packet is corrupt or not.
*
*/
int generateChecksum(char* seg){
	int i = 0;
	uint16_t sum = 0;
	
	for(i=0; i < strlen(seg); i++){
		sum = sum + seg[i];
	}
	
	return sum;
}


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
void createSocketInfo(int localPort,struct sockaddr_in *my_addr){
	char host[SIZE];
	struct hostent *hp;
	char myIP[IPSIZE];
	
	gethostname(host,SIZE);
	printf("Hostname: %s  Port: %d\n",host,localPort);
	hp = gethostbyname(host);
	
	memset(myIP,0,IPSIZE);
	
	int i = 0;
	while(hp->h_addr_list[i] != NULL){
		strcat(myIP,inet_ntoa( *(struct in_addr*)(hp->h_addr_list[i])));
		i++;
	}
	
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(localPort);
	my_addr->sin_addr.s_addr = htonl(INADDR_ANY);
}