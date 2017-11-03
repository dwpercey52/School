/************************
*Name: Darrell W. Percey*
*File: MathFunc.c 		*
*For: Project 2			*
*						*
*************************/

#include "MathFunc.h"

	/*
	* Function:  newMathNode
	*
	* Description:
	* Creates a new mathStruct and runs calculations
	* 
	*
	*/
	mathStructP newMathNode(){
		mathStructP temp = (mathStructP) malloc(sizeof(mathStruct));
		askValues(temp);
		return temp;
	}
	
	
	/*
	* Function:  runMathCalculations
	*
	* Description:
	* Runs all the functions for each calculation
	* that needs to be solved.
	*
	*/
	void runMathCalculations(mathStructP math){
		math->idleTime = percentIdle(math);
		math->avgPeople = avgPeopleIn(math);
		math->avgTimeSpent = avgTimeSpent(math);
		math->avgNumQueue = avgNumQueue(math);
		math->avgQueueTime = avgQueueTime(math);
		math->utilization = utilFactor(math);
		
	}
	
	
	/*
	* Function:  askValues
	*
	* Description:
	* Ask the user for the input values for the
	* calculations and simulation.
	*
	*/
	void askValues(mathStructP math){
		printf("Enter a number of arrivals to simulate:  ");
		scanf("%lf",&math->n);
		printf("Enter average arrivals in a time period:  ");
		scanf("%lf",&math->l);
		printf("Enter average number served in a time period:  ");
		scanf("%lf",&math->m);
		printf("Enter number of service channels:  ");
		scanf("%lf",&math->M);
		
		runMathCalculations(math);
		printMathCalculations(math);
		
	}
	
	
	/*
	* Function:  factorial
	*
	* Description:
	* solves for the factorial of the inputed number
	*
	*/
	double factorial(double fac){
		double x = 1;
		int i;
	
		if(fac == 0){
			x = 1;
		}
		else{
			for(i = 1;i <= fac; i++){
				x = x * i;
			}
		}
		return x;
	}
	
	
	/*
	* Function:  percentIdle
	*
	* Description:
	* Solves for the percent of idle time in the system.
	*
	*/
	double percentIdle(mathStructP math){
		double total1 = 0, total2 = 0, sum = 0;
		int i;
		
		for(i = 0; i <= (math->M)-1; i++){
			total1 += (1.0/factorial(i))*(pow((math->l/math->m),i));
		}
		
		total2 = (1.0/factorial(math->M))*(pow((math->l/math->m),math->M))*((math->M*math->m)/((math->M * math->m) - math->l));
		sum = 1.0/(total1 + total2);
		
		return sum;
	}
	
	
	/*
	* Function:  avgPeopleIn
	*
	* Description:
	* Solves for the average amount of people that
	* will be in the system.
	*
	*/
	double avgPeopleIn(mathStructP math){
		double total1, total2, sum;
		
		total1 = ((math->l * math->m)*(pow((math->l/math->m),math->M)));
		total2 = (factorial((math->M)-1) * pow(((math->M * math->m) - math->l),2));
		total1 = (total1/total2) * math->idleTime;
		total2 = (math->l / math->m);
		sum = total1 + total2;
	
		return sum;
	}
	
	
	/*
	* Function:  avgTimeSpent
	*
	* Description:
	* solves for the average time a person will be
	* in the system.
	*
	*/
	double avgTimeSpent(mathStructP math){
		double sum;
		sum = math->avgPeople / math->l;
		return sum;
	}
	
	
	/*
	* Function:  avgNumQueue
	*
	* Description:
	* Finds the average amount of people that will be in
	* the queue at a given time.
	*
	*/
	double avgNumQueue(mathStructP math){
		double sum;
		sum = math->avgPeople - (math->l / math->m);
		return sum;
	}
	
	
	/*
	* Function:  avgQueueTime
	*
	* Description:
	* Solves for the average time a user will wait
	* in the queue.
	*
	*/
	double avgQueueTime(mathStructP math){
		double sum;
		sum = math->avgNumQueue / math->l;
		return sum;
	}
	
	
	/*
	* Function:  utilFactor
	*
	* Description:
	* Solves for the ultility factor
	*
	*/
	double utilFactor(mathStructP math){
		double sum;
		sum = ((math->l)/((math->m)*(math->M)));
		return sum;
	}
	

	/*
	* Function:  printMathCalculations
	*
	* Description:
	* Prints all calculations in the math portion
	* to the stdout 
	*
	*/
	void printMathCalculations(mathStructP math){
		printf("Po = [%.3f] \n",math->idleTime);
		printf("L = [%.3f] \n",math->avgPeople);
		printf("W = [%.3f] \n",math->avgTimeSpent);
		printf("Lq = [%.3f] \n",math->avgNumQueue);
		printf("Wq = [%.4f] \n",math->avgQueueTime);
		printf("p = [%.3f] \n", math->utilization);
	}
