/****************************************************************/
/* Darrell Percey	&&   Andrew Boven		                   	*/
/* bbfile.c                                                     */
/* Project 1 || System Networks II							   	*/
/*               											   	*/
/*	This program handles all the file operations done to the	*/
/*  shared file or "bullentin board". None of these actions 	*/
/*  can be executed till the user has the token in their 		*/
/*  possension												    */
/*                                                             	*/
/****************************************************************/
#include "bbfile.h"

/*
* Function:  writeToFile()
* 
* Description:
* This opens the file and writes to the file a new 
* input from the user. It will find out how many lines
* are in the documents and place the header and footer on it.
*
*/
void writeToFile(char* file, char* input){
	char headnfoot[SIZE];
	int messageAmt;
	FILE *fp;
	
	messageAmt = findMessageAmount(file);
	messageAmt++;
	
	snprintf(headnfoot,sizeof(headnfoot),"<message %d>\n",messageAmt);
	
	fp = fopen(file,"a");
	
	if(!fp){
		printf("File couldn't open! \n");
		exit(1);
	}
	
	fputs(headnfoot,fp);
	fputs(input,fp);
	snprintf(headnfoot,sizeof(headnfoot),"</message %d>\n",messageAmt);
	fputs(headnfoot,fp);
	
	fclose(fp);
}


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
void readMessage(char* file, int messageNum){
	int amount = 0;
	int i = 0;
	char message[SIZE];
	FILE *fp;
	
	fp = fopen(file,"r");
	
	if(!fp){
		printf("File couldn't open! \n");
		exit(1);
	}
	
	amount = findMessageAmount(file);
	
	if( amount != 0){
		if( messageNum > amount){
			printf("There is only %d message(s) \n",amount);
		
			while(messageNum > amount){
				printf("Enter a new #: ");
				scanf("%d",&messageNum);
			}
		}
	
		if(messageNum == 1){
			messageNum = 3;
			while(i < messageNum){
				fgets(message,SIZE,fp);
				printf("%s",message);
				i++;
			}
		}
		else{
			messageNum = messageNum*3;
			while(fgets(message,SIZE,fp) != NULL){
			
				if(i >= messageNum-3 && i < messageNum){
					printf("%s",message);
				}
				i++;
			}
		}
	}
	else{
		printf("There are 0 message \n");
	}
	
	fclose(fp);
	
}

/*
* Function:  listMessages()
* 
* Description:
* Post all messages to the stdout for the user
*
*/
void listMessages(char* file){
	char message[SIZE];
	FILE *fp;
	
	fp = fopen(file, "r");
	
	if(!fp){
		printf("File couldn't open! \n");
		exit(1);
	}
	
	while(fgets(message,SIZE,fp) != NULL){
		printf("%s",message);
	}
	
	fclose(fp);
}


/*
* Function:  findMessageAmount()
* 
* Description:
* Goes through the entire file to find the
* number of messages in the file. This is called by
* readMessage and writeToFile functions.
*
*/
int findMessageAmount(char* file){
	int amount = 0;
	char message[SIZE];
	char *tok;
	FILE *fp;
	
	fp = fopen(file,"r");
	
	if(!fp){
		printf("File couldn't open! 2 \n");
		exit(1);
	}
	
	fseek(fp,0,SEEK_END);
	
	if(ftell(fp) == 0){
		amount = 0;
	}
	else{
		rewind(fp);
		
		while(fgets(message,SIZE,fp) != NULL){
		}
		tok = strtok(message, " >");
		tok = strtok(NULL," >");
	
		amount = atoi(tok);
	}
	
	fclose(fp);
	
	return amount;
}