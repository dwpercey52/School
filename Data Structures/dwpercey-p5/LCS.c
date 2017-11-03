/****************************************************************/
/* Darrell Percey				                               	*/
/* Test.c                                                      	*/
/* Project 5 || Data Structure II							   	*/
/*               											   	*/
/*	This file pulls in two strings and compared them using a 	*/
/*  c-array and finds the sequence from that matrix.			*/
/*                                                             	*/
/*                                                             	*/
/****************************************************************/
#include "LCS.h"


/*
* Function:  findLCS()
* 
* Description:
* Calls functions to compare two strings and
* find their LCS to print to the screen.
*
*/
void findLCS(){
	
	LCSP seq = createNewLCSNode();
	
	LCSTable(seq);
	printf("Sequence 1: [%s]  \n",seq->x);
	printf("Sequence 2: [%s] \n",seq->y);
	printf("The longest common sequence is: [");
	
	printSequence(seq->mLength, seq->nLength, seq);
	printf("] \n");

	free(seq);
	
}


/*
* Function:  createNewLCSNode()
* 
* Description:
* creates and allocates memory for a new
* LCS structure
*
*/
LCSP createNewLCSNode(){
	int i,j;
	LCSP temp  = (LCSP) malloc(sizeof(LCS_Info));
	
	for(i = 0; i < MAXLENGTH; i++){
		for(j = 0; j < MAXLENGTH; j++){
			temp->cArray[i][j] = 0;
		}
	}
	
	for(i = 0; i < MAXLENGTH; i++){
		temp->x[i] = '\0';
		temp->y[i] = '\0';
	}
	
	readFileSequences(temp->x, temp->y);
	
	
	temp->mLength = 0;
	temp->nLength = 0;
	
	return temp;
}


/*
* Function:  readFileSequences()
* 
* Description:
* Reads in the two strings from the file.
* "twoSequences.txt"
*
*/
void readFileSequences(char *x,char *y){
	FILE *in;
	in = fopen("twoSequences.txt","r");
	
	if( !in ){
		perror("Couldn't open file! \n");
		exit(1);
	}
	
	fscanf(in,"%s", x);
	fscanf(in,"%s", y);
	
}


/*
* Function:  LCSTable()
* 
* Description:
* Makes a c-array table with a 2-D matrix
* using the two strings.
*
*/
void LCSTable(LCSP seq){
	int i, j;
	
	seq->mLength = strlen(seq->x);
	seq->nLength = strlen(seq->y);
	
	for(i = 1; i <= seq->mLength; i++){
		for(j = 1; j <= seq->nLength; j++){
			
			if( seq->x[i-1] == seq->y[j-1]){
				seq->cArray[i][j] = seq->cArray[i-1][j-1] +1;
			}
			else if(seq->cArray[i-1][j] >= seq->cArray[i][j-1]){
				seq->cArray[i][j] = seq->cArray[i-1][j];
			}
			else{
				seq->cArray[i][j] = seq->cArray[i][j-1];
			}
		}
	}
}


/*
* Function:  printSequence()
* 
* Description:
* recursivly finds the LCS of the two strings
* and prints it to the screen one character 
* at a time.
*
*/
void printSequence(int m, int n, LCSP seq){
	if( m == 0 || n == 0){
		return;
	}
	
	if(seq->cArray[m][n] > seq->cArray[m-1][n] && seq->cArray[m][n] > seq->cArray[m][n-1]){
		printSequence(m-1, n-1, seq);
		printf("%c",seq->x[m-1]);
		
	}
	else if(seq->cArray[m][n] == seq->cArray[m-1][n] && seq->cArray[m][n] == seq->cArray[m][n-1]){
		printSequence(m, n-1, seq);
	}
	else{
		printSequence(m-1, n, seq);
	}
	
}