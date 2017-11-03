#include <stdio.h>

/**
 * Finds the largest value in a list.
 * list - an array of numbers
 * n    - the size of the array
 *
 * Returns the index where the largest value is stored
 * or -1 if there are no array elements.
 */


/**
 * Switches two values given as parameter.
 * 
 * a - an integer value
 * b - an integer value
 */
void switchValue ( int *a, int *b )
{
   int temp;

   temp = *b;
   *b = *a;
   *a = temp;
}

int main ( void )
{
   int n;
   
   printf ("Enter the number of elements you want to sort: ");
   scanf ("%d", &n);

   int numbers[n];
   int i;

   for ( i=0; i < n; i++ ) {
      printf ("Enter a value: ");
      scanf ("%d", &numbers[i]);
   }

   int temp = n;
   while (temp > 1) {
       
      int result = getMax ( numbers, temp );
      switchValue ( &numbers[result], &numbers[temp-1] );

      temp--;
   }

   for ( i=0; i < n; i++ ) {
       printf ("%d ", numbers[i]);
   }
   printf ("\n");

   return 0;
}
