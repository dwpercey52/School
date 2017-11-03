#include <stdio.h>
#include <string.h>
 
 typedef struct { 
 char label[20]; 
} WordT; 

int getMax ( WordT *words, int numWords, int index, int bottom);
void sort ( WordT *words, int numWords ); 


int main (void)  { 
  char listNo[20], stop[1] = {'0'},clear[1] = {'\0'};
  int numWords,index, a=0, i=0;
  WordT words[30];
  printf("Enter a list of words, or 0 to stop \n");
  
  // this scans for user input till they hit 0, then wipes the 0 from the array.
  do {
    scanf("%s", &listNo);
	strcpy(words[i].label , listNo);
	i++;
	numWords++;
  } while( listNo[0]!= stop[0] ) ;
  
   stpcpy( words[numWords].label, clear );
   numWords --;
  
   sort( words,  numWords ); 
   
  //prints out the new sorted list to the screen.
  for ( i=0; i < numWords; i++ ) {
    printf("%s, ", words[i].label);
  }
    
}

// takes the value given by getMax and sorts them using atemp holder.
void sort ( WordT *words, int numWords )  {
  int i=0,j=0, n, hold, bottom = 1, index =0;
  char temp[30];
  
  for (i=0;i<numWords;i++) {
    hold = getMax( words, numWords, index, bottom);
	strcpy(temp, words[i].label);
    strcpy(words[i].label, words[hold].label);
    strcpy(words[hold].label, temp);
	index++;
	bottom++;
  }
}

// used to find the index of the highest ranking word (by letter) and returns it to sort function
int getMax ( WordT *words, int numWords, int index, int bottom )  {
  int i,holdStr;
  if ( numWords == 0 )
    return -1;
	
  for (i=bottom; i<numWords; i++)  {
    if (strcmp(words[index].label,words[i].label) > 0) {
	  index = i;
	}
	else if (strcmp(words[index].label,words[i].label) < 0)  {
	  index = index;
	}
  }
  return index;
}







