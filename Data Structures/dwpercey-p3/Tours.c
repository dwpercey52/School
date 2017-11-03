/****************************
*Name: Darrell W. Percey	*
*File: Tours.c				*
*For: Project 3				*
*							*
*****************************/


#include "Tours.h"


/************************/
/*   Genetic    	  	*/
/*	  Functions			*/
/************************/

/*
* Function:  createNewGeneration
*
* Description:
* Creates a new generation node that allows us to allocate memory
* for all the tours needed.
*
*/
genP createNewGeneration(matrixP mat){
	genP temp = (genP) malloc(sizeof(generation));
	int i;
	
	temp->tourList = malloc(mat->tourAmount * sizeof(int *));
	for(i = 0; i < mat->tourAmount; i++){
		temp->tourList[i] = malloc(((mat->cityAmount)+1) * sizeof(int));
	}
	
	for(i = 0; i < BESTTOURSIZE; i++){
		temp->bestTours[i] = 0;
	}
	
	for(i = 0; i < BESTTOURSIZE; i++){
		temp->bestToursDistance[i] = 0;
	}
	
	
	return temp;
}

/*
* Function:  searchGen
*
* Description:
* Searches for the best possible genetic distance
* within the bounds of tours/generations
*
*/
double searchGen(matrixP mat){
	int i;
	double temp;
	genP gen = createNewGeneration(mat);

	firstGenerationSet(mat, gen);
	
	
	for(i = 1; i < mat->generationAmount; i++){
		otherGenerations(mat,gen);
	}
	
	if(gen->bestToursDistance[0] > gen->bestToursDistance[1]){
		temp = gen->bestToursDistance[1];
		free(gen);
		return temp;
	}
	else{
		temp = gen->bestToursDistance[0];
		free(gen);
		return temp;
	}
	
}


/*
* Function:  firstGenerationSet
*
* Description:
* Creates the tours for the first generation and
* starts the elite/mutation pattern for following.
*
*/
void firstGenerationSet(matrixP mat, genP gen){
	int i, j, n, middle;
	n = mat->cityAmount;
	
	for(i = 0; i < n+1; i++){
		gen->tourList[0][i] = i;
	}
	gen->tourList[0][n] = 0;

	
	int middleTour[n-1];
	for(i = 0; i < n-1; i++){
		middleTour[i] = i + 1;
	}
	
	
	
	for(i = 1; i < mat->tourAmount; i++){
		permute(middleTour, n-1);
		
		middle = 1;
		gen->tourList[i][0] = 0;
		gen->tourList[i][n] = 0;
		for(j = 0; j < n-1; j++){
			gen->tourList[i][middle] = middleTour[j];
			middle++;
		}
	}
	
	
	findBestDistance(gen, mat);
}


/*
* Function:  otherGenerations
*
* Description:
* Runs any generations over 1.
* This is if the user wants more than 1 generation
*
*/
void otherGenerations(matrixP mat, genP gen){
	int i, j, n, m, mutPerc;
	n = mat->cityAmount;
	int middleTour[n-1],savePerm[n-1];
	mutPerc = mat->tourAmount * mat->mutationPer;
	
	
	//Move down two elites
	for(i = 0; i < BESTTOURSIZE; i++){
		for(j = 0; j < n; j++){
			gen->tourList[i][j] = gen->tourList[gen->bestTours[i]][j];
		}
	}
	
	j = 1;
	m = 0;
	for(i = 0; i < n-1; i++){
		middleTour[i] = gen->tourList[m][j];
		savePerm[i] = gen->tourList[mat->tourAmount-1][j];
		j++;
	}
	
	//mutate
	
	for(i = 2; i < mutPerc+2; i++ ){
		mutateTour(middleTour,n-1);
		m = 1;
		for(j = 0; j < n-1; j++){
			gen->tourList[i][m] = middleTour[j];
			m++;
		}
	}
	
	mutPerc = mutPerc+2;
	
	for(i = mutPerc; i < mat->tourAmount; i++){
		permute(savePerm,n-1);
		m = 1;
		for(j = 0; j < n-1; j++){
			gen->tourList[i][m] = savePerm[j];
		}
	}
	
	
	//compare
	
	findBestDistance(gen, mat);
}


/*
* Function:  mutateTour
*
* Description:
* Changes the elites to add back to the new generation
* 
*
*/
void mutateTour(int *tour, int n){
	int i, j;
	j = n-1;
	
	for(i = 0; i < n/2; i++){
		swap(tour, i, j);
		j--;
	}
	
	for(i = 0; i < n/2; i++){
		if(tour[i] > tour[j]){
			swap(tour, i, j);
		}
		j--;
	}
}


