#include <stdio.h>


int main (void)
{

    double d, i, Irest, Amount;
    int x, time;

    printf("Please enter a deposit amount:\n");
    scanf("%lf", &d);

    printf("Please enter your interest rate:\n");
    scanf("%lf", &i);

    printf("Please enter the number of years:\n");
    scanf("%d", &x);

    Irest = (d*i*x)*12 /100;
    

    while ( time < x ) 
	  { 
	    Amount = d + Irest;
	    time++;
	  } 

    printf("After %d number of years, the deposit in the savings account is now %.3f \n", x, Amount);

}

