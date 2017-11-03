#include "rdtReceiver.h"


int main(int argc, char *argv[]){
	
	if(argc <= 1){
			printf("Please input arguements: port \n");
			return 1;
	} 
	
	
	receiveMessage (atoi(argv[1]));
	
	
}

char* receiveMessage (int port){
	int finish = 0;
	int8_t seq = 0;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	char completeString[SIZE];
	struct packet recvPacket;
	struct sockaddr_in my_addr;
	socklen_t addrlen = sizeof(my_addr);
	
	createSocketInfo(port, &my_addr);
	
	if(bind(sockfd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 0;
	}
	
	while(finish == 0){
		recvfrom(sockfd,&recvPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, &addrlen);
	
		if(recvPacket.seqNumber == 2){
			finish = 1;
		}
		else{
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
				printf("Received corrupt packet \n");
			}
			else if(recvPacket.checkSum - generateChecksum(recvPacket.data) == 0 && seq != recvPacket.seqNumber){
				generateAck(&recvPacket);
				sendto(sockfd,&recvPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, addrlen);
				printf("Message: %s \n",completeString);
			}
		}
	}
	printf("Complete Message: [%s] \n",completeString);
	return 1;
}

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

int generateChecksum(char* seg){
	int i = 0;
	uint16_t sum = 0;
	
	for(i=0; i < strlen(seg); i++){
		sum = sum + seg[i];
	}
	
	return sum;
}

void createSocketInfo(int localPort,struct sockaddr_in *my_addr){
	char host[SIZE];
	struct hostent *hp;
	char myIP[IPSIZE];
	
	gethostname(host,SIZE);
	printf("Hostname: %s \n",host);
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