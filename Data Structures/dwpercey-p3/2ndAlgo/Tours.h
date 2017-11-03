/****************************
*Name: Darrell W. Percey	*
*File: Tours.h				*
*For: Project 3				*
*							*
*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphBuild.h"


#ifndef Tours_h
#define Tours_h

#define BESTTOURSIZE 2


/**************************** 
* 		Structs				*
*****************************/

typedef struct generation* genP;

struct generation{
	int **tourList;
	int bestTours[BESTTOURSIZE];
	int bestToursDistance[BESTTOURSIZE];
}generation;



//See C file for all detailed descriptions on all functions below in order
/**************************** 
* 		Genetic				*
*****************************/
genP createNewGeneration(matrixP mat);
double searchGen(matrixP mat);
void firstGenerationSet(matrixP mat, genP gen);
void otherGenerations(matrixP mat, genP gen);
void mutateTour(int *tour, int n);
void findBestDistance(genP gen, matrixP mat);
/**************************** 
* 		Brute Force			*
*****************************/
long int factorial(int fac);
double searchBruteForce(matrixP mat);
double findDistance(matrixP mat, int *tour, int amount);


/**************************** 
* 		Shared				*
*****************************/
void swap(int *arr, int x, int y);
void permute(int *tour, int n);




#endif