/****************************************************************/
/* Darrell Percey				                               	*/
/* Test.c                                                      	*/
/* Project 5 || Data Structure II							   	*/
/*               											   	*/
/*	This file runs the multiple string comparison after finding	*/	
/*	the length of each of the LCS it will solve by finding a 	*/
/*	percentage of the total lengths and by percentage based on 	*/
/*	the LCS													   	*/
/*                                                             	*/
/*                                                             	*/
/****************************************************************/


#include "TableCompare.h"



/*
* Function:  compareMultipleSequences()
* 
* Description:
* compares the multiple strings by sending
* them to a 2*M table for computation
*
*/
void compareMultipleSequences(){
	int i, j, n;
	char value;
	seqP seq = createNewSeqNode();
	
	for(i = 0; i < seq->stringAmount; i++){
		printf("   %d", i+1);
	}
	printf("\n");
	
	for(i = 0; i < seq->stringAmount; i++){
		printf("%d  ",i+1);
		for(n = 0; n < i+1; n++){
			printf("-   ");
		}
		
		for(j = i+1; j < seq->stringAmount; j++){
			value = findLCSLength(seq, i, j);
			printf("%c   ", value);
		}
		printf("\n");
	}
	
	
	free(seq);
}


/*
* Function:  createNewSeqNode()
* 
* Description:
* Allocates memory for a new sequence structure
* and sets all values to 0 or NULL
*
*/
seqP createNewSeqNode(){
	int i, j;
	seqP temp = (seqP) malloc(sizeof(sequences));
	
	wipeArray(temp);
	
	temp->mLength = 0;
	temp->nLength = 0;
	temp->stringAmount = 0;
	
	for(i = 0; i < MAXLENGTH; i++){
		for(j = 0; j < MAXLENGTH; j++){
			temp->listOfStrings[i][j] = '\0';
		}
	}
	
	readFileMultipleSequence(temp);
	
	return temp;
}


/*
* Function:  readFileMultipleSequence()
* 
* Description:
* Reads the multiple strings into a
* 2-D array
*
*/
void readFileMultipleSequence(seqP seq){
	FILE *in;
	in = fopen("multipleSequencess.txt","r");
	
	if( !in ){
		perror("Couldn't open file! \n");
		exit (1);
	}
	
	fscanf(in, "%s", seq->listOfStrings[seq->stringAmount]);
	while(seq->listOfStrings[seq->stringAmount][0] != '\0'){
		seq->stringAmount++;
		fscanf(in, "%s", seq->listOfStrings[seq->stringAmount]);
	}
}


/*
* Function:  findLCSLength()
* 
* Description:
* computes the LCS by comparing the letters
* in the strings.
*
*/
char findLCSLength(seqP seq, int x, int y){
	int i, j, n, value;
	char similar;
	
	seq->mLength = strlen(seq->listOfStrings[x]);
	seq->nLength = strlen(seq->listOfStrings[y]);
	
	for(i = 1; i <= seq->nLength; i++){
		for(j = 1; j <= seq->mLength; j++){
			
			if( seq->listOfStrings[x][i-1] == seq->listOfStrings[y][j-1]){
				seq->mArray[1][j] = seq->mArray[0][j-1] +1;;
			}
			else if(seq->mArray[0][j] >= seq->mArray[1][j-1]){
				seq->mArray[1][j] = seq->mArray[0][j];
			}
			else{
				seq->mArray[1][j] = seq->mArray[1][j-1];
			}
		}
		
		for(n = 1; n <= seq->mLength; n++){
			seq->mArray[0][n] = seq->mArray[1][n];
			seq->mArray[1][n] = 0;
		}
	}
	
	value = seq->mArray[0][seq->mLength];
	
	similar = findSimilarity(seq->mLength, seq->nLength, value);
	
	wipeArray(seq);
	
	return similar;
}


/*
* Function:  findSimilarity()
* 
* Description:
* Computes the percentage of lengths and 
* the percentage of the LCS to the shortest
* string.
*
*/
char findSimilarity(int m, int n, int comp){
	float percentCheck, LCScheck;
	char value;
	
	if(m > n){
		percentCheck = (float) n / (float) m;
		LCScheck = (float) comp / (float) n;
	}
	else{
		percentCheck = (float) m / (float) n;
		LCScheck = (float) comp / (float) m;
	}
	
	value = 'D';
	
	if(percentCheck >= .39){
		if(LCScheck >= .49){
			value = 'L';
		}
	}
	
	if(percentCheck >= .79){
		if(LCScheck >= .59){
			value = 'M';
		}
	}
	
	if(percentCheck >= .89){
		if(LCScheck >= .79){
			value = 'H';
		}
	}
	
	return value;
}


/*
* Function:  wipeArray()
* 
* Description:
* wipes the mArray clean just incase.
*
*
*/
void wipeArray(seqP seq){
	int i, j;
	
	for(i = 0; i < 2; i ++){
		for(j = 0; j < MAXLENGTH; j++){
			seq->mArray[i][j] = 0;
		}
	}
}