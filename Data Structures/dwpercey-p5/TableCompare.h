/****************************************************************/
/* Darrell Percey				                               	*/
/* Test.c                                                      	*/
/* Project 5 || Data Structure II							   	*/
/*               											   	*/
/*	See the TableCompare.c file for more details.				*/
/*                                                             	*/
/*                                                             	*/
/****************************************************************/


#ifndef TableCompare_h
#define TableCompare_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRING 100
#define MAXLENGTH 1010


/************
* Pointers	*
************/
typedef struct sequences* seqP;


/************
* Structs	*
************/
struct sequences{
	int mArray[2][MAXLENGTH];
	int mLength;
	int nLength;
	int stringAmount;
	char listOfStrings[MAXSTRING][MAXLENGTH];
} sequences;


/****************************************
* Functions (see C file for details)	*
****************************************/
void readFileMultipleSequence(seqP seq);
seqP createNewSeqNode();
void compareMultipleSequences();
char findLCSLength(seqP seq, int x, int y);
char findSimilarity(int m, int n, int comp);
void wipeArray(seqP seq);





#endif