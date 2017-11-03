/*****************************************
*	Name: Darrell Percey && Andrew Boven *
*	File: myshell.c						 *
*	For: Project 1	System Networks I	 *
*	Date(LM): 9/18/20   				 *
******************************************/


#include "parse.h"



int main(int argc,char *argv[]){
	int x = 0;
	char userInput[MAXUSERINPUT];
	bool debugMode = false;
	PARAMP ptr = newParamNode();
	
	//test for arg input from launching main program
	if(argc > true){
		debugMode =	checkArgs(argc, argv);
		if(debugMode == false){
			printf("Invalid or too many arguement(s) \n");
			exit(1);
		}
	}
	
	//prints information for the user to read
	system("clear");
	printShellInformation();
	
	
	//Shell loop, ends when user enters "exit"
	while(x == 0){
		printf("Enter a command to execute:  ");
		fgets(userInput, sizeof userInput, stdin);
		userInput[strlen(userInput) - 1] = '\0';
		parseUserInput(userInput, ptr);
		
		//Checks for the input "exit"
		if(strcmp(userInput,"exit") == 0){
			printf("Closing the program, Goodbye! \n");
			free(ptr);
			exit(1);
		}
		
		//Checks if the user wants to clear the screen
		if(strcmp(userInput,"clear") == 0){
			system("clear");
			printShellInformation();
		}
		else{
			if(debugMode == true){
				//If the user ran the program in debug mode
				//it will print their input paramters
				printParams(ptr);
			}
		
		
			execCommands(ptr);
		
			freeArgumentMemeory(ptr);
		}
	}

	return 0;
}


	/*
	* Function:  checkArgs(int, char*)
	* Return: int
	*
	* Description:
	* Checks to see if the main program is being ran in 
	* "debug" mode or not. 
	* 
	*/


int checkArgs(int argAmount, char* argv[]){
	if(argAmount > MAXARGUEMENTS){
		return false;	
	}
	else if(strcmp(argv[1], "-Debug") == 0){
		return true;
	}
	else{
		return false;
	}
}

	/*
	* Function:  printShellInformation()
	* Return: void
	*
	* Description:
	* Prints general information to the screen for the user
	* to understand how to operate the shell. This can be reprinted
	* if the user inputs "clear"
	* 
	*/

void printShellInformation(){
	
	printf("------------------------------------------------------------ \n");
	printf("|Welcome to my shell! You can input the programs you would | \n");
	printf("|like to run here. Running [./myshell -Debug] option will  | \n");
	printf("|give you a debug print out of parameters. You can type    | \n");
	printf("|the command 'clear' to clear the screen and reprint       | \n");
	printf("|this set of instructions to the screen.  Typing in the    | \n");
	printf("|command 'exit' will close this program. Have fun!         | \n");
	printf("------------------------------------------------------------ \n ");
	
	
	printf("----------------Examples of commands------------------------ \n");
	printf("| testme 4 100   runs 4 instances of testme                | \n");
	printf("| ./prime 2 300  runs 2 instance of prime                  | \n");
	printf("| <input.txt    gives an input redirection for input.txt   | \n");
	printf("| >output.txt   gives an output redirection for output.txt | \n");
	printf("------------------------------------------------------------ \n \n ");
	

}