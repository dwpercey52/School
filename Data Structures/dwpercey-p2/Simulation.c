/************************
*Name: Darrell W. Percey*
*File: Simulation.c		*
*For: Project 2			*
*						*
*************************/


#include "Simulation.h"

/**************************** 
* Node Allocation Functions *
*****************************/

	/*
	* Function:  newPQNode
	*
	* Description:
	* Allocates memory for a new node of PQ to
	* hold all the information of the simulation.
	*
	*/
	PqueueP newPQNode(){
		int i;
		PqueueP temp = (PqueueP) malloc(sizeof(Pqueue));
		
	
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
	
	
	/*
	* Function:  newCustNode
	*
	* Description:
	* Allocates memory for a new customer in the system.
	*
	*/
	CustomerP newCustNode(){
		CustomerP temp = (CustomerP) malloc(sizeof(struct Customer));

		temp->arrivalTime = 0;
		temp->startTime = 0;
		temp->departureTime = -1;
		temp->next = NULL;
    
		return temp;
	}
	

	
/**************************** 
*   Simulation Functions    *
*****************************/
	
	
	/*
	* Function:  getRandomInterval
	*
	* Description:
	* Generates a random number on in the range of
	* 0..1
	*
	*/
	double getRandomInterval(int avg){
		float x = 0;
		float interval;
		x = (float)rand() / RAND_MAX;
		interval = -1*(1.0/avg)*log(x); 
	
		return interval;
	}
	
	
	/*
	* Function:  runSimulation
	*
	* Description:
	* Pushes the simlation by creating new items for
	* the PQ and also by calling ProcessEvent
	*/
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
		
		while( queue->heapSize > 0 ){
			processEvent(queue,math);
			
			
			if((queue->heapSize < (math->M)+1) && (queue->servedCounter < math->n)){
				i = 0;
				while( i < math->M){
					customer = newCustNode();
					insertPqueue(queue,customer);
					i++;
				}
			}
		}
	}
	
	
	/*
	* Function: processEvent
	*
	* Description:
	* Takes in the next event of the PQ and processes
	* it as an arrival or departure.
	*
	*/
	void processEvent(PqueueP que, mathStructP mat){
		double info;
		if(que->PQ[1]->departureTime == -1){
			if(que->serverAvailable > 0){
				//printf("1.Arrival \n");
				//que->timeTotal = que->PQ[1]->arrivalTime;
				que->serverAvailable--;
				que->PQ[1]->startTime = que->PQ[1]->arrivalTime;
				que->PQ[1]->PQTime = getRandomInterval(mat->l);
				que->PQ[1]->departureTime = que->PQ[1]->arrivalTime + que->PQ[1]->PQTime;
				//que->PQ[1]->PQTime = que->PQ[1]->departureTime; 
				CustomerP temp = deletePqueue(que);
				insertPqueue(que, temp);
			}
			else{
				CustomerP temp = que->storedCust;
				//printf("2.FIFO \n");
				if(temp != NULL){
					while(temp->next){
						temp = temp->next;
					}
					temp->next = deletePqueue(que);
				}
				else{
					que->storedCust = deletePqueue(que);
				}
			}
		}
		else{
		//	printf("4.Departure \n");
			que->serverAvailable++;
			que->servedCounter++;
			que->ServedCust[que->servedSize] = deletePqueue(que);
			que->servedSize++;
			if(que->storedCust != NULL){
			//	printf("5.Add/FIFO \n");
				CustomerP temp = que->storedCust;
				if(temp->next){
					que->storedCust = temp->next;
				}
				else{
					que->storedCust = NULL;
				}
				temp->startTime = que->ServedCust[que->servedSize-1]->departureTime;
				//temp->PQTime =   getRandomInterval(mat->l);
				info = getRandomInterval(mat->m);
				temp->departureTime = info + temp->startTime;
				temp->PQTime = temp->departureTime;
				insertPqueue(que,temp);
				que->serverAvailable--;
			}
		}
	}
	

	/*
	* Function:  printSimResults
	*
	* Description:
	* prints all the results of the simulations to the
	* screen in stdout.
	*
	*/
	void printSimResults(PqueueP que, mathStructP mat){
		int i;
		double waitAvg, avgTime, idleAvg, totalTime;
		
		i = 0;
		while(i < que->servedSize){
			if(que->ServedCust[i]){
				waitAvg =+ que->ServedCust[i]->startTime - que->ServedCust[i]->arrivalTime;
				avgTime =+ que->ServedCust[i]->departureTime - que->ServedCust[i]->startTime;
				totalTime =+ que->ServedCust[i]->departureTime;
				i++;
			}
			else{
				break;
			}
		}  
		waitAvg = (waitAvg/totalTime);
		avgTime = (avgTime/totalTime);
		printf("\n");
		printf("---Simulation--- \n");
		//printf("Po = [%.3f] \n",math->idleTime);
		printf("W = [%.3f] \n",avgTime);
		printf("Wq = [%.4f] \n",waitAvg);
		//printf("p = [%.3f] \n", math->utilization);
		
	}
	
/**************************** 
*      PQueue Functions     *
*****************************/
	
	/*
	* Function:  insertPqueue
	*
	* Description:
	* Inserts the new customer node that is provided
	* via paramter into the PQ. Also percUp is built
	* into this function.
	*
	*/
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
	
	
	/*
	* Function:  deletePqueue
	*
	* Description:
	* Takes the item out of poisition 1 in the
	* PQ and returns it. Also percdown to restore
	* heap condition
	*/
	CustomerP deletePqueue(PqueueP PQ){
		CustomerP temp = PQ->PQ[1];
		PQ->PQ[1] = PQ->PQ[PQ->heapSize];
		PQ->heapSize--;
		percDown(PQ,1);
		
		return temp;
	}
	
	
	/*
	* Function:  percDown
	*
	* Description:
	* Moves an item down the list to restore 
	* the heap condition.
	*
	*/
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
	
	
	
