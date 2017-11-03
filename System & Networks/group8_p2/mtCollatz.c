/*****************************************
*	Name: Darrell Percey && Andrew Boven *
*	File: myCollatz						 *
*	For: Project 2	System Networks I	 *
*	Date(LM): 9/29/20   				 *
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define MAXARGS 3
#define MAXINPUT 200
#define true 1
#define false 0
#define MAXCOLLATZ 1000

typedef int bool;


/*****************
*Global Variables*
*****************/ 
int threadStopTimes[MAXCOLLATZ];
int counter = 2;
/*****************
*Global Variables*
*	End			 *
*****************/ 

/************************************
*		Function Prototypes			*
*-See functions for more information*
************************************/
bool checkForNumber(char** argv);
void startHistogramArray();
void printHistogramArray();
void *threadFunc(void *arg);
int collatzFunc(long solve);
/************************************
*		Function Prototypes	End		*
*-See functions for more information*
************************************/


	
int main(int amountOfInput, char *argumentVector[]){
	int isValid = 0;
	int threadAmount = 0;
	int collatzAmount = 0;
	double totalTime = 0;
	struct timespec start, stop;
	
	
	//check user input for correctness numbers and 1 >
	if(amountOfInput == MAXARGS){
		isValid = checkForNumber(argumentVector);
		if(isValid == false){
			fprintf(stderr,"Wrong type of arguments! \n");
			exit(1);
		}
		threadAmount = atoi(argumentVector[2]);
		collatzAmount = atoi(argumentVector[1]);
		
		if(collatzAmount <= 1){
			//Makes sure the collatz series is 2 or more.
			fprintf(stderr,"Not enough numbers to Collatz! \n");
			exit(1);
		}
		else if(threadAmount < 1){
			//Makes sure the thread amount is 1 or higher
			fprintf(stderr,"Not enough threads \n");
			exit(1);
		}
	}
	else{
		//prints if there are the wrong amount of arguments
		fprintf(stderr,"Wrong amount of arguments! \n");
		exit(1);
	}
	//end of error checking inputs
	
	startHistogramArray();
	pthread_t threadVector[threadAmount];
	
	int i = 0;
	int *test = malloc(sizeof(*test));
	*test = collatzAmount;
	
	
	//Starts the clock used to calculate computing time
	//For loop to create multiple threads
	clock_gettime(CLOCK_REALTIME, &start);
	for(i = 0; i < threadAmount; i++){
		pthread_create(&threadVector[i],NULL,threadFunc, (void *)&collatzAmount);
	}
	
	//Close all threads and get end time
	for(i = 0; i < threadAmount; i++){
		pthread_join(threadVector[i],NULL);
	}
	clock_gettime(CLOCK_REALTIME, &stop);
	
	//Calculate and print all information to the screen or to a file.
	totalTime = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;
	printHistogramArray();
	fprintf(stderr,"%d,%d,%lf  \n",collatzAmount,threadAmount,totalTime);
	
	return 0;
}



	/*
	* Function:  threadFunc(void *)
	* Return: void *
	*
	* Description:
	* Computes the collatz increases the counter
	* for the next collatz. Stores the stopping time
	* that was computed.
	*
	*/
 
void *threadFunc(void *arg){
	int x = *((int *) arg);
	int temp;
	int stopTime;
	
	while(counter < x){
		temp = counter;
		counter++;
		stopTime = collatzFunc((long)temp);
		threadStopTimes[stopTime]++;
	}
	return (void *) 0;
}



	/*
	* Function:  startHistogramArray()
	* Return: 
	*
	* Description:
	* Starts the histogram array initilizing all
	* numbers to zero.
	*
	*/
 
void startHistogramArray(){
	int i;
	for(i = 0; i < MAXCOLLATZ; i++){
		threadStopTimes[i] = 0;
	}
}



	/*
	* Function:  printHistogramArray()
	* Return: 
	*
	* Description:
	* Prints all the non-zero histogram values
	* that were calculated.
	*
	*/
 
void printHistogramArray(){
	int i;
	for(i = 0; i < MAXCOLLATZ; i++){
		if(threadStopTimes[i] != 0){
			printf("%d, %d \n",i,threadStopTimes[i]);
		}
	}
	printf("\n");
}



	/*
	* Function:  collatzFunc(long)
	* Return: int
	*
	* Description:
	* Computes the collatz of the value passed into
	* the function. Then returns the stopping time of
	* the function to be stored.
	*
	*/
 
int collatzFunc(long solve){
	long stopTime = 0;
	
	if(solve == 1){
		return stopTime;
	}
	else{
		while(solve != 1){
			if(solve%2 == 0){
				solve = (solve/2);
				stopTime++;
			}
			else{
				solve = ((solve*3) + 1);
				stopTime++;
			}
		}
	}
	return stopTime;
}



	/*
	* Function:  checkForNumber()
	* Return: bool (int)
	*
	* Description:
	* Checks to see if the user input args is 
	* a number and not a letter.
	*
	*/
 
bool checkForNumber(char** argv){
	char temp1[MAXINPUT];
	char temp2[MAXINPUT];
	int i;
	
	strcpy(temp1,argv[1]);
	strcpy(temp2,argv[2]);
	
	for(i = 0; i < strlen(temp1); i++){
		if((temp1[i] >= 'a' && temp1[i] <= 'z') || (temp1[i] >= 'A' && temp1[i] <= 'Z')){
			return false;
		}
	}
	for(i = 0; i < strlen(temp2); i++){
		if((temp2[i] >= 'a' && temp2[i] <= 'z') || (temp2[i] >= 'A' && temp2[i] <= 'Z')){
			return false;
		}
	}
	
	return true;
}

