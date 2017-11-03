/****************************
*Name: Darrell W. Percey	*
*File: GraphBuild.h			*
*For: Project 3				*
*							*
*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GraphBuild_h
#define GraphBuild_h

#define MATRIX_SIZE 20


/**************************** 
* 		Structs				*
*****************************/

typedef struct matrix* matrixP;

struct matrix{
	double matrix[MATRIX_SIZE][MATRIX_SIZE];
	
	int cityAmount;
	int tourAmount;
	int generationAmount;
	double mutationPer;
	
	//Other stuff
	double bestBruteForce;
	double bruteTime;
	double bestGenetic;
	double geneticTime;
	
}matrix;



//See C file for all detailed descriptions on all functions below in order
matrixP makeMatrix();
void askUserInformation(matrixP mat);
void printMatrix(matrixP mat);


#endif