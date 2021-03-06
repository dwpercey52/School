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
	
	struct Customer{
		double arrivalTime;
		double startTime;
		double departureTime;
		double PQTime;
		CustomerP next;
	} Customer;
	
	struct Pqueue{
		double idleTime;		// Calculations from simulation
		double avgPeople;
		double avgTimeSpent;
		double avgNumQueue;
		double avgQueueTime;
		double timeTotal;
		
		int servedCounter;		//Stored Values amount served
		int serverAvailable;	//Servers
		int heapSize;			//PQ size
		int servedSize;			//current size of served array
		
		CustomerP PQ[PQUEUE_MAX];
		CustomerP ServedCust[SERVED_MAX]; //Served Customers to be calculated later
		CustomerP storedCust;
	} Pqueue;
	
	
	
	void runSimulation(mathStructP math, PqueueP queue);
	PqueueP newPQNode();
	CustomerP newCustNode();
	double getRandomInterval(int avg);
	void processEvent(PqueueP que, mathStructP mat);
	void insertPqueue(PqueueP Pqueue, CustomerP cust);
	CustomerP deletePqueue(PqueueP Pqueue);
	void percDown(PqueueP Pqueue, int position);
	void swapFunc(PqueueP que,int post1,int post2);
  


  
  
#endif