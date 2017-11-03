#include "rdtNetwork.h"

int main(int argc, char *argv[]){
	int myPort;

	if(argc <= 4)
		{
			printf("Please input arguements: port  lostPercent  delayPercent  errorPercent \n");
			return 1;
		} 
	myPort = atoi(argv[1]);
	
	controlNetwork(myPort);
}

int controlNetwork (int localPort){
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in my_addr, source_addr;
	struct packet forwardPacket;
	socklen_t addrlen = sizeof(my_addr);
	socklen_t sourcelen = sizeof(source_addr);
	
	
	createSocketInfo(localPort, &my_addr, &source_addr);
	
	if(bind(sockfd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 0;
	}
	
	while(1){
	recvfrom(sockfd,&forwardPacket,sizeof(struct packet),0,(struct sockaddr*)&my_addr, &addrlen);
	
	printf("Dest IP/PORT: %s  /  %d \n",forwardPacket.destIP,forwardPacket.destPort);
	printf("Src IP/PORT: %s  /  %d \n",forwardPacket.srcIP,forwardPacket.srcPort);
	printf("Segment: %s  \n",forwardPacket.data);
	
	if(inet_pton(AF_INET, forwardPacket.destIP, &source_addr.sin_addr) < 0){
		printf("inet_pton error occured: destIP \n");
		return 0;
	}
	source_addr.sin_port = htons(forwardPacket.destPort);
	
	sendto(sockfd, &forwardPacket, sizeof(struct packet), 0, (struct sockaddr*)&source_addr, sourcelen);
	
	
	}
}

void createSocketInfo(int localPort,struct sockaddr_in *my_addr, struct sockaddr_in *source_addr){
	char host[SIZE];
	struct hostent *hp;
	char myIP[IPSIZE+10];
	
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
	source_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(localPort);
	
	if(inet_pton(AF_INET, myIP, &my_addr->sin_addr) <  0){
        printf("inet_pton error occured: myIP\n");
        exit(1);
    } 
}