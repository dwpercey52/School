#include <stdio.h>

int main (void)



{    
    int z, Rem1, Rem2, Rise; 
    double x,x2, y2,  y, s, r, p, Remainder;

    printf("Enter a value for x:\n");
    scanf("%lf", &x);
    

    while (  x  <  0 ) 	
	 {
	   printf("Error with input try again!\n");
	   scanf("%lf",&x);
 	 }
	 
    printf("Enter a value for y:\n");
    scanf("%lf", &y);

    while( y < 0 )
	 {
	   printf("Error with input try again!\n");
	   scanf("%lf",&y);
	 }


    printf("Enter a value for z:\n");
    scanf("%d",&z);

    while ( z < 0 )
	 { 
	   printf("Error with input try again!\n");
	   scanf("%d", &z);
	 }

    
    Rem1 = x*1000;
    Rem2 = y*1000;
    Remainder =  Rem1 % Rem2;

    if ( Rem1 % Rem2 != 0 ) 
	{  
 	   r = Remainder/1000; 
	   printf("The remainder of x and y is %.3f \n",r);
	}
    else
	{
	   printf("The remainder of x and y is  0");
        }
  
   
    s = (x*x)+(y*y)+(z*z);

    printf("The sum of the squares of x, y, and z is %.3f \n", s);

	x2 = x;
	y2 = y;
  
    while ( Rise+1 < z)
	 { 
	   x2 = x2*x;
	   y2 = y2*y;
	   Rise++;
 	 } 
    
    p = x2 + y2;

    printf("The sum of x to the power of z and y to the power of z is %lf \n", p);

}
