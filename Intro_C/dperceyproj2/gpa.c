#include <stdio.h>

int main( void )
{
	float gpa;
	float   i, sum, numberGrade;
	int    numberCourses;
	char  letterGrade, modifier;


	printf("Enter the number of course:");
	scanf("%d", &numberCourses);

	for (i=0; i < numberCourses; i++)
 	{

		  
	printf ("What grade did you earn?\n");
		
	printf ("Enter A, B, C, D, or F:\n ");
	scanf (" %c" ,&letterGrade);

	printf ("Enter modifier - for letter grades A-, etc. + for letter grades B+, etc. , and _ for letter grades A, B, etc.:\n ");
	scanf (" %c", &modifier);
		  

	      if (letterGrade == 'A')
		  {
			numberGrade = 4.0f;
		  } 
	      else if (letterGrade == 'B')
		  {
			numberGrade = 3.0f;
		  } 
	      else if (letterGrade == 'C')
		  {
			numberGrade == 2.0f;
		  }
	      else if (letterGrade == 'D')
		  {
			numberGrade = 1.0f;
		  }
		else
		  {
			numberGrade = 0.0f;
		  }

		if (modifier == '-')
		  {
			numberGrade = numberGrade - 0.3f;
		  }
		else if (modifier == '+')
		  {
			numberGrade = numberGrade + 0.3f;	
		  }

		sum = sum + numberGrade;
	}


	gpa = sum/numberCourses;

	printf ("The final gpa is %1.2f.\n", gpa);

	return 0;
}
	
