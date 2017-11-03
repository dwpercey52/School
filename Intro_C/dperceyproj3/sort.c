#include <stdio.h> 


int getMax (int list[], int n)
  {
    int i, temp, max;
    temp = 0;
    max = 0;
    
    for ( i=0; i < n; i++)
      {
        if ( list[i] > temp ) 
          {
	    temp = list[i];
	    max = i ;
	  }
        
      }

    n = max;
   
   return n;
   }



int main (void) 

{
   
   int  amount, i, temp, hold;
  
   // gains the amount needed for the array
   printf("Enter the amount of of numbers you want to sort \n");
   scanf("%d", &amount);

   int sort[amount];
   hold = amount;
       
   for ( i = 0; i < amount; i++ )
     {
       printf("Please enter amounts for storage \n");
       scanf("%d", &sort[i]); 
     } 
   
   // loop to sort the larger numbs to the top and rerun the function getMax 
   for ( i = 0; i < amount; i++ )
     {
      getMax (sort, amount);
      
      temp = sort[getMax(sort, amount)];
      sort[getMax(sort,amount)] = sort[amount-1];
      sort[amount-1] = temp;
      amount --;
     }	
   
   // loop to make sure if the highest was sort[0] that it gets moved to a higher position
   for ( i = 0; i < hold; i++)
     {
       if ( sort[0] > sort[i])
	 {
	  temp = sort[0];
	  sort[0] = sort[i];
	  sort[i] = temp;
	 }
      }
     // prints the new order of sorted array
    for ( i = 0; i < hold; i++ )
 	{ 
	printf(" %d", sort[i]); 
	} 


}

