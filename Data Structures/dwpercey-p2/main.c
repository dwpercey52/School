#include "queue.h"
#include "matfuncs.h"
/*************************************************************** 
  Student Name: Darrell Percey
  File Name: main.c
  Assignment number 2
***************************************************************/

int main(){
	Customer* p1 = startCustomer();
	//srand(time(NULL));
	askInfo();
	percentidleFunc(serv, avgSerTime, avgArrive);
	p1 = runSimulation(p1);
	return 0;
}