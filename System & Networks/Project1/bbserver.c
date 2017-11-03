/****************************************************************/
/* Darrell Percey	&& Andrew Boven		                       	*/
/* bbserver.c                                                   */
/* Project 1 || System Networks II							   	*/
/*               											   	*/
/*	This program takes in connections from peers of the number  */
/*  that the user decides. Then it forms a ring connection      */
/*  between all the peers.  									*/
/*                                                             	*/
/****************************************************************/
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

int main(int argc, char *argv[]){
	
	if( argc < 2){
		perror("Please enter paramters [serverPortber] [numberHosts] \n");
		exit(1);
	}
	
	
	int listenSock = 0;
	int serverPort = 0;
	int test;
	int firstPort;
	char holdPort[100];
	int i = 0;
	char buf[100];
	char ip[100];
	char firstIP[100];
	char holdIP[100];
	struct sockaddr_in server, client;
	socklen_t addrlen = sizeof(client);
	
	
	
	
	serverPort = atoi(argv[1]);
	listenSock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(listenSock < 0){
		perror("Failed to create socket \n");
		exit(1);
	}
	
	
	gethostname(buf, 1000);
	printf("This Server's Hostname: %s \n",buf);
	struct hostent *hp  = gethostbyname(argv[1]);
	
	if( hp == NULL){
		printf("hostent:Cannot get name!");
		exit(1);
	}
	
	memset(ip,0,100);
	while(hp->h_addr_list[i] != NULL){
		strcat(ip,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
		i++;
	}
	
	
	memset(&server,'0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(serverPort);
	
	
	if( bind(listenSock, (struct sockaddr*)&server, sizeof(server)) < 0){
        perror("Bind failed.");
        return 1;
    }
	
	
	
	
	
	//passes around the connection information between each of the peers.
	i = 1;
	int n = atoi(argv[2]);
	while(i <= n){
		
		if(recvfrom(listenSock,buf,1000,0,(struct sockaddr*)&client, &addrlen) < 0){
			perror("recv:Failed \n");
		}
		
		if(i == 1){
			//stores the first connection information to pass information to later.
			inet_ntop(AF_INET, &client.sin_addr,firstIP,1000);
			firstPort = ntohs(client.sin_port);
		}
		
		if( i > 1 ){
			
			sendto(listenSock,holdIP,100,0,(struct sockaddr*)&client, addrlen);
			sendto(listenSock,holdPort,100,0,(struct sockaddr*)&client, addrlen);
		}
		
		//Prints incoming connections("DGRAM") to the screen.
		inet_ntop(AF_INET, &client.sin_addr,holdIP,1000);
		test = ntohs(client.sin_port);
		strcpy(holdPort, buf);
		printf("Client Connected IP: %s  Port: %d  Listen Port: %s\n",holdIP,test, buf);
		
		i++;
		
		
	
	}
	client.sin_addr.s_addr = inet_addr(firstIP);
	client.sin_port = htons(firstPort);
	//Passes the last IP/PORT to the first connection.
	sendto(listenSock, holdIP, 100, 0,(struct sockaddr*)&client, addrlen );
	sendto(listenSock,buf,100,0,(struct sockaddr*)&client, addrlen);

	
	return 1;
	
}

