/****************************************************************/
/* Darrell Percey	&&  Andew Boven		                       	*/
/* rdtSender.c                                                  */
/* Project 2 || System Networks II							   	*/
/*               											   	*/
/*	This program allows us to implement a 3.0 RDT Sender.    	*/
/*  This will allow for realiable transfer across the network 	*/
/*  even if the packets are lost, delayed, or corrupted.   		*/
/*                                                             	*/
/****************************************************************/
#include "rdtSender.h"


int main(int argc, char *argv[]){
	
	char message[SIZE];
	int x = 0;
	//Checks for arguements
	if(argc <= 5)
    {
        printf("Please input arguements: port  rcvHost  rcvPort  networkHost  networkPort \n");
        return 1;
    } 
	
	int myPort = atoi(argv[1]);
	int destPort = atoi(argv[3]);
	int netPort = atoi(argv[5]);
	
	//Gets the user input
	getUserInput(message);
	printf("Sending [%s] to rcv",message);
	
	//Starts sending the message
	x = sendMessage(myPort, argv[4], netPort, argv[2], destPort, message);
	
	if(x == 1)
		printf("Message was sent, and FIN received \n");
	else
		printf("Error sending message! \n");
	
	return 0;
}

/*
* Function:  sendMessage
* 
* Description:
* Main loop in the program that sends the message
* until it has FIN'd. It will takes a message from the
* user and break it into segments which it will send one 
* at a time till each piece is ACK'd.
* Further information commented below.
*
*/
int sendMessage (int localPort, char* netwhost, int netwPort, char* desthost, int destPort, char* message){
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int stringCount = 0;	//Keeps a place holder on the string so we can divide each piece
	int x = 0;
	int finalACK = 0;		//Knows when we send the final ACK and quits sending
	int8_t seq = 0; 
	char dest[IPSIZE];
	//Socket information
	struct sockaddr_in my_addr, network;
	struct packet currentPacket, previousPacket;
	struct timeval time;
	fd_set readfds;
	socklen_t addrlen = sizeof(network);
	socklen_t unstucklen = sizeof(my_addr);
	
	
	//Get all address information
	findDestIP(dest,desthost);
	createSocketInfo(localPort, netwhost, netwPort, &my_addr, &network);
	
	if(bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 0;
	}
	
	/********************************
	* Send sender itself a fake packet
	* This helps with the sticking issue in the
	* SSH server 
	*********************************/
	currentPacket.seqNumber = 5;
	previousPacket.seqNumber = 4;
	previousPacket.checkSum = 100;
	currentPacket.checkSum = 102;
	sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr,unstucklen);
	/*            END           */
	
	makePacket(&currentPacket, &previousPacket, localPort, dest, destPort, my_addr, message, &stringCount, seq);
	sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
	
	while(finalACK == 0){
		
		
		FD_ZERO(&readfds);
		FD_SET(sockfd,&readfds);
		time.tv_sec = 2;
		//Waits for information on the socket or times out
		x = select(sockfd+1,&readfds,NULL,NULL,&time);
		if( x == -1){
			//Opps not good
			printf("error with select() \n");
			return 0;
		}
		else if(x == 0){
			//Timeout so resend last packet
			printf("Timeout occured: resending packet \n");
			sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
			
		}
		else{
			//ACK was received
		//	recvfrom(sockfd,&previousPacket,sizeof(struct packet),0,(struct sockaddr*)&network, &addrlen);
			recvfrom(sockfd,&previousPacket,sizeof(struct packet),0,NULL,NULL);
			if(seq == previousPacket.seqNumber && currentPacket.checkSum == previousPacket.checkSum){
				//This is if a valid ACK is received testing Sequence number and checksums
				printf("ACK received \n");
				if(stringCount >= strlen(message)){
					finalACK = 1;
				}
				//Switches the seq for the next packet
				if(seq == 1)
					seq = 0;
				else
					seq = 1;
				//Makes the next piece
				makePacket(&currentPacket, &previousPacket, localPort, dest, destPort, my_addr, message, &stringCount, seq);
				sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
			}
		}
	}
	
	//This is used to send out extra "FIN" request to ensure the network and receiver get them
	int y = 0;
	while(y < 2){
		currentPacket.seqNumber = 2;
		sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
		x = select((sockfd+1),&readfds,NULL,NULL,&time);
		
		if(x > 0){
			recvfrom(sockfd,&previousPacket,sizeof(struct packet),0,(struct sockaddr*)&network,&addrlen);
		}
		
		time.tv_sec = 1;
		FD_ZERO(&readfds);
		FD_SET(sockfd,&readfds);
		y++;
		
	}
	
	return 1;
}

