#include "Simulation.h"

/**************************** 
* Node Allocation Functions *
*****************************/
	
	PqueueP newPQNode(){
		int i;
		PqueueP temp = (PqueueP) malloc(sizeof(Pqueue));
		
		temp->idleTime = 0;
		temp->avgPeople = 0;
		temp->avgTimeSpent = 0;
		temp->avgNumQueue = 0;
		temp->avgQueueTime = 0;
		temp->timeTotal = 0;
		temp->servedCounter = 0;
		temp->serverAvailable = 0;
		temp->heapSize = 0;
		temp->servedSize = 0;
		
		for(i = 0; i < PQUEUE_MAX; i++){
			temp->PQ[i] = NULL;
		}
		for(i = 0; i < SERVED_MAX; i++){
			temp->ServedCust[i] = NULL;
		} 
		temp->storedCust = NULL;
		
		return temp;
	}
	
	CustomerP newCustNode(){
		CustomerP temp = (CustomerP) malloc(sizeof(struct Customer));

		temp->arrivalTime = 0;
		temp->startTime = 0;
		temp->departureTime = 0;
		temp->next = NULL;
    
		return temp;
	}
	
	
/**************************** 
*   Simulation Functions    *
*****************************/
	
	double getRandomInterval(int avg){
		float x = 0;
		float interval;
		x = (float)rand() / RAND_MAX;
		interval = -1*(1.0/avg)*log(x); 
	
		return interval;
	}
	
	
	void runSimulation(mathStructP math, PqueueP queue){
		CustomerP customer;
		int i = 0;
		queue->servedCounter = math->M;
		queue->serverAvailable = math->M;
		
		while(i < math->M){
			customer = newCustNode();
			customer->PQTime = customer->arrivalTime;
			insertPqueue(queue,customer);
			i++;
		}
		
		queue->servedCounter = math->M;
		queue->serverAvailable = math->M;
		
		while( queue->heapSize >= 0 ){
			//processevent
			if((queue->heapSize < (math->M)+1) && (queue->servedCounter < math->n)){
				i = 0;
				while( i < queue->serverAvailable){
					customer = newCustNode();
					insertPqueue(queue,customer);
					i++;
				}
			}
		}	
	}
	
	void processEvent(PqueueP que, mathStructP mat){
		if(que->PQ[1]->departureTime == 0){
			if(que->serverAvailable > 0){
				que->serverAvailable--;
				que->PQ[1]->startTime = que->[1]->arrivalTime;
				que->PQ[1]->PQTime = getRandomInterval(math->l);
				que->PQ[1]->departureTime = que->PQ[1]->startTime + que->[1]->PQTime;
				que->PQ[1]->PQTime = que->PQ[1]->departureTime;
				insertPqueue(que,que->PQ[1]);
			}
			else{
				CustomerP temp = que->storedCust;
				
			}
		}
		
	}
	
/**************************** 
*      PQueue Functions     *
*****************************/
	
	void insertPqueue(PqueueP Pqueue, CustomerP cust){
		
		int size = Pqueue->heapSize;
		size++;
		Pqueue->PQ[0] = cust;
		//Percup built into the function here
		while(cust->PQTime < Pqueue->PQ[size/2]->PQTime){
			Pqueue->PQ[size] = Pqueue->PQ[size/2];
			size /=2;
		}
		Pqueue->PQ[size] = cust;
		Pqueue->heapSize++;
	}
	
	CustomerP deletePqueue(PqueueP PQ){
		CustomerP temp = PQ->PQ[1];
		PQ->PQ[1] = PQ->PQ[PQ->heapSize];
		percDown(PQ,1);
		PQ->heapSize--;
		
		return temp;
	}
	
	 void percDown(PqueueP PQ, int position){
		int child;
		CustomerP temp = PQ->PQ[position];
    
		while(position * 2 <= PQ->heapSize) {
			child = position * 2;
			if( child != PQ->heapSize && PQ->PQ[child + 1] < PQ->PQ[child] ){
				child++;
			}
			if( PQ->PQ[child]->PQTime < temp->PQTime ){
				PQ->PQ[position] = PQ->PQ[child];
			}
			else{
				break;
			}
			position = child;
		}
		PQ->PQ[position] = temp;
	} 
	
	
	
