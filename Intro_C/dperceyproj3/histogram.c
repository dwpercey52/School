#include <stdio.h>

/**
 * Prints a histogram to the screen using horizontal bar chart.
 * Parameters:
 *   list - a list of integers
 *   n - the number of values in the list
 */
void printHistogram (int *list,  int *hist, int n );

/**
 * This program requests data from the user and then
 * computes and prints a histogram. You may assume that
 * the data values entered are in the range of 0 to 9.
 */
int main ( void )
{
	int i, n;

	// Data entry
	//
	printf ("How many values in your data set? ");
	scanf ("%d", &n);

	int list[n];
       // Loop to get values from user and making sure it's in the range 0-9
	for (i=0; i < n; i++)
	  {
		printf ("Enter a value: ");
		scanf ("%d", &list[i]);
                
                if ( list[i] > 9 ) 
		  {
                    printf("Enter in the valid range 0-9: "); 
	            scanf("%d", &list[i]); 
		  } 
		else if ( list[i] < 0 ) 
		  { 
                    printf("Enter in the valid range 0-9: ");
                    scanf("%d", &list[i]); 
		  } 
		         
          }
	

	// Processing data to compute histogram
	//
	int hist[10]; 


	// Printing histogram
	printHistogram (list, hist, n);
        
        for( i=0; i < 10; i++)
	 {
           printf("%d ", hist[i]);
	 } 

	return 0;
}

void printHistogram ( int *list, int *hist, int n )
{
    int i, j, c, h;
    c=0; h=0;
    for (i=0; i < 10; i++)
      {
	printf ("[%d] ", i);
                          
	for (j = 0; j < n; j++)
          {   
 	    if ( list[j] == c) 
              {
	        printf ("*"); 
                h++;
              } 
          }
       // This updates the histogram array values to match the amounts that are *  
        hist[i] = h;
        h=0;
       // the c is a constant that is tested against the value of list[] to add * to the histogram
        c++;
    	printf ("\n");
    }
}
