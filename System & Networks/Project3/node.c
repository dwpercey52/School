/* Darrell Percey && Andrew Boven
 * File: node.c
 * Project 3 || System Network II
 * 
 * This program simulates routers in a network forwarding packets that
 * contain neighbor information to the other routers on the network.
 * this allows the "routers" to build a forwarding table which they can
 * find the fastest pathway to to get to other nodes.
 *
 *
 */

#include "node.h"



int main(int argc, char *argv[]){
	
	int x = 0;
	char label;
	forP topTable = createNewNode();
	
	//checks for arguements
	if(argc <= 4){
		printf("Please input arguements: Label  port  numberRouter  discoveryFile \n");
		return 1;
	}
	
	//Makes a char our of string
	label = argv[1][0];
	x = startRouting(label,atoi(argv[2]),atoi(argv[3]),argv[4], topTable);
	
	//If an error occured 
	if(x == 1){
		printf("Error with routing \n");
		return 1;
	}
	
	//prints the forwarding table
	printForwardingTable(topTable);
	
	//Frees the memory allocated to the linked list
	forP temp = topTable;
	while(temp->next !=NULL){
		temp = temp->next;
		free(topTable);
		topTable = temp;
	}
	free(topTable);
	
	return 0;
}



/*
* Function:  checkReadyStatus
* 
* Description:
* Waits for the user to enter y to start the routing function
* this gives the user time to boot up all "routers" so they can
* begin passing messages together.
*
*/
void checkReadyStatus(){
	int x = 0;
	char a;
	
	while(x == 0){
		printf("Are all routers online and ready?(y/n) \n");
		scanf(" %c",&a);
		
		if(a == 'y'){
			x = 1;
		}
	}
}
	

	
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
int startRouting(char label, int port, int numRouter, char* file, forP topTable){
	
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int neighborPort[SIZE];
	int i, x;
	int neighborAmt = 0;
	int orgCntr = 0;
	char neighborLabel[SIZE];
	char neighborIP[SIZE][IPSIZE];
	char orgSenderList[SIZE];
	struct sockaddr_in my_addr, dest;
	struct packet send, recv, forward;
	struct timeval time;
	socklen_t addrlen = sizeof(dest);
	fd_set readfds;
	
	//Sets up the information for the socket
	setUpSocket(port, &my_addr, &dest);
	
	//Makes sure the list is clear as it is the stopping counter
	for(i = 0; i < SIZE; i++){
		orgSenderList[i] = '\0';
	}
	
	//Makes sure that the neighbors are listed for easy access
	if(findNeighbors(neighborIP, neighborPort, neighborLabel, file, topTable) == 1){
		printf("Error with finding neighbors \n");
		return 1;
	}
	
	//Displays the neighbors to the screen for the user to verify
	i = 0;
	while(neighborPort[i] > 0){
		if(neighborPort[i] > 0){
			printf("Neighbor %d: %s  -  %d \n",i+1,neighborIP[i],neighborPort[i]);
			i++;
		}
	}
	
	printf("Ready to start.... \n");
	
	if(bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		printf("Failed to bind socket \n");
		return 1;
	}
	
	//Checks if the user has prepared all routers.
	checkReadyStatus();
	sleep(6);
	
	//Makes the packet which will be stored and sent out on the network
	if(makePacket(&send, topTable, numRouter, label) == 1){
		printf("Error in making flood packet \n");
		return 1;
	}
	i = 0;
	
	//Makes sure the labels are clear 
	while(neighborLabel[i] != '\0'){
		i++;
	}
	neighborAmt = i;

	//Sends out first packet and sets up select()
	sendNeighbors(send, neighborIP, neighborPort, sockfd, &dest, addrlen);
	FD_ZERO(&readfds);
	FD_SET(sockfd,&readfds);
	time.tv_sec = 4;
	
	
	while( orgCntr < numRouter-1){
		i = 0;
		
		
		x = select(sockfd+1,&readfds,NULL,NULL,&time);
		if(x == -1){
			printf("Error with select() \n");
			return 1;
		}
		else if(x == 0){
			//Resends if timeout occurs 
			printf("Timeout");
			sendNeighbors(send, neighborIP, neighborPort, sockfd, &dest, addrlen);
		}
		else{
			//Receives a packet, if the hops is 0 it will drop the packet
			recvfrom(sockfd,&recv,sizeof(struct packet),0,NULL,NULL);
			orgCntr = orginalSenderCheck(recv, orgSenderList);
			i = generateForwardPacket(recv, &forward, label, neighborLabel, neighborAmt, topTable);
			if( i == 2 ){
				//do nothing packet out of hops
			}
			else{
				//Sends the neighbors the forwarded packet
				sendNeighbors(forward, neighborIP, neighborPort, sockfd, &dest, addrlen);
			}
		}
		FD_ZERO(&readfds);
		FD_SET(sockfd,&readfds);
		time.tv_sec = 4;
		
	}
	
	close(sockfd);
	return 0;
}



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
int orginalSenderCheck(struct packet recv, char *orgSenderList){
	int i = 0;
	int isAdded = 0;
	int counter = 0;
	
	while(orgSenderList[i] != '\0'){
	
		if(orgSenderList[i] == recv.orgSender){
			isAdded++;
		}
		i++;
	}
	
	if(isAdded == 0 && i < SIZE){
		orgSenderList[i] = recv.orgSender;
	}
	
	i = 0;
	while(orgSenderList[i] != '\0'){
		counter++;
		i++;
	}
	return counter;
}



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
void printForwardingTable(forP top){
	forP temp = top;
	printf("| Destination    Distance    Path |\n");
	while(temp->next != NULL){
		printf("| %11c    %8d    %4c |\n",temp->dest,temp->distance,temp->path);
		temp = temp->next;
	}
	printf("| %11c    %8d    %4c |\n",temp->dest,temp->distance,temp->path);
}



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
int generateForwardPacket(struct packet recv, struct packet *forward, char label, char *neighborLabel, int neighborAmt, forP top){
	int isNeighbor;
	int i = 0;
	int x = 0;
	forP temp;
	
	//-- the hops if they are 0 or less then return 2 to drop
	forward->hops = recv.hops-1;
	if(forward->hops <= 0){
		return 2;
	}
	
	i = 0;
	while(recv.label[i] != '\0' || recv.distance[i] != 999 ){
		isNeighbor = 0;
		for(x = 0; x < neighborAmt; x++){
			if(recv.label[i] == neighborLabel[x]){
				isNeighbor = 1;
			}
		}
		//If it's a neighbor and it recv 0 then change to neighbor distance
		//If it's not found yet, push to table and test.
		if(isNeighbor == 1 && recv.distance[i] == 0){
				temp = findTableEntry(top, recv.label[i]);
				forward->label[i] = recv.label[i];
				if(temp == NULL){
					printf("Error finding entry \n");
					return 1;
				}
				else{
					forward->distance[i] = temp->distance;
				}
		}
		else if(recv.label[i] == label){
			forward->label[i] = label;
			forward->distance[i] = 0;
		}
		else{
			temp = findTableEntry(top,recv.currSender);
			forward->distance[i] = (recv.distance[i] + temp->distance);
			forward->label[i] = recv.label[i];
		}
		i++;
	}
	
	//Clear all the extra labels and distances
	for(x = i; x < SIZE; x++){
		forward->distance[x] = 999;
		forward->label[x] = '\0';
	}
	
	forward->currSender = label;
	forward->orgSender = recv.orgSender;
	
	//Fill in the table as receiving packets
	for(x = 0; x < i; x++){
		if(forward->label[x] == label){
			fillForwardTable(forward->label[x], forward->distance[x], forward->label[x], top);
		}
		else{
			fillForwardTable(forward->label[x], forward->distance[x], recv.currSender, top);
		}
	}
	
	return 0;
}



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
void fillForwardTable(char label, int dist, char path, forP top){
	forP temp = top;
	
	if(findTableEntry(top, label) == NULL){
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = addNewNode(label, dist, path);
	}
	else{
		temp = findTableEntry(top, label);
		if(temp->distance > dist){
			temp->distance = dist;
			temp->dest = label;
			temp->path = path;
		}
	}
}



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
int sendNeighbors(struct packet send, char neighborIP[SIZE][IPSIZE], int *neighborPort, int sock, struct sockaddr_in *dest, socklen_t addrlen){
	int i = 0;
	
	//Changes the IP and port then sends 
	while(neighborPort[i] > 0){
		dest->sin_port = htons(neighborPort[i]);
		
		if(inet_pton(AF_INET, neighborIP[i], &dest->sin_addr) <  0){
			printf("inet_pton error occured: myIP\n");
			return 1;
		} 
		
		sendto(sock,&send,sizeof(struct packet),0,(struct sockaddr *)dest,addrlen);
		if(neighborPort[i] > 0){
			i++;
		}
	}
	
	return 0;
}



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
int makePacket(struct packet *send, forP top, int numRouter, char myLabel){
	forP temp = top;
	int i = 0;
	int x = 0;
	
	send->currSender = myLabel;
	send->hops = numRouter+2;
	send->orgSender = myLabel;
	
	while(i == 0){
		send->label[x] = temp->dest;
		send->distance[x] = temp->distance;
		if(temp->next != NULL){
			temp = temp->next;
			x++;
		}
		else{
			i++;
			x++;
		}
	}
	//Fill in the extra space
	for(i = x; i < SIZE; i++){
		send->label[i] = '\0';
		send->distance[i] = 999;
	}
	
	return 0;
}



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
int findNeighbors(char neighborIP[SIZE][IPSIZE],int *neighborPort, char* neighborLabel, char* file, forP top){
	FILE *fp;
	int x = 0;
	int i,y;
	int placeHolder = 0;
	char line[LSIZE];
	char tempLabel[SIZE];
	char tempHost[LSIZE];
	char temp[LSIZE];
	int tempDistance[SIZE];
	struct hostent *hp;
	forP tempNode = top;
	
	fp = fopen(file,"r");
	
	if(!fp){
		printf("File couldn't open! \n");
		return 1;
	}
	
	//Pulls in a line from text file
	while( fgets(line,LSIZE,fp) != NULL){
		hp = NULL;
		line[strlen(line)] = '\0';
		strcpy(temp,strtok(line,","));
		tempLabel[placeHolder] = temp[0];
		
		//Breaks apart each strtok piece
		for(i = 0; i < 3; i++){
			strcpy(temp,strtok(NULL,","));
			
			if(i == 0){
				memset(tempHost,0,sizeof(tempHost));
				strcpy(tempHost,temp);
				hp = gethostbyname(tempHost);
				memset(neighborIP[placeHolder],0,sizeof(neighborIP[i]));
				
				y = 0;
				while(hp->h_addr_list[y] != NULL){
					strcat(neighborIP[placeHolder],inet_ntoa( *(struct in_addr*)(hp->h_addr_list[y])));
					y++;
				}
			}
			else if(i == 1){
				neighborPort[placeHolder] = atoi(temp);
			}
		
		}
		tempDistance[placeHolder] = atoi(temp);
		placeHolder++;
	}
	
	//Fills in the extra spaces
	for(i = placeHolder; i < SIZE; i++){
			tempDistance[i] = 0;
			tempLabel[i] = '\0';
			memset(neighborIP[i],0,sizeof(neighborIP[i]));
			neighborPort[i] = 0;
	}
	
	//Puts the neighbors in the forwarding table
	while(tempLabel[x] != '\0'){
		if(x == 0){
			top->distance = tempDistance[x];
			top->dest = tempLabel[x];
			top->path = tempLabel[x];
			neighborLabel[x] = tempLabel[x];
		}
		else{
			tempNode = top;
			while(tempNode->next != NULL){
				tempNode = tempNode->next;
			}
			tempNode->next = addNewNode(tempLabel[x],tempDistance[x],tempLabel[x]);
			neighborLabel[x] = tempLabel[x];
		}
		x++;
	}
	
	//Fills in the extra space
	for(i = x; i < SIZE; i++){
		neighborLabel[i] = '\0';
	}
	
	return 0;
}



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
void setUpSocket(int port, struct sockaddr_in *my_addr, struct sockaddr_in *dest){
	struct hostent *hp;
	char host[LSIZE];
	char myIP[IPSIZE];
	
	gethostname(host,LSIZE);
	
	//Prints the hostname for the user to see
	printf("Hostname: %s \n",host);
	hp = gethostbyname(host);
	
	memset(myIP,0,IPSIZE);
	int i = 0;
	if(hp != NULL){
		while(hp->h_addr_list[i] != NULL){
			strcat(myIP,inet_ntoa( *(struct in_addr*)(hp->h_addr_list[i])));
			i++;
		}
	}
	
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(port);
	dest->sin_family = AF_INET;
	
	if(inet_pton(AF_INET, myIP, &my_addr->sin_addr) <  0){
        printf("inet_pton error occured: myIP\n");
        exit(1);
    } 
}



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
forP findTableEntry(forP top, char label){
	forP temp = top;
	while(temp->next != NULL){
		if(temp->dest == label){
			return temp;
		}
		temp = temp->next;
	}
	
	if(temp->dest == label){
		return temp;
	}
	
	
	return NULL;
}



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
forP createNewNode(){
	forP temp = (forP) malloc(sizeof(forwardTable));
	temp->dest = '\0';
	temp->distance = 0;
	temp->path = '\0';
	temp->next = NULL;
	
	return temp;
}



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
forP addNewNode(char destLabel, int dist, char pathLabel){
	forP temp = (forP) malloc(sizeof(forwardTable));
	temp->dest = destLabel;
	temp->distance = dist;
	temp->path = pathLabel;
	temp->next = NULL;
	
	return temp;
}