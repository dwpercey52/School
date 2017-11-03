/*****************************************
*	Name: Darrell Percey && Andrew Boven *
*	File: parse.c						 *
*	For: Project 1	System Networks I	 *
*	Date(LM): 9/18/20					 *
******************************************/

#include "parse.h"


	/*
	* Function:  printParams(struct* PARAM)
	* Return: void
	*
	* Description:
	* Prints all store values inside the PARAM type
	* node. If there is no value, then NULL is printed.
	* 
	*/

	void printParams(PARAMP para){
		int i;
		printf("InputRedirect: [%s]\n",(para->inputRedirect != NULL) ? para->inputRedirect:"NULL");
		printf("OutputRedirect: [%s]\n",(para->outputRedirect != NULL) ? para->outputRedirect:"NULL");
		printf("argumentCount: [%d]\n",para->argumentCount);
		for(i = 0; i < para->argumentCount; i++){
			printf("Arguement Vector[%2d]: [%s]\n", i, para->argumentVector[i]);
		}
	}
	
	
	/*
	* Function:  newParamNode()
	* Return: struct* PARAM
	*
	* Description:
	* Prints all store values inside the PARAM type
	* node. If there is no value, then NULL is printed.
	* 
	*/
	
	PARAMP newParamNode(){
		PARAMP temp = (PARAMP) malloc(sizeof(PARAM));
		temp->inputRedirect = NULL;
		temp->outputRedirect = NULL;
		temp->argumentCount = 0;
		return temp;
	}
	
	
	
	/*
	* Function:  checkForFile(char*)
	* Return: bool (int)
	*
	* Description:
	* Creates a list of all files in directory and
	* compares them to the first arugment the user inputs
	* to see if that is a valid choice.
	*
	*/
	bool checkForFile(char* fileName){
		system("ls >listOfFileInCWD.txt");
		FILE* in;
		char temp[MAXUSERINPUT];
		char temp2[MAXUSERINPUT];
		
		//takes the ./ off the filename for comparison
		strcpy(temp2,fileName);
		if(temp2[0] == '.'){
			if(temp2[1] == '/'){
				int i;
				for(i = 0; i < strlen(temp2); i++){
					temp2[i] = temp2[i+2];
				}
			}
		}
		
		//opens the list of files in directory
		in = fopen("listOfFileInCWD.txt","r");
		if(!in){
			return false;
		}
		
		//compares all name to input file name
		while(fgets(temp, MAXUSERINPUT, in) != NULL){
			temp[strlen(temp)-1] = '\0';
			
			if(strcmp(temp2, temp) == 0){
				fclose(in);
				return true;
			}
		}
		fclose(in);
		return false;
	}
	

	
	
	/*
	* Function:  freeArgumentMemeory(struct* PARAM)
	* Return: void
	*
	* Description:
	* Frees the memory of each piece of the struct till
	* it is used again for the next set of arguments
	*
	*/
	void freeArgumentMemeory(PARAMP ptr){
		free(ptr->outputRedirect);
		free(ptr->inputRedirect);
		int i;
		
		for(i = 0; i < MAXARGS; i++){
			free(ptr->argumentVector[i]);
		}
	}
	
	
	/*
	* Function:  parseUserInput(char*, struct* PARAM)
	* Return: void
	*
	* Description:
	* Takes in the string from the user input and decides 
	* in which part of the PARAM node to store it. 
	* If input an input file is added, it must add that to 
	* the list of paramters.
	*
	*/
	void parseUserInput(char* input, PARAMP para){
		char* temp = strtok(input," ");
		char tempHolder[MAXUSERINPUT];
		int i;
		int j = 0;
		para->argumentCount = 0;
		para->outputRedirect = NULL;
		para->inputRedirect = NULL;
		
		//Tokenizes till the end of the input string
		while(temp != NULL){
			if(temp != NULL){
				strcpy(tempHolder, temp);
			}
			//finds the output redirect value by finding an '>' sign
			if(tempHolder[0] == '>'){
				if(para->outputRedirect == NULL){
					para->outputRedirect = malloc(30*sizeof(char));
				}
				if(tempHolder[1] == '\0'){
					temp = strtok(NULL," ");
					strcpy(para->outputRedirect,temp);
				}
				else{
					for(i = 0; i < strlen(tempHolder); i++){
						tempHolder[i] = tempHolder[i+1];
					}
					strcpy(para->outputRedirect,tempHolder);
				}
			} //finds the output redirect value by finding an '<' sign
			else if(tempHolder[0] == '<'){
				if(para->inputRedirect == NULL){
					para->inputRedirect = malloc(30*sizeof(char));
				}
				if(tempHolder[1] == '\0'){
					temp = strtok(NULL," ");
					strcpy(para->inputRedirect,temp);
				}
				else{
					for(i = 0; i < strlen(tempHolder); i++){
						tempHolder[i] = tempHolder[i+1];
					}
					strcpy(para->inputRedirect,tempHolder);
				}
				//Adds the input arguments from the file the user picked for input
				j = addInputArguments(para, j);
			}
			else if( j < MAXARGS){
				para->argumentVector[j] = malloc(30*sizeof(char));
				strcpy(para->argumentVector[j],tempHolder);
				para->argumentCount++;
				j++;
			}
			temp = strtok(NULL," ");
		}
		//Nulls any remaining spots (clean up) 
		while(j < MAXARGS){
			para->argumentVector[j] = NULL;
			j++;
		}
	}

	
	/*
	* Function:  addInputArguments(struct* PARAM, int)
	* Return: int
	*
	* Description:
	* If there is an input file then this will read the arguments
	* from the fail and return the position where it left off.
	* That way any following arguments will be included.
	*
	*/
	int addInputArguments(PARAMP para, int argumentPlace){
		char temp[MAXUSERINPUT];
		FILE* in;
		int i = 0;
		
		//opens the file that the user said was input
		in = fopen(para->inputRedirect,"r");
		if(!in){
			printf("That input file doesn't exist! \n");
			return argumentPlace;
		}
		
		//Tokenizes each piece by a space
		//CANNOT USE STRTOK HERE!
		//Using strtok causes the strtok in parse function to lose its 
		//position as strtok uses a global placement holder!
		while(!feof(in)){
			i = 0;
			temp[i] = fgetc(in);
			while(temp[i] != ' '){
				i++;
				temp[i] = fgetc(in);
				if(feof(in)){
					break;
				}
			}
			temp[strlen(temp)-1] = '\0';
		
		// adds the argument the PARAM node
			if(argumentPlace < MAXARGS){
				para->argumentVector[argumentPlace] = malloc(30*sizeof(char));
				strcpy(para->argumentVector[argumentPlace],temp);
				para->argumentCount++;
				printf("ARG: %d \n",argumentPlace);
				argumentPlace++;
			}
		
		}
		
		fclose(in);
		return argumentPlace;
	}
	
	
	/*
	* Function:  buildExecString(struct* PARAM, char*)
	* Return: char**
	*
	* Description:
	* This builds an arugment array that can be passed to
	* the execv function. This will allow for a bunch of different
	* arguments complied to one input.
	*
	*/
	char** buildExecString(PARAMP para, char* instance){
		char** temp = malloc(32*sizeof(char*));
		int i = 0;
		
		if(para->argumentCount == 1){
			temp[i] = para->argumentVector[i];
			temp[i+1] = '\0';
		}
		else{
		// adds in the number for each process
			for(i = 0; i < para->argumentCount+1; i++){
				if(i == 0 ){
					temp[i] = para->argumentVector[0];
				}
				else if(i == 1){
					temp[i] = para->argumentVector[1];
				}
				else if(i == 2){
					temp[i] = instance;
				}
				else{
					if(para->argumentVector[i-1] != NULL){
						temp[i] = para->argumentVector[i-1];
					}	
				}
				temp[i+1] = '\0';
			}
		
		}

		
		return temp;
	}
	
	
	/*
	* Function:  execCommands(struct* PARAM)
	* Return: void
	*
	* Description:
	* This will call buildExecString to make an argument array.
	* Once the array is ready it will then fork to make a child process
	* If it's the parent, it will wait for child to finish. Once child is
	* finished it will loop multiple times till all children are done.
	*
	*/
	void execCommands(PARAMP para){
		int i = 0;
		int status = 0;
		bool isFile = false;
		int instances = 1;
		char** str = NULL;
		char *hold = malloc(5*sizeof(char));
	
		if(para->argumentCount > 1){
			instances = atoi(para->argumentVector[1]);
		}
		
		
		for(i = 0; i < instances; i++){
			sprintf(hold,"%d",i);
			str = buildExecString(para, hold);
			
			//looks for output redirect
			//Also forks and waits for children process
			pid_t pidChild = fork();
			if(pidChild == 0){
				if(para->outputRedirect != NULL){
					if(i == 0){
						printf("Output redirected to [%s] \n",para->outputRedirect);
						freopen(para->outputRedirect,"w",stdout);
					}
					else{
						freopen (para->outputRedirect,"a+",stdout);
					}
				}
				
				
				isFile = checkForFile(str[0]);
				if(isFile == true){
					char temp[MAXUSERINPUT];
					strcpy(temp,str[0]);
					if(temp[0] != '.'){
						int j;
						for(j = strlen(temp)+2; j > 0; j--){
							temp[j] = temp[j-2];
						}
						temp[0] = '.';
						temp[1] = '/';
						strcpy(str[0],temp);
					}
					
				}
				
				
				execvp(str[0],str);
				exit(0);
			}
			else if(pidChild < 0){
				perror("Fork Failed! \n");
			}
			else{
				waitpid(pidChild, &status, 0);
			} 
		} 
		
		free(str);
		free(hold);
	}
	
	