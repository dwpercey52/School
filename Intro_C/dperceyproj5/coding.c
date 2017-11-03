#include <stdio.h>
#include <string.h>

typedef struct {
  char from[28];
  char to[28];
} CodeT;

void encodeStr ( char *input, char *output, CodeT code );
void decodeStr ( char *input, char *output, CodeT code );

int main (void)  {
  char input[40], output[40];
  int a= 0;

  //Initializing the struct for the code 
  CodeT code = { .from = " abcdefghijklmnopqrstuvwxyz", 
                 .to = ".172093%@#+!:_-$^*()854=6?>" };
				 
 //do while loop for the user input to be sent to code and decode, ends on empty enter.
  do {
    input[0] = '\0';
    printf("Please enter a word or sentence to code and decode \n");
    fgets(input, 40, stdin); 
    encodeStr( input, output, code );
    printf("Your input coded is %s \n",output);
    decodeStr( input, output, code );
    printf("Your input decoded is %s \n", output);
	} while ( input[1] != '\0');
 
  
}

// Function for encoding the input of the user to the to code.
// similar loops were used for both decode and code in a reverse manner.
void encodeStr ( char *input, char *output, CodeT code ) {
  int a,next=0,i=0, length = strlen(input);
  
  
  for ( i=0; i < length; i++ )  {
    for ( a=0; a < 28; a++ )  {
      if ( input[i] == code.from[a] )  {
	    input[next] = code.to[a];
	    output[next] = code.to[a];
        next++;
	  }
	  else if ( input[i] == '\0' )  {
	    input[next] = '\0';
	    output[next] = '\0';
	  }
    }
  }
  
 
}

// function for encoding the input of the user to the from code. 
// similar loops were used for both decode and code in a reverse manner.
void decodeStr ( char *input, char *output, CodeT code ) {
 int a,next=0,i=0, length = strlen(input);

  for ( i=0; i < length; i++ )  {
    for ( a=0; a < 28; a++ )  {
      if ( input[i] == code.to[a] )  {
	    input[next] = code.from[a];
	    output[next] = code.from[a];
        next++;
	  }
	  else if ( input[i] == '\0' )  {
	    input[next] = '\0';
	    output[next] = '\0';
	  }
    }
  }
}