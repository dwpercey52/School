/****************************
*Name: Darrell W. Percey	*
*File: GraphBuild.c			*
*For: Project 3				*
*							*
*****************************/

#include "GraphBuild.h"
#include "Tours.h"



/*
* Function:  makeMatrix
*
* Description:
* Creates a new matrix node
* 
*
*/
matrixP makeMatrix(){
	int i, j;
	matrixP temp = (matrixP) malloc(sizeof(matrix)); 
	FILE *input = fopen("cityWeights.txt","r");
	
	if(!input){
		perror("Couldn't open file. \n");
		exit(1);
	}
	
	for(i = 0; i < MATRIX_SIZE; i++){
		for(j = 0; j < MATRIX_SIZE; j++){
			if(i == j){
				temp->matrix[i][j] = 0;
			}
			else{
				fscanf(input,"%lf",&temp->matrix[i][j]);
			}
		}
	}
	
	fclose(input);
	askUserInformation(temp);
	return temp;
}


/*
* Function:  askUserInformation
*
* Description:
* Ask the user for input of the fields of information for Matrix node
* 
*
*/
void askUserInformation(matrixP mat){
	printf("What amount of cities would you like to run? [i.e 10, 11, 12] \n");
	scanf("%d",&mat->cityAmount);
	printf("How many tours per generation would you like to run? [i.e 10, 1000, 10000, 30000] \n");
	scanf("%d",&mat->tourAmount);
	printf("How many generations would you like to run? [i.e 1, 5, 10] \n");
	scanf("%d",&mat->generationAmount);
	printf("What percentage of mutations would you like? [i.e .1, .2, .3] \n");
	scanf("%lf",&mat->mutationPer);
}


/*
* Function:  printMatrix
*
* Description:
* Prints all results to the screen.
* 
*
*/
void printMatrix(matrixP mat){
	double percentOpt = (mat->bestGenetic/mat->bestBruteForce)*100.0;
	
	printf("-----------Information----------- \n");
	printf("Number of cities: %d \n",mat->cityAmount);
	printf("Best Bruteforce Tour: %.3lf \n",mat->bestBruteForce);
	printf("Bruteforce Time: %.6lf \n",mat->bruteTime);
	printf("\n");
	printf("Best Genetic Tour: %.3lf \n",mat->bestGenetic);
	printf("Genetic Time: %.6lf \n",mat->geneticTime);
	printf("Percent Optimal: %.2lf%% \n", percentOpt);
	printf("--------------------------------- \n");
}