/*
* Function:  findDestIP
* 
* Description:
* Finds the 16byte IP address from the hostname
* that the user provided. Used for sending the in
* packet.
*
*/
void findDestIP(char* dest, char *desthost){
	struct hostent *hp;
	hp = gethostbyname(desthost);
	memset(dest,0,sizeof(IPSIZE));
	
	int i = 0;
	while(hp->h_addr_list[i] != NULL){
		strcat(dest,inet_ntoa( *(struct in_addr*)(hp->h_addr_list[i])));
		i++;
	}
}


/*
* Function:  makePacket
* 
* Description:
* Creates a new packet with the next piece of message
* to send to the receiver. This will also generate a new
* checksum and set the proper sequence number.
*
*/
int makePacket(pack curr, pack prev, int localPort, char* desthost, int destPort, struct sockaddr_in addr, char* seg, int* strCntr, int8_t seq){
	int i, y;
	int x = 0;
	char segment[7];
	
	//*prev = *curr;
	strcpy(curr->destIP,desthost);
	curr->destPort = destPort;
	inet_ntop(AF_INET, &addr.sin_addr,curr->srcIP,IPSIZE);
	curr->srcPort = localPort;
	curr->seqNumber = seq;
	
	i = *strCntr;
	
	y = i + 6;
	for(i = *strCntr; i < y; i++){
		if( i < strlen(seg)){
			segment[x] = seg[i];
			x++;
		}
		else{
			segment[x] = '\0';
			x++;
		}
	}
	segment[6] = '\0';
	*strCntr = i;
	curr->checkSum = (uint16_t)generateChecksum(segment);
	strcpy(curr->data,segment);
	
	return 0;
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
* Function:  getUserInput
* 
* Description:
* Gets the message from the user that they
* would like to send to the receiver.
*
*/
void getUserInput(char *message){
	
	printf("Enter a message(1000char limit): ");
	fgets(message,SIZE,stdin);
	message[strlen(message)-1] = '\0';
	
	
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
void createSocketInfo(int localPort,char *netwhost,int netwPort,struct sockaddr_in *my_addr, struct sockaddr_in *network){
	
	char host[SIZE];
	struct hostent *hp;
	char myIP[IPSIZE];
	char netIP[IPSIZE];
	
	gethostname(host,SIZE);
	printf("Hostname: %s \n",host);
	hp = gethostbyname(host);
	
	memset(myIP,0,IPSIZE);
	memset(netIP,0,IPSIZE);
	
	int i = 0;
	if(hp != NULL){
		while(hp->h_addr_list[i] != NULL){
			strcat(myIP,inet_ntoa( *(struct in_addr*)(hp->h_addr_list[i])));
			i++;
		}
	}
	
	
	i = 0;
	if(hp != NULL){
	hp = gethostbyname(netwhost);
		while(hp->h_addr_list[i] != NULL){
			strcat(netIP,inet_ntoa( *(struct in_addr*)(hp->h_addr_list[i])));
			i++;
		}
	}
	
	
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(localPort);
	network->sin_family = AF_INET;
	network->sin_port = htons(netwPort);
	
	if(inet_pton(AF_INET, myIP, &my_addr->sin_addr) <  0){
        printf("inet_pton error occured: myIP\n");
        exit(1);
    } 
	
	if(inet_pton(AF_INET, netIP, &network->sin_addr) <  0){
        printf("inet_pton error occured: netIP\n");
        exit(1);
    } 
	
	
}