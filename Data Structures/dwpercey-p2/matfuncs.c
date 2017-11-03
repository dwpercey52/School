#include "matfuncs.h"
#include "queue.h"
/*************************************************************** 
  Student Name: Darrell Percey
  File Name: matfuncs.c
  Assignment number 2
***************************************************************/

int factorial(int digit){
	int a = 1;
	int i;
	
	if(digit == 0){
		a = 1;
	}
	else{
		for(i=1;i<=digit;i++){
		a = a * i;
		}
	}
	return a;
}



void percentidleFunc(int m, int mu, int lam){
	double total = 0;
	double total2 = 0;
	double temp = 0;
	int i;

	
	for(i=0; i<(m); i++){
		total = total + ((1.0)/(factorial(m-1)))*pow((lam/(double)mu),(m-1));
	} 
	
	total2 = ((1.0)/factorial(m))*(pow(lam/(double)mu,m));
	total2 = (total2)*((m*mu)/((double)(m*mu)-lam));
	
	
	total = (1.0)/(total + total2);
	
	
	printf("Po = %.3lf \n", total);
	avgpeopleIn(m, mu, lam, total);
}


void avgpeopleIn(int m, int mu, int lam, double po){
	double total = 0;
	
	total = lam*mu*pow((lam/(double)mu), m);
	total = total/(pow((m*mu-lam),2)*factorial(m-1)); 
	total = total * po;
	total = total + (lam/(double)mu);
	printf("L = %.3lf \n", total);
	
	avgtimeWait(lam, total);
	avgnumQue(mu, lam, total);
}

void avgtimeWait(int lam, double L){
	double total;
	
	total = (L/(double)lam);
	printf("W = %.3lf \n", total);
	
	
}

void avgnumQue(int mu, int lam, double L){
	double total;
	
	total = L - (lam/(double)mu);
	printf("Lq = %.3lf \n", total);
	
	avgtimeSpend(lam, total);
}

void avgtimeSpend(int lam, double Lq){
	double total;
	
	total = (Lq / (double) lam);
	printf("Wq = %.3lf \n", total);
	
}