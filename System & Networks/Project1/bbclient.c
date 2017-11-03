/****************************************************************/
/* Darrell Percey	&&  Andew Boven		                       	*/
/* bbclient.c                                                   */
/* Project 1 || System Networks II							   	*/
/*               											   	*/
/*	This is the client program. It will either connect to a		*/
/*  server or a peer to establish a ring connection so that     */
/*  it can operate on a shared file making a bullentin board    */
/*                                                             	*/
/****************************************************************/

#include "bbclient.h"
#include "bbfile.h"

int main(int argc, char *argv[])
{
    
	int userInt = 0;
	char message[SIZE];
	char userInput[SIZE];
	char fileName[SIZE];
	int len = sizeof(serv_addr);
	int i = 0;
	pthread_t recvThr;
	

    if(argc <= 4)
    {
        printf("Please input arguements [-new] portNum hostIp(hostname) hostPort fileName \n");
        return 1;
    } 
	
	
	//If statement checks if -new or not new for server or peer-to-peer direct connection
	if(argc == 6){
		if(strcmp("-new",argv[1]) == 0){
			printf("Connecting to server... \n");
			connectToServer(argv);
			if(makeListenSocket(argv[2]) != 1){
				perror("listen socket: Failed \n");
			}
			int tokCode = generateToken();
			sleep(2);
			findFirstToken(tokCode);
			strcpy(fileName,argv[5]);
		}
	}
	else{
		printf("Connecting to ring... \n");
		makeListenSocket(argv[1]);
		strcpy(fileName, argv[4]);
		joinRing(argv[2],argv[3]);
		token = 0;
	}
	
	i = pthread_create(&recvThr,NULL,recvFunc,NULL);
	
	
	
	int actionDone = 0;
	strcpy(message,"token");
	
	// Does the main action of executing the actions the user wants
	//Also sends the token after the user has finished with their action.
	while(actionDone != 4){
		
		//Prints a menu for the user.
		printUserMenu();
		
		//Ask the user for input until they enter a valid number 1-4
		actionDone = 0;
		while(actionDone == 0){
			scanf("%s",userInput);
			actionDone = checkUserInput(userInput);
		}
		
		
		if(actionDone == 1){
			printf("Enter your post(100char): ");
			i = strlen(userInput);
			while((i = getchar() != '\n' && i != EOF));
			fgets(userInput,SIZE,stdin);
		}
		else if(actionDone == 2){
			printf("Enter message #: ");
			scanf("%d",&userInt);
		}
		
		
		//Waits for token to do actions.
		//A.K.A checks for token before action/sending token.
		while(token == 0){
			sleep(2);
		}
	
		executeUserAction(actionDone, fileName, userInput, userInt);
		
		sendto(listenSock, message, SIZE, 0,(struct sockaddr *)&serv_addr, len);
		
		pthread_mutex_trylock(&mutex);
		token = 0;
		pthread_mutex_unlock(&mutex);
		
	
		
	}
  
	printf("Leaving ring...");
	pthread_join(recvThr,NULL);
			

    return 0;
}

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
void joinRing(char* ip, char* port){
	struct hostent *hp =gethostbyname(ip);
	char connectIP[SIZE];
	int portNum = 0;
	int i = 0;
	
	
	if(hp == NULL){
		printf("hostent:Cannot gethostbyname \n");
		exit(1);
	}
	
	memset(connectIP,0,SIZE);
	while(hp->h_addr_list[i] != NULL){
		strcat(connectIP,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
		i++;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port)); 
	
	if(inet_pton(AF_INET, connectIP, &serv_addr.sin_addr) <  0){
        printf("inet_pton error occured\n");
        exit(1);
    } 
	
	if( sendto(listenSock, "join", SIZE, 0,(struct sockaddr *)&serv_addr, len) < 0 ){
		perror("send failed \n");
		exit(1);
	}
	
	if(recvfrom(listenSock, connectIP, SIZE, 0,(struct sockaddr*)&my_addr, &socklen) < 0 ){
			perror("recv failed \n");
			exit(1);
	}
	if(recvfrom(listenSock, &portNum, sizeof(portNum), 0,(struct sockaddr*)&my_addr, &socklen) < 0 ){
			perror("recv failed \n");
			exit(1);
	}
	
	printf("Recv - IP:[%s] Port:[%d] \n",connectIP, portNum);
	
	if(inet_pton(AF_INET, connectIP, &serv_addr.sin_addr) <  0){
        printf("inet_pton error occured\n");
        exit(1);
    } 
	
	serv_addr.sin_port =htons(portNum);
}


