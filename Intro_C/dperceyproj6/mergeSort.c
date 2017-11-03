#include <stdio.h>
#include <stdlib.h>

int getValue( FILE*, int *sort);
int processFile( FILE *sortP3, int sort1, int sort2);

int main (int sortNums, char *sortFiles[])  {
  FILE *sortP1;
  FILE *sortP2;
  FILE *sortP3;
  int sortOne = 1, sortTwo, sortThree;

  
  // checking to see if all the files were opened if not, then exits the program 
  if ( sortNums != 4 ) {
    printf("Failed to do operations \n");
	return 1;
  }
  
  sortP1 = fopen(sortFiles[1], "r");
  sortP2 = fopen(sortFiles[2], "r");
  
  // checks to see if the files that were open, had numbers to be sorted.
  if ( sortP1 == NULL || sortP2 == NULL ) {
    printf("Failure to open read files");
	return 2;
  }
	
  sortP3 = fopen(sortFiles[3], "w+");
  
  if ( sortP3 == NULL ) {
    printf("Failure to open write file");
	return 3;
  }
  
  getValue ( sortP1, &sortOne);
  getValue ( sortP2, &sortTwo);
  
  
  // while loop for using the functions to compare the values given back to the previous
  // value that was assigned. This then places the low number in the third file. 
  while ( !feof(sortP1) && !feof(sortP2) ) {
    
	sortThree = processFile( sortP3, sortOne, sortTwo);
	if ( sortThree == sortOne ) {
	  getValue ( sortP1, &sortOne);
	  if ( feof(sortP1)) {
	    getValue ( sortP2, &sortOne);
	  }
	}
	else if ( sortThree == sortTwo ) {
	  getValue ( sortP2, &sortTwo);
      if ( feof(sortP2)) { 
        getValue ( sortP1, &sortTwo);	  
      }
    }
  }
  
  
  // puts the last two integers in the third file.
  if ( sortOne > sortTwo ) {
    fprintf(sortP3,"%d \n", sortTwo);
	fprintf(sortP3,"%d \n", sortOne);
  }
  else {
    fprintf(sortP3,"%d \n", sortTwo);
	fprintf(sortP3,"%d \n", sortOne);
  }
} 
 
 // this function compares the value from txt 1 and txt 2 files and returns the value 
 // with the returned value it allows me to assign it to a variable and place in the third file
int processFile( FILE *sortP3, int sort1, int sort2 ) {
  int low; 
  
  if ( sort1 > sort2 ) {
    low = sort2;  
  } 
  else {
    low = sort1; 
  }
  fprintf(sortP3, "%d \n", low);
  return low;
}

// Function for fscanf so I could easily change the values that were place in the while loop in main 
int getValue ( FILE *sortP, int *sort) { 

 fscanf(sortP, "%d", &*sort);
   
  
}