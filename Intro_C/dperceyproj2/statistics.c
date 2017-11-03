#include <stdio.h>

int main (void)
{
    int age, s, v, l;
    

           printf("Enter an age 1-150\n");
           scanf("%d", &age);  
	 
           
           if ( s > age && age > 0)
		{
		   s = age;
		}
	   else
		{
		   s = s;
		} 

 
while ( (age >  0) && (age < 150) )
	{
	   printf("Enter an age 1-150\n");
	   scanf("%d", &age);
             if ( s > age && age > 0)
		{
		   s = age;
		}
	     else
		{
		   s = s;
		}
	     if ( l < age && age < 150) 
		{
		   l = age;
		}
	     else
		{
		   l = l;
		}  
	}

    v = (s+l)/2;
   
    printf("The smallest entered age is %d \n", s);
    printf("The largest entered age is %d \n", l);
    printf("The average entered age is %d \n", v);

}

