/************************
*Name: Darrell W. Percey*
*File: MathFunc.h		*
*For: Project 2			*
*						*
*************************/

#ifndef MathFunc
#define MathFunc
#include <math.h>
#include "Simulation.h"
	
	typedef struct mathStruct* mathStructP;
	
/**************************** 
* 		Structs				*
*****************************/
	struct mathStruct{
		double n; //arrivals
		double l; //arrivals in time
		double m; //served in time
		double M; //service channels
		
		double idleTime;
		double avgPeople;
		double avgTimeSpent;
		double avgNumQueue;
		double avgQueueTime;
		double utilization;
	} mathStruct;
	

//See C file for all detailed descriptions
	mathStructP newMathNode();
	void runMathCalculations(mathStructP math); 
	void askValues(mathStructP math);
	double factorial(double fac);
	double percentIdle(mathStructP math);
	double avgPeopleIn(mathStructP math);
	double avgTimeSpent(mathStructP math);
	double avgNumQueue(mathStructP math);
	double avgQueueTime(mathStructP math);
	double utilFactor(mathStructP math);
	void printMathCalculations(mathStructP math);

#endif
