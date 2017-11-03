#include <stdio.h>
#include <string.h>

int contains ( const char *text, const char *pattern );


int main (void)
{
  int inputs, patternPosition;
  char text[30], pattern[30];
  inputs = 0;
  // While loop to test 5 different phrases and text
  while ( inputs < 5 ) {
    printf("Please enter a phrase. \n");
	fgets(text,30,stdin);
	printf("Please enter a pattern to search for \n");
	fgets(pattern,20,stdin);
	patternPosition = contains( text, pattern);
	// test if the return was there or not  if -1 then there was no pattern in text 
	if ( patternPosition != -1)  { 
	  printf("Pattern %s occurs in %s at the location %d \n", pattern, text, patternPosition);
	}
 	else  {
	  printf("The pattern %s is not in %s \n ",pattern, text);
	}
	inputs++;
  }
}

// contains function for comparing both strings text and pattern against each other for a position
int contains ( const char *text, const char *pattern ) {
  int i,n, a,hold, textSize = strlen(text), patternSize = strlen(pattern);
  i = 0;
  n = 0;
  // while loop to scan through text string by single letters
  while( i < textSize )  {
  // if a match occurs with the text[i] this statement starts a for loop to compare further.
    if ( text[i] == pattern[n] )  {
      hold = i;	
	  for( n=0; n < patternSize; n++ ) {
	    if ( text[i+n] == pattern[n] )  {
		  i++;
		}
      }
	}
	if ( n == patternSize )  { 
	  return hold;
	}
	i++;
  }
  return -1;
}