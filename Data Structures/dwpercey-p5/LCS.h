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
#define MAXLENGTH 1010


/************
* Pointers	*
************/
typedef struct LCS_Info* LCSP;

/************
* Structs	*
************/
struct LCS_Info {
	int cArray[MAXLENGTH][MAXLENGTH];
	int mLength;
	int nLength;
	char x[MAXLENGTH];
	char y[MAXLENGTH];
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