#include "Simulation.h"
#include "MathFunc.h"

int main(){
	srand(time(NULL));
	mathStructP math = newMathNode();
	PqueueP PQ = newPQNode();
	runSimulation(math, PQ);
	
	return 0;
}