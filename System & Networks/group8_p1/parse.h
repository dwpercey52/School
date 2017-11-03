/*****************************************
*	Name: Darrell Percey && Andrew Boven *
*	File: parse.h						 *
*	For: Project 1	System Networks I	 *
*	Date(LM): 9/18/20					 *
******************************************/


#ifndef parse
#define parse
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXARGS 32
#define MAXARGUEMENTS 2
#define MAXUSERINPUT 200
#define true 1
#define false 0


/***********************
* Structures & typedef *
************************/
  
	
	typedef struct PARAM* PARAMP;
	typedef int bool;
	
	struct PARAM{
		char* inputRedirect;
		char* outputRedirect;
		int argumentCount;
		char *argumentVector[MAXARGS];
	} PARAM;
	
	
	
/***********************
* Structures & typedef *
* 			End        *
************************/
	
	/*
	* Function:  checkArgs(int, char*)
	* Return: int
	*
	* Description:
	* Checks to see if the main program is being ran in 
	* "debug" mode or not. 
	* 
	*/
	int checkArgs(int argAmount, char* argv[]);
	
	/*
	* Function:  printShellInformation()
	* Return: void
	*
	* Description:
	* Prints general information to the screen for the user
	* to understand how to operate the shell. This can be reprinted
	* if the user inputs "clear".
	* 
	*/
	void printShellInformation();
	
	/*
	* Function:  printParams(struct* PARAM)
	* Return: void
	*
	* Description:
	* Prints all store values inside the PARAM type
	* node. If there is no value, then NULL is printed.
	* 
	*/
	void printParams(PARAMP parameters);
	
	/*
	* Function:  newParamNode()
	* Return: struct* PARAM
	*
	* Description:
	* Prints all store values inside the PARAM type
	* node. If there is no value, then NULL is printed.
	* 
	*/
	PARAMP newParamNode();
	
	
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
	bool checkForFile(char* fileName);
	
	
	/*
	* Function:  freeArgumentMemeory(struct* PARAM)
	* Return: void
	*
	* Description:
	* Frees the memory of each piece of the struct till
	* it is used again for the next set of arguments
	*
	*/
	void freeArgumentMemeory(PARAMP ptr);
	
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
	void parseUserInput(char* input, PARAMP para);
	
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
	int addInputArguments(PARAMP para, int argumentPlace);
	
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
	char** buildExecString(PARAMP para, char* instance);
	
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
	void execCommands(PARAMP para);

  
#endif