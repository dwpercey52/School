/****************************************************************/
/* Darrell Percey				                               	*/
/* Test.c                                                      	*/
/* Project 5 || Data Structure II							   	*/
/*               											   	*/
/*	See the LCS.c file for more details.						*/
/*                                                             	*/
/*                                                             	*/
/****************************************************************/


#ifndef LCS_h
#define LCS_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRING 100


/************
* Pointers	*
************/
typedef struct LCS_Info* LCSP;

/************
* Structs	*
************/
struct LCS_Info {
	int cArray[MAXSTRING][MAXSTRING];
	int mLength;
	int nLength;
	char x[MAXSTRING];
	char y[MAXSTRING];
} LCS_Info;


/****************************************
* Functions (see C file for details)	*
****************************************/
void findLCS();
LCSP createNewLCSNode();
void readFileSequences(char *x,char *y);
void LCSTable(LCSP seq);
void printSequence(int m, int n, LCSP seq);

#endif