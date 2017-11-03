/***************************************************************/
/* Darrell Percey				                               */
/* Test.c                                                      */
/* Project 5 || Data Structure II							   */
/*               											   */
/*	This file is the driver for the program it will run a 	   */
/*  comparison of two string and print the LCS to the screen   */
/*  it will then go to the next file which computes the 	   */
/*  similarity of multiple strings into a table.			   */
/*															   */
/*  Files Needed: Test.c LCS.c/h TableCompare.c/h			   */
/*  type make into UNIX system to compile run w/  ./LCS        */
/*															   */
/*                                                             */
/*                                                             */
/***************************************************************/



#include "LCS.h"
#include "TableCompare.h"


int main(){
	
	//Part 1 
	printf("Part 1 \n");
	printf("-------------------------------------------------------\n");
	//Find LCS of twosequences
	findLCS();
	printf("-------------------------------------------------------\n");
	printf("\n");
	
	//Part 2
	printf("Part 2 \n");
	printf("-------------------------------------------------------\n");
	//comparison of multiple sequences
	compareMultipleSequences();
	printf("-------------------------------------------------------\n");
	
	return 0;
}