/*
* Function:  executeUserAction()
* 
* Description:
* depending on the code that is passed in from act
* this function will execute the need I/O on the file
* assuming the user has the token to do so.
*
*/
void executeUserAction(int act, char* file, char* inputS, int inputD){
	switch(act){
		case 1:
			writeToFile(file, inputS);
			break;
		case 2:
			readMessage(file,inputD);
			break;
		case 3:
			listMessages(file);
			break;
		case 4:
			exitFunction();
			break;
		default:
			break;
	}
}


/*
* Function:  checkUserInput()
* 
* Description:
* This verifies that the user put a number from the menu
* either 1-4 for one of the acts that the user can request.
*
*/
int checkUserInput(char* input){
	int action = 0;
	
	if(strcmp(input,"1") == 0){
		action = 1;
	}
	else if(strcmp(input,"2") == 0){
		action = 2;
	}
	else if(strcmp(input,"3") == 0){
		action = 3;
	}
	else if(strcmp(input,"4") == 0){
		action = 4;
		quitToken = 1;
	}
	else{
		printf("Invalid entry. \n");
	}
	
	return action;
}


/*
* Function:  exitFunction()
* 
* Description:
* This notifies the peer that is sending to this peer
* that it is exiting the ring so it passed the information of
* it's sender to the recevier.
*
*/
void exitFunction(){
	char connectIP[SIZE];
	char message[SIZE];
	int portNum = 0;
	
	strcpy(message,"exit");
	inet_ntop(AF_INET, &serv_addr.sin_addr,connectIP,SIZE);
	portNum = ntohs(serv_addr.sin_port);
	
	if(sendto(listenSock, message, SIZE, 0,(struct sockaddr *)&my_addr, len) < 0){
		printf("failed to send \n");
		exit(1);
	}
	if(sendto(listenSock, connectIP, SIZE, 0,(struct sockaddr *)&my_addr, len) < 0){
		printf("failed to send \n");
		exit(1);
	}
	if(sendto(listenSock,&portNum, sizeof(portNum), 0,(struct sockaddr *)&my_addr, len) < 0){
		printf("failed to send \n");
		exit(1);
	}
}


/*
* Function:  printUserMenu()
* 
* Description:
* prints the menu for the user to read.
* this is done every rotation so that the user
* doesn't have to remember the commands.
*
*/
void printUserMenu(){
	printf("\n");
	printf("Please enter the corresponding number of the action you wish to do. \n");
	printf("1) Write  - Allows you to write to the board. \n");
	printf("2) Read - Will ask for a valid number on the board to read. \n");
	printf("3) List - Will display the entire board to the screen. \n");
	printf("4) Exit - Leaves the program. \n");
	printf("\n");
	printf("Enter a response: ");
}


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
void *recvFunc(){
	char message[SIZE];
	char currentIP[SIZE];
	int currentPort = 0;
	
	pthread_mutex_t mutex;
	
	while(quitToken != 1){
		
			
		if(recvfrom(listenSock, message, SIZE, 0,(struct sockaddr*)&my_addr, &socklen) < 0 ){
			perror("thread recv: failed \n");
			exit(1);
		}
			
			
		if(strcmp(message,"token\0") == 0){
			pthread_mutex_trylock(&mutex);
			token = 1;
			pthread_mutex_unlock(&mutex);
		}
		else if(strcmp(message,"join\0") == 0){
			inet_ntop(AF_INET, &serv_addr.sin_addr,currentIP,SIZE);
			currentPort = ntohs(serv_addr.sin_port);
			if(sendto(listenSock, currentIP, SIZE, 0,(struct sockaddr*)&my_addr, len) < 0){
				printf("Failed to send IP \n");
			}
			if(sendto(listenSock, &currentPort, sizeof(currentPort), 0,(struct sockaddr*)&my_addr, len) < 0){
				printf("Failed to send IP \n");
			}
			inet_ntop(AF_INET, &my_addr.sin_addr,currentIP,SIZE);
			currentPort = ntohs(my_addr.sin_port);
			
			if(inet_pton(AF_INET, currentIP, &serv_addr.sin_addr) <  0){
				printf("inet_pton error occured\n");
				exit(1);
			} 
			serv_addr.sin_port =htons(currentPort);
			
		}
		else if(strcmp(message,"exit") == 0){
			if(recvfrom(listenSock, currentIP, SIZE, 0,(struct sockaddr*)&my_addr, &socklen) < 0 ){
				perror("thread recv: failed \n");
				exit(1);
			}
			if(recvfrom(listenSock, &currentPort, sizeof(currentPort), 0,(struct sockaddr*)&my_addr, &socklen) < 0 ){
				perror("thread recv: failed \n");
				exit(1);
			}
			
			
			if(inet_pton(AF_INET, currentIP, &serv_addr.sin_addr) <  0){
				printf("inet_pton error occured\n");
				exit(1);
			} 
			serv_addr.sin_port =htons(currentPort);
		}
		else{
			//do nothing
		}
			
	}
	
	return NULL;
}