/*
* Function:  findBestDistance
*
* Description:
* Finds the distance of the array passed in for 
* the genetic sequence. (slightly different from the other)
*
*/
void findBestDistance(genP gen, matrixP mat){
	int i, j, n, toCity, fromCity;
	double tourPrice = 0;
	
	for(i = 0; i < mat->tourAmount; i++){
		n = 0;
		tourPrice = 0;
		for(j = 1; j <= mat->cityAmount; j++){
			fromCity = gen->tourList[i][n];
			toCity = gen->tourList[i][j];
			tourPrice += mat->matrix[fromCity][toCity];
			n++;
		}
		
		if(gen->bestToursDistance[0] == 0 || gen->bestToursDistance[1] == 0){
			if(gen->bestToursDistance[0] == 0){
				gen->bestToursDistance[0] = tourPrice;
				gen->bestTours[0] = i;
			}
			else{
				gen->bestToursDistance[1] = tourPrice;
				gen->bestTours[1] = i;
			}
		}
		else if(gen->bestToursDistance[0] > tourPrice && gen->bestToursDistance[1] > tourPrice){
			if(gen->bestToursDistance[0] > gen->bestToursDistance[1]){
				gen->bestToursDistance[0] = tourPrice;
				gen->bestTours[0] = i;
			}
			else{
				gen->bestToursDistance[1] = tourPrice;
				gen->bestTours[1] = i;
			}
		}
		else{
			if(gen->bestToursDistance[0] > tourPrice){
				gen->bestToursDistance[0] = tourPrice;
				gen->bestTours[0] = i;
			}
			else if(gen->bestToursDistance[1] > tourPrice){
				gen->bestToursDistance[1] = tourPrice;
				gen->bestTours[1] = i;
			}
		}
		
	}

}




/************************/
/*   Brute Force	  	*/
/*	  Functions			*/
/************************/

/*
* Function:  factorial
*
* Description:
* recursivly finds the factorial of the number passed
* in to return for a permutation amount.
*
*/
long int factorial(int fac){
	long int temp;
	if(fac <= 1){
		return 1;
	}
	else{
		temp = fac * factorial(fac-1);
		return temp;
	}
}


/*
* Function:  searchBruteForce
*
* Description:
* Finds the best possible outcome for travel
* distance between all combinations of cities.
*
*/
double searchBruteForce(matrixP mat) {
    int i, m, n, j, middle;
	double distance = 0;
    long int permAmount = 1;
	
	n = mat->cityAmount; 
	permAmount = factorial(n-1);
	
	
    int tour[n];
	int middleTour[n - 1];
	
	for(i = 0; i < n+1; i++){
		tour[i] = i;
	}
    tour[n] = 0;
    
	for(i = 0; i < n+1; i++){
		middleTour[i] = i+1;
	}
	
    distance = findDistance(mat, tour, n);
    
    for(i = 1; i < permAmount; i++ ) {

        permute(middleTour, n - 1);
		middle = 0;
		for(j = 0; j < n-1; j++){
			tour[middle] = middleTour[j];
			middle++;
		}
        
        m = findDistance(mat, tour, n);
		
        if( m < distance ) {
            distance = m;
        }
    }
    
    return distance;
}


/*
* Function:  findDistance
*
* Description:
* Calcualtes the array passed in for a bruteforce
* test.
*
*/
double findDistance(matrixP mat, int *tour, int amount) {
    double temp = 0;
    int i, j;
	int fromCity, toCity;
	j = 0;
	
	for(i = 1; i <= amount; i++){
		fromCity = tour[j];
		toCity = tour[i];
		temp += mat->matrix[fromCity][toCity];
		j++;
	}
    
    return temp;
}



/************************/
/*     Shared 		  	*/
/*	  Functions			*/
/************************/

/*
* Function:  swap
*
* Description:
* Takes in an array and swaps the items in position
* j and in position i
*
*/
void swap(int *arr, int x, int y){
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}


/*
* Function:  permute
*
* Description:
* Rearranges the middle of the array for a new combination
* which can be calculated later.
*
*/
void permute(int *tour, int n) {
	
	int i, j;
	if( n > 2){
		i = n - 2;
		j = n - 1;
		while( tour[i] > tour[i+1] ){
			if(i > 0){
				i = i - 1;
			}else{
				break;
			}
		}
		while( tour[i] > tour[j] ){
			if(j > 0){
				j = j - 1;
			}
			else{
				break;
			}
		} 
		swap(tour, j , i);
		j = n - 1;
		for(i = i+1; i < j; i++){
			swap(tour, j , i);
			j--;
		}
			
			
		
	}
	else{
		if(n == 2){
			i = n-1;
			j = 0;
			swap(tour, i, j);
		}
		else{
			i = n-1;
			j = 0;
			while(i > j){
				swap(tour,i,j);
				j++;
				i--;
			}
		}
	}
} 