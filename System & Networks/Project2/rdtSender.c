#include "rdtSender.h"


int main(int argc, char *argv[]){
	
	char message[SIZE];
	
	if(argc <= 5)
    {
        printf("Please input arguements: port  rcvHost  rcvPort  networkHost  networkPort \n");
        return 1;
    } 
	
	int myPort = atoi(argv[1]);
	int destPort = atoi(argv[3]);
	int netPort = atoi(argv[5]);
	
	
	getUserInput(message);
	printf("Sending [%s] to rcv",message);
	
	
	sendMessage(myPort, argv[4], netPort, argv[2], destPort, message);
	
	
	
}


int sendMessage (int localPort, char* netwhost, int netwPort, char* desthost, int destPort, char* message){
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int stringCount = 0;
	int x;
	int8_t seq = 0; 
	char dest[IPSIZE];
	struct sockaddr_in my_addr, network;
	struct packet currentPacket, previousPacket;
	struct timeval time;
	fd_set readfds;
	socklen_t addrlen = sizeof(network);
	
	
	findDestIP(dest,desthost);
	createSocketInfo(localPort, netwhost, netwPort, &my_addr, &network);
	
	if(bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 0;
	}
	
	FD_ZERO(&readfds);
	FD_SET(sockfd,&readfds);
	time.tv_sec = 5;
	
	
	makePacket(&currentPacket, &previousPacket, localPort, dest, destPort, my_addr, message, &stringCount, seq);
	sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
	
	while(stringCount < strlen(message)){
		
		x = select(sockfd+1,&readfds,NULL,NULL,&time);
		if( x == -1){
			//Opps not good
			printf("error with select() \n");
			return 0;
		}
		else if(x == 0){
			
			printf("Timeout occured: resending packet \n");
			sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
			
		}
		else{
			recvfrom(sockfd,&previousPacket,sizeof(struct packet),0,(struct sockaddr*)&network,&addrlen);
			
			if(seq == previousPacket.seqNumber && currentPacket.checkSum == previousPacket.checkSum){
				if(seq == 1)
					seq = 0;
				else
					seq = 1;
				
				makePacket(&currentPacket, &previousPacket, localPort, dest, destPort, my_addr, message, &stringCount, seq);
				sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
			}
		}
		
		time.tv_sec = 5;
		
	}
	
	//make fin pack!
	currentPacket.seqNumber = 2;
	sendto(sockfd,&currentPacket,sizeof(struct packet),0,(struct sockaddr*)&network,addrlen);
	return 1;
}


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

int generateChecksum(char* seg){
	int i = 0;
	uint16_t sum = 0;
	
	for(i=0; i < strlen(seg); i++){
		sum = sum + seg[i];
	}
	
	return sum;
}


void getUserInput(char *message){
	
	printf("Enter a message(1000char limit): ");
	fgets(message,SIZE,stdin);
	message[strlen(message)-1] = '\0';
	
	
}


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