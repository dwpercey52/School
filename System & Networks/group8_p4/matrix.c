/***************************************************************/
/* Darrell Percey && Andrew Boven                              */
/* matrix.c                                                    */
/* Project 4 || System Networks I							   */
/*               											   */
/*															   */	
/*	This program will declare a large array size of 20480x4096 */
/*	Using that array it will then write and access each of the */
/*	positions in the array. It will write into the array by    */
/* 	column first then it will do it in rows. Doing each of     */
/* 	these operations 10 times for an average time. Then it will*/
/*	do the same for reading (accessing) each array position    */
/*                      									   */	
/*	Files Needed: matrix.c                                     */
/* First command line is with optimization the second is w/o   */
/*   gcc -Wall matrix.c -o matrix 						       */
/*	 gcc -O0 matrix.c         (output file 'a.out')		       */
/*                                                             */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_AMOUNT 20480
#define COL_AMOUNT 4096
#define TEST_NUMBERS 10
#define TEST_TIME 4

/************************************
*		2-D Array and Time Struct	*
************************************/
char testArr[ROW_AMOUNT][COL_AMOUNT];
struct timespec start, stop;


/************************************
*		Function Declarations		&
*	See functions for more detail   *
************************************/
double writeToCol();
double writeToRow();
double accessCol();
double accessRow();
void printInformation(double *info);

int main(){
	//Holds all times for each operation (summed of 10 times)
	double timeAverage[TEST_TIME] = {0,0,0,0};
	
	/************************************
	*		Write by Columns			*
	************************************/
	timeAverage[0] = writeToCol();
	
	/************************************
	*		Write by Rows				*
	************************************/
	timeAverage[1] = writeToRow();
	
	/************************************
	*		Access by Columns			*
	************************************/
	timeAverage[2] = accessCol();
	
	/************************************
	*		Access by Rows				*
	************************************/
	timeAverage[3] = accessRow();

	/************************************
	*		Print Information			*
	************************************/
	printInformation(timeAverage);
	
	return 0;
}


/*
* Function:  writeToCol()
* Return: double
*
* Description:
* Writes a char to every position in
* the 2-D array 10 times and takes a
* average of all those times and returns that
* value. This function writes in order by column
*
*/
double writeToCol(){
	int i, j, n;
	double timeTemp[TEST_NUMBERS];
	double timeTotal;
	
	for(n = 0; n < TEST_NUMBERS; n++){
		
		clock_gettime(CLOCK_REALTIME, &start);
		for(i = 0; i < COL_AMOUNT; i++){
			for(j = 0; j < ROW_AMOUNT; j++){
				testArr[j][i] = 'a';
			}
		}
		clock_gettime(CLOCK_REALTIME, &stop);
		
		timeTemp[n] = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;
	}
	
	for(i = 0; i < TEST_NUMBERS; i++){
		timeTotal += timeTemp[i];
	}
	timeTotal = timeTotal / 10.0;
	
	return timeTotal;
}


/*
* Function:  writeToRow()
* Return: double
*
* Description:
* Writes a char to every position in
* the 2-D array 10 times and takes a
* average of all those times and returns that
* value. This function writes in order by row
*
*/
double writeToRow(){
	int i, j, n;
	double timeTemp[TEST_NUMBERS];
	double timeTotal;
	
	for(n = 0; n < TEST_NUMBERS; n++){
		
		clock_gettime(CLOCK_REALTIME, &start);
		for(i = 0; i < ROW_AMOUNT; i++){
			for(j = 0; j < COL_AMOUNT; j++){
				testArr[i][j] = 'b';
			}
		}
		clock_gettime(CLOCK_REALTIME, &stop);
		
		timeTemp[n] = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;
	}
	
	for(i = 0; i < TEST_NUMBERS; i++){
		timeTotal += timeTemp[i];
	}
	timeTotal = timeTotal / 10.0;
	
	return timeTotal;
}



/*
* Function:  accessCol()
* Return: double
*
* Description:
* Accesses all the positions in the
* 2-D array in order of columns.
* Carries out this operation 10 times
* and then sums the times for an average
* 
*/
double accessCol(){
	int i, j, n;
	char temp;
	double timeTemp[TEST_NUMBERS];
	double timeTotal;
	
	for(n = 0; n < TEST_NUMBERS; n++){
		
		clock_gettime(CLOCK_REALTIME, &start);
		for(i = 0; i < COL_AMOUNT; i++){
			for(j = 0; j < ROW_AMOUNT; j++){
				temp = testArr[j][i];
			}
		}
		clock_gettime(CLOCK_REALTIME, &stop);
		
		timeTemp[n] = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;
	}
	
	for(i = 0; i < TEST_NUMBERS; i++){
		timeTotal += timeTemp[i];
	}
	timeTotal = timeTotal / 10.0;
	
	return timeTotal;
}


/*
* Function:  accessRow()
* Return: double
*
* Description:
* Accesses all the positions in the
* 2-D array in order of rows.
* Carries out this operation 10 times
* and then sums the times for an average
* 
*/
double accessRow(){
	int i, j, n;
	char temp;
	double timeTemp[TEST_NUMBERS];
	double timeTotal;
	
	for(n = 0; n < TEST_NUMBERS; n++){
		
		clock_gettime(CLOCK_REALTIME, &start);
		for(i = 0; i < ROW_AMOUNT; i++){
			for(j = 0; j < COL_AMOUNT; j++){
				temp = testArr[i][j];
			}
		}
		clock_gettime(CLOCK_REALTIME, &stop);
		
		timeTemp[n] = (stop.tv_sec - start.tv_sec) +(stop.tv_nsec - start.tv_nsec)/1000000000.0;
	}
	
	for(i = 0; i < TEST_NUMBERS; i++){
		timeTotal += timeTemp[i];
	}
	timeTotal = timeTotal / 10.0;
	
	return timeTotal;
}


/*
* Function:  printInformation()
* Return: 
*
* Description:
* Takes in the timeAverage array which
* stores all the average times for each
* of the 4 operations above. Then it 
* will print that information for the user.
* 
*/
void printInformation(double *info){
	int i;
	
	for(i = 0 ; i < TEST_TIME; i++){
		switch(i){
			case 0	:
				printf("Write Column: %.4lf",info[i]);
				printf("\n");
				break;
			case 1	:
				printf("Write Row: %.4lf",info[i]);
				printf("\n");
				break;
			case 2 	:
				printf("Read Column: %.4lf",info[i]);
				printf("\n");
				break;
			case 3	:
				printf("Read Row: %.4lf",info[i]);
				printf("\n");
				break;
			default	:
				break;
		}
	}
}