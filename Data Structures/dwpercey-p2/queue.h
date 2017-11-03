#ifndef queue
#define queue
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "matfuncs.h"
  /*************************************************************** 
  Student Name: Darrell Percey
  File Name: queue.h
  Assignment number 2
***************************************************************/

  	int serv, avgArrive, avgSerTime, serNumber;
  
	typedef struct Customer{
		double PQtime;
		double arrivalTime;
		double startServ;
		double depTime;
		struct Customer* nextCust;
		}Customer;
		
		
	double pQueue[100], waitQueue[1000];
	int front, back, front2, back2;
	
  
	void createQue();
	void askInfo();
	void sortPqueue();
	void nextCustomer(Customer* curr);
	void createArrivals(double time);
	int checkDept(Customer* top);
	double getRandomInterval(int avg);
	Customer* runSimulation(Customer* cust);
	Customer* startCustomer();
	Customer* processEvent(Customer* topCust, Customer* curr, double *time, int *servers);
  
  
#endif