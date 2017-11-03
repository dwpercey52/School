/****************************
*Name: Darrell W. Percey	*
*File: Test.c				*
*For: Project 3				*
*							*
*****************************/


#include <time.h>
#include "Tours.h"
#include "GraphBuild.h"


int main(){
	//Declare time clock and main struct for information
	//ask the user for information
	struct timespec start, stop;
	matrixP mat = makeMatrix();
	
	
	
	//Run the bruteforce
	clock_gettime(CLOCK_REALTIME, &start);
	mat->bestBruteForce = searchBruteForce(mat);
	clock_gettime(CLOCK_REALTIME, &stop);
	
	mat->bruteTime = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;

	printf("GEN TIME \n");
	
	//Run the genetic
	clock_gettime(CLOCK_REALTIME, &start);
	mat->bestGenetic = searchGen(mat);
	clock_gettime(CLOCK_REALTIME, &stop);
	
	mat->geneticTime = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;
	
	
	//Print all results
	printMatrix(mat);
	
	free(mat);
	
	return 0;
}

