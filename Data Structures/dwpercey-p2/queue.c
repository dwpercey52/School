#include "queue.h"
/*************************************************************** 
  Student Name: Darrell Percey
  File Name: queue.c
  Assignment number 2
***************************************************************/
void createpQue(){
	front = back = 0;
	front2 = back2 = 0;
}

//asks the user for all the input values.
void askInfo(){
	printf("Enter the number of service channels: ");
	scanf("%d", &serv);
	printf("Enter the average arrivals in a time period: ");
	scanf("%d", &avgArrive);
	printf("Enter the average served in a time period: ");
	scanf("%d", &avgSerTime);
	printf("Enter the number of arrivals to simulate: ");
	scanf("%d", &serNumber);
}

//Takes in the input for average served or arrivals
//then outputs a random number generated.
double getRandomInterval(int avg){
	float x = 0;
	float interval;
	int i;
	x = (float)rand() / RAND_MAX;
	interval = -1*(1.0/avg)*log(x); 
	
	return interval;
}

//makes a new customer node.
//returns the pointer to the new node made for customer. 
Customer* startCustomer(){
	Customer* cust = malloc(sizeof(Customer));
	cust->PQtime = 0;
	cust->arrivalTime = 0;
	cust->startServ = 0;
	cust->depTime = 0;
	cust->nextCust = NULL;
	return cust;
}

void nextCustomer(Customer* curr){
	Customer* temp = malloc(sizeof(Customer));
	temp->PQtime = 0;
	temp->arrivalTime = 0;
	temp->startServ = 0;
	temp->depTime = 0;
	temp->nextCust = NULL;
	curr->nextCust = temp;
}

void firstArrivals(){
	int i = 0;
	front = 0; 
	back = serv;
	for(i=0;i<serv;i++){
		pQueue[i]= getRandomInterval(avgArrive);
	}
	sortPqueue();
}

void createArrivals(double time){
	back ++;
	pQueue[back-1]= time + getRandomInterval(avgArrive);
	sortPqueue();
}


void sortPqueue(){
	int i = 0;
	int x = 0;
	int j = 0;
	double temp;

	
	for(i=1;i<back;i++){
		x = i;
		do{
			j = (x-1)/2;
			if(pQueue[j] > pQueue[x]){
				temp = pQueue[j];
				pQueue[j] = pQueue[x];
				pQueue[x] = temp;
			}
			x = j;
			
		}while(x != 0);
	}
}


int checkDept(Customer* top){
	int i = 0;
	
	while(top->nextCust != NULL){
		if(top->depTime == pQueue[front]){
			i=1;
		}
		top = top->nextCust;
	}
	return i;
}

void sortWqueue(){
	int i;
	front2 = 0;
	for(i=0; i<back2; i++){
		waitQueue[i] = waitQueue[i+1];
	}
	back2--;
}

Customer* processEvent(Customer* topCust, Customer* curr, double *time, int *servers){
		
		if(checkDept(topCust) == 0){
			if(*servers != 0){
				*time = pQueue[front];
				curr->arrivalTime = pQueue[front];
				curr->startServ = pQueue[front];
				curr->depTime = *time + getRandomInterval(avgSerTime);
				pQueue[front] = curr->depTime;
				nextCustomer(curr);
				curr = curr->nextCust;
				*servers = *servers - 1;
				sortPqueue();
			}
			else{
				*time = pQueue[front];
				waitQueue[back2] = pQueue[front];
				pQueue[front] = pQueue[back-2];
				back--;
				back2++;
				sortPqueue();
			}
		}
		else{
			*time = pQueue[front];
			*servers = *servers + 1;
			if(back2 == 0){
				curr->arrivalTime = waitQueue[front2];
				curr->startServ = pQueue[front];
				curr->depTime = *time + getRandomInterval(avgSerTime);
				pQueue[front] = curr->depTime;
				nextCustomer(curr);
				curr = curr->nextCust;
				*servers = *servers - 1;
				sortWqueue();
				sortPqueue();
			}
			else{
				pQueue[front] = pQueue[back-1];
				back--;
				sortPqueue();
			}
		
		}
	return curr;
}


//calls a lot of the main functions for operating the simulation
Customer* runSimulation(Customer* cust){
	int x = serv;
	int servers = serv;
	double hold_t = 0;
	
	Customer* p1;
	p1 = startCustomer();
	cust->nextCust = p1;
	createpQue();
	firstArrivals();
	
	while(front != back){
		p1 = processEvent(cust,p1,&hold_t, &servers);
		if( (x != serNumber) && (front <= back)){
			createArrivals(hold_t);
			x++;
		}
	}

	return cust->nextCust;
}
