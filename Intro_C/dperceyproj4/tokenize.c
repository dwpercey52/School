#include <stdio.h>
#include <string.h>

// global variable to hold position of the tokenize function 
// helps maintain spot and contiune from the current null position
char* tokenize ( char *text, const char *separators);
int placeHolder = -1, Length;
char *tokens[15];

	
int main (void)  {
  char *text, *separators = {" .,?"},userInput[50];
  int i = -1, count;
  
  printf("Please enter a sentence to be tokenized \n");
  fgets( userInput, 50, stdin);
  Length = strlen(userInput);
  text = userInput;
  
  // do while to do the tokenize process as needed till null was reached.
  // when returning text I couldn't figure out how to get words other then
  // the first part of the string.
  do  { 
    i++;
    tokens[i] = tokenize( text, separators );
	printf("%s \n", tokens[i]);
  }  while ( tokens[i] != NULL);
 

} 

// Tokenize function, Fully tokenizes the whole string but I couldn't figure out
// how to transfer the information to the *tokens arry
char* tokenize ( char *text, const char *separators ) { 
  int i, j;
  
  for ( i=placeHolder+1; i<Length; i++ )  {
	for ( j=0; j<4; j++ )  {
	  if ( *(text+i) == *(separators+j))  {
		*(text+i) = '\0';
	    placeHolder = i;
		return text;
      }
	}
  }
  return NULL;  
}