/************************
*Name: Darrell W. Percey*
*File: Simulation.h		*
*For: Project 2			*
*						*
*************************/

#ifndef Simulation
#define Simulation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MathFunc.h"


#define PQUEUE_MAX 200
#define SERVED_MAX 20000

	typedef struct Customer* CustomerP;
	typedef struct Pqueue* PqueueP;
	typedef struct mathStruct* mathStructP;
	
/**************************** 
* 		Structs				*
*****************************/	

	struct Customer{
		double arrivalTime;
		double startTime;
		double departureTime;
		double PQTime;
		CustomerP next;
	} Customer;
	
	struct Pqueue{
		double timeTotal;
		
		int servedCounter;		//Stored Values amount served
		int serverAvailable;	//Servers
		int heapSize;			//PQ size
		int servedSize;			//current size of served array
		
		CustomerP PQ[PQUEUE_MAX];
		CustomerP ServedCust[SERVED_MAX]; //Served Customers to be calculated later
		CustomerP storedCust;
	} Pqueue;
	
	
//see C file for all detailed descriptions
/**************************** 
* Node Allocation Functions *
*****************************/
	PqueueP newPQNode();
	CustomerP newCustNode();

/**************************** 
*   Simulation Functions    *
*****************************/
	double getRandomInterval(int avg);
	void runSimulation(mathStructP math, PqueueP queue);
	void processEvent(PqueueP que, mathStructP mat);
	void printSimResults(PqueueP que, mathStructP mat);

/**************************** 
*      PQueue Functions     *
*****************************/
	void insertPqueue(PqueueP Pqueue, CustomerP cust);
	CustomerP deletePqueue(PqueueP Pqueue);
	void percDown(PqueueP Pqueue, int position);
  
  
#endif