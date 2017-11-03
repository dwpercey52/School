/************************
*Name: Darrell W. Percey*
*File: RunSim.cabs		*
*For: Project 2			*
*						*
*************************/

#include "Simulation.h"
#include "MathFunc.h"

int main(){
	srand(time(NULL));
	mathStructP math = newMathNode();
	PqueueP PQ = newPQNode();
	runSimulation(math, PQ);
	printSimResults(PQ,math);
	free(PQ);
	free(math);
	
	return 0;
}