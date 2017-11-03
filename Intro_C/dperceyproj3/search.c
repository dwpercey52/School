#include <stdio.h>

// SearchLinear function for searching the array for the index value of s 
int searchLinear( int s, int *list, int n )
{
  int i; 
  int l = -1;

  for ( i=0; i < n; i++) 
   { 
    
     if ( s == list[i] ) 
       {
         l = i;
         break;
       }
   }

   return l;
}

// Binary search fucntion for searching the array for the index value of s
int searchBinary( int s, int *list, int n )
{
  int bot, mid, i, l;
    bot = 0;
    l = -1;
    mid = (bot + n) / 2;

 
 while ( bot <= n )
      {
        if ( list[mid] < s )
          {
	    bot = mid + 1;
	  }

	else if ( list[mid] > s )
	  {
	   n = mid - 1;
	  }

        if ( list[mid] ==  s )
	  {
	    l=mid;
	    break;
	  }

	if ( bot > 10 )
	  {
	    break;
	  } 
        
	mid = (bot + n) / 2;

      } 
    return l;

} 







int main (void) 

{
   int list[10], n, s, Nret;
  

   // loop for asking values of numbs[] 
   for(n=0; n<10; n++)
     {
      printf("Enter a postive interger in ascending order \n");
      scanf("%d", &list[n]);

   // checks if the value entered are positive
     if(list[n] < 0 ) 
       {
	printf("Enter a postive value \n");
	scanf("%d", &list[n]);
       } 
      } 
     

   // Ask for a search input
    printf("Enter a number to search for \n"); 
    scanf("%d", &s);  


   // runs the searchLinear function and then input the return in printf 
     searchLinear(s, list, 10);

    int index;
    index = searchLinear( s, list, 10); 

    // if statement to check for index value in searchLinear if -1 returned then DNE
    if ( index == -1 )
      {
        printf("The searched value doesn't exist in the array \n");
      }
    else
      {
        printf("The value %d is in the index %d  \n", s, index);
      }
    // checks the value s compared to numbs[] value by binary search
    searchBinary( s, list, 10);
    index = searchBinary(s, list, 10); 
   
    // if-statement to check for index value to display if -1 returned then DNE
    if ( index == -1)
      {
        printf("The searched value doesn't exist in the array \n");
      }
    else
      {
         printf("The value %d is in the index %d \n", s , searchBinary(s, list, 10));   
      } 


    return 0;
        	
}