/*
* Function:  connectToServer()
* 
* Description:
* If the -new option is put on the command line
* it calls this function so that the user will connect
* to the server to get information about it's peers.
*
*/
void connectToServer(char *argv[]){
	char firstIP[SIZE];
	char holdIP[SIZE];
	char buffer[SIZE];
	int serverPort = 0;
	int i = 0;
	
	serverPort = atoi(argv[4]);
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        exit(1);
    } 
	
	struct hostent *hp  = gethostbyname(argv[3]);
	
	if( hp == NULL){
		printf("hostent:Cannot gethostbyname \n");
		exit(1);
	}
	
	memset(firstIP,0,SIZE);
	while(hp->h_addr_list[i] != NULL){
		strcat(firstIP,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
		i++;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort); 
	
	if(inet_pton(AF_INET, firstIP, &serv_addr.sin_addr) <  0){
        printf("inet_pton error occured\n");
        exit(1);
    } 
	
	listenPort = atoi(argv[2]);
	if( sendto(sockfd, argv[2], 100, 0,(struct sockaddr *)&serv_addr, len) < 0 ){
		perror("send failed \n");
		exit(1);
	}
		
		
	if( recvfrom(sockfd, buffer, 100, 0,NULL, NULL) < 0 ){
		perror("recv failed \n");
		exit(1);
	} 
	strcpy(holdIP,buffer);
	
	if(recvfrom(sockfd, buffer,100,0,NULL,NULL) < 0){
		perror("recv failed \n");
		exit(1);
	}
	printf("Message RECV: Ip-%s  Port-%s \n",holdIP,buffer);
	
	createRingSocket(holdIP, buffer);
}


/*
* Function:  createRingSocket()
* 
* Description:
* Builds the socket for the ring depending on the 
* information that was provided by the server.
*
*/
void createRingSocket(char* ip, char* port){
	
	int portNum = atoi(port);
	
	serv_addr.sin_port = htons(portNum);
	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) < 0){
		printf("inet_pton error occured\n");
        exit(1);
	}
}


/*
* Function:  makeListenSocket()
* 
* Description:
* Creates the socket for the client to listen on.
*
*/
int makeListenSocket(char* port){
	int portNum = atoi(port);
	
	
	listenSock = socket(AF_INET,SOCK_DGRAM,0);
	if(listenSock < 0){
		perror("Failed to make socket \n");
		return 0;
	}
	
	memset(&my_addr,'0', sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(portNum);
	
	if(bind(listenSock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
		perror("Failed to bind socket \n");
		return 0;
	}
	
	
	return 1;
}


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
int generateToken(){
	int randTok = 0;
	
	srand(time(NULL));
	randTok = rand() % 300;
	randTok = randTok+(rand() % 300);
	
	
	return randTok;
}


/*
* Function:  findFirstToken()
* 
* Description:
* Passes around values till the highest value is found.
* Once found it is passed around and whoever matches that
* value is the first token.
*
*/
void findFirstToken(int tokCode){
	int myTok = tokCode;
	int highestTok = tokCode;
	int cmpTok = 0;
	int testTime = 0;
	
	printf("My Token: %d \n",tokCode);
	

	while(testTime < 1){
		
		if(sendto(sockfd, &highestTok, sizeof(cmpTok), 0,(struct sockaddr *)&serv_addr, len) < 0){
			perror("sending:Token Code \n");
			exit(1);
		}
		
		if(recvfrom(listenSock, &cmpTok, sizeof(cmpTok), 0,(struct sockaddr*)&my_addr, &socklen) < 0){
			perror("recv:Token Code \n");
			exit(1);
		}
		
		
		if(highestTok == cmpTok){
			testTime++;
		}
		
		if(highestTok < cmpTok){
			highestTok = cmpTok;
		}
		
		
	}
	
	
	if(sendto(sockfd, &highestTok, sizeof(cmpTok), 0,(struct sockaddr *)&serv_addr, len) < 0){
			perror("sending:Token Code \n");
			exit(1);
	}
	
	
	if(highestTok == myTok){
		token = 1;
		printf("Token set to 1 \n");
	}
	else{
		token = 0;
		printf("Token set to 0 \n");
	}
}