/****************************************************************/
/* Darrell Percey	&&  Andew Boven		                       	*/
/* rdtNetwork.c                                                 */
/* Project 2 || System Networks II							   	*/
/*               											   	*/
/*	Header file for RDT network. Simulates the network			*/
/* to cause artifical corruption, delay, and lost of packets.	*/
/* This allows us to create our own	environment for				*/
/*  testing our RDT 3.0 sender and receiver.     				*/
/*                                                             	*/
/****************************************************************/
 
#include "rdtNetwork.h"


int main(int argc, char *argv[]){
	//Checks if enough args are put in and tells the user what to type if not
	if(argc <= 4){
			printf("Please input arguements: port  lostPercent  delayPercent  errorPercent \n");
			return 1;
		} 
	//Starts up the "Network"
	controlNetwork(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	
	return 0;
}


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
int controlNetwork (int localPort, int lost, int delay, int corrupt){
	
	srand(time(NULL));		//Generating seed
	int percentageChecker;	//Used for putting against percentages for lost/delay/corrupt
	int finish = 0;			//Checks if the network can close down.
	int lostPack = 0, delayPack = 0, corruptPack = 0, sender = 0, receiver = 0, statDisplay = 0;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  //Socket
	char senderIP[IPSIZE];		
	//Socket information
	struct sockaddr_in my_addr, source_addr;
	struct packet forwardPacket;
	socklen_t addrlen = sizeof(my_addr);
	socklen_t sourcelen = sizeof(source_addr);
	
	
	//Creates the socket information from the users input
	createSocketInfo(localPort, &my_addr, &source_addr);
	printf("Percentages- Lost:%d%% Delay:%d%%  Corrupt:%d%% \n",lost, delay, corrupt);
	
	if(bind(sockfd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 0;
	}
	
	//Main loop for processing the network
	while(finish < 2){
		
		recvfrom(sockfd,&forwardPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, &addrlen);
		//If first receive then the sender's IP is saved for statistics
		if(sender == 0){
			strcpy(senderIP,forwardPacket.srcIP);
			sender++;
		}
		
		//If sender ip sender++ otherwise it's the receiver for statistics
		if(strcmp(senderIP,forwardPacket.srcIP) == 0){
			sender++;
		}
		else{
			receiver++;
		}
		
		//If the seqNumber is 2 (always a 1 or 0) then we know it's a FIN request to stop
		if(forwardPacket.seqNumber == 2){
			finish++;
			forwardPacket.seqNumber = 2;
			//Sends out final FINs to both to ENSURE the sender and receiver both close (this is started from sender however).
			sendto(sockfd,&forwardPacket,sizeof(struct packet), 0, (struct sockaddr*)&source_addr,sourcelen);
			
			if(inet_pton(AF_INET, forwardPacket.destIP, &source_addr.sin_addr) < 0){
				printf("inet_pton error occured: destIP \n");
				return 0;
			}
			source_addr.sin_port = htons(forwardPacket.destPort);
			sendto(sockfd,&forwardPacket,sizeof(struct packet), 0, (struct sockaddr*)&source_addr,sourcelen);
		}
		else{
			//Must switch the new address to send to so the dest is reached.
			if(inet_pton(AF_INET, forwardPacket.destIP, &source_addr.sin_addr) < 0){
				printf("inet_pton error occured: destIP \n");
				return 0;
			}
			source_addr.sin_port = htons(forwardPacket.destPort);
		
			//Checks for lost/delayed/corrupted packet by testing the percentage against a random number 1-100
			//If 60% then random generation chance of being 60-100 is 40% Checking if the percentageChecker is lower
			//then the percentage value picked.
			percentageChecker = (rand() % 100) + 1;
			if(percentageChecker <= lost){
				lostPack++;
				//Do nothing packet is lost
				printf("Packet lost: dest-[%s/%d] segment-[%s]  \n",forwardPacket.destIP, forwardPacket.destPort, forwardPacket.data);
			}
			else{
				percentageChecker = (rand() % 100) + 1;
				if(percentageChecker <= corrupt){
					corruptPack++;
					printf("Corrupt packet: dest-[%s/%d] segment-[%s]  \n",forwardPacket.destIP, forwardPacket.destPort, forwardPacket.data);
					forwardPacket.checkSum = forwardPacket.checkSum + 10;
				}
				
				percentageChecker = (rand() % 100) + 1;
				if(percentageChecker <= delay){
					delayPack++;
					printf("Delaying packet: dest-[%s/%d] segment-[%s]  \n",forwardPacket.destIP, forwardPacket.destPort, forwardPacket.data);
					sleep(7);
				}
				sendto(sockfd, &forwardPacket, sizeof(struct packet), 0, (struct sockaddr*)&source_addr, sourcelen);
			}
			
			sleep(1);
			
			//Displays the stats every two packets received (keeps the clutter down a little).
			if(statDisplay >= 2){
				printf("Sender: %d  Receiver: %d  Lost: %d  Delay: %d  Corrupt: %d \n",sender, receiver, lostPack, delayPack, corruptPack);
				statDisplay = 0;
			}
			statDisplay++;
		}
	}
	printf("------------------FINAL STATS------------------\n");
	printf("Sender: %d  Receiver: %d  Lost: %d  Delay: %d  Corrupt: %d \n",sender, receiver, lostPack, delayPack, corruptPack);
	printf("-----------------------------------------------");
	return 0;
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
void createSocketInfo(int localPort,struct sockaddr_in *my_addr, struct sockaddr_in *source_addr){
	char host[SIZE];
	struct hostent *hp;
	char myIP[IPSIZE+10];
	
	//Gets the hostname
	gethostname(host,SIZE);
	printf("Hostname: %s  Port: %d \n",host,localPort);
	hp = gethostbyname(host);
	
	memset(myIP,0,IPSIZE);
	
	int i = 0;
	while(hp->h_addr_list[i] != NULL){
		strcat(myIP,inet_ntoa( *(struct in_addr*)(hp->h_addr_list[i])));
		i++;
	}
	
	//Sets up information for the socket to bind.
	my_addr->sin_family = AF_INET;
	source_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(localPort);
	
	if(inet_pton(AF_INET, myIP, &my_addr->sin_addr) <  0){
        printf("inet_pton error occured: myIP\n");
        exit(1);
    } 
}