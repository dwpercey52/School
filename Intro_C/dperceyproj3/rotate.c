#include <stdio.h>

int main (void)

{
   double  matrixXY[1][1];
   double  matrixC[2][2]= { 0.5, -0.866, 0.866, 0.5};
   double  matrixHold[1][1];
   
   printf("Enter a value for x \n");
   scanf("%lf", &matrixXY[0][0]);

   printf("Enter a value for y \n");
   scanf("%lf", &matrixXY[1][0]);

   matrixHold[0][0] = (matrixXY[0][0] * matrixC[0][0])+(matrixXY[1][0]*matrixC[0][1]);
   matrixHold[1][0] = (matrixXY[0][0] * matrixC[1][0])+(matrixXY[1][0]*matrixC[1][1]); 
  
   printf("x is %lf and y is  %lf for the new matrix \n", matrixHold[0][0], matrixHold[1][0]);
   

